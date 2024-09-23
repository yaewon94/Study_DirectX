#include "pch.h"
#include "CollisionManager.h"
#include "Collider2D.h"
#include "GameObject.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}

void CollisionManager::AddCollider(const Ptr<Collider2D>& collider)
{
	LAYER_TYPE layer = collider->GetOwner()->GetLayer();
	const auto iter = m_colliderMap.find(layer);

	if (iter == m_colliderMap.end())
	{
		vector<Ptr<Collider2D>> vec;
		vec.push_back(collider);
		m_colliderMap.insert(make_pair(layer, vec));
	}
	else
	{
		// 중복체크
		for (auto& _collider : iter->second)
		{
			if (collider.GetAddressOf() == _collider.GetAddressOf())
			{
				throw std::logic_error("이미 등록된 콜라이더 입니다");
			}
		}

		iter->second.push_back(collider);
	}
}

void CollisionManager::RemoveCollider(const Ptr<Collider2D>& collider)
{
	LAYER_TYPE layer = collider->GetOwner()->GetLayer();
	const auto mapiter = m_colliderMap.find(layer);

	if (mapiter != m_colliderMap.end())
	{
		auto& vec = mapiter->second;

		for (auto veciter = vec.begin(); veciter != vec.end(); ++veciter)
		{
			if (collider.GetAddressOf() == veciter->GetAddressOf())
			{
				// CollisionSet에 등록된 경우 제거
				for (auto setiter = m_collisionSet.begin(); setiter != m_collisionSet.end(); ++setiter)
				{
					UINT leftID = (*setiter) >> 4;
					UINT rightID = 0b1111 & (*setiter);

					if (collider->GetID() == leftID || collider->GetID() == rightID)
					{
						ChangeCollisionSet(leftID, rightID, false);
						break;
					}
				}

				// ColliderMap에서 제거
				vec.erase(veciter);
				if (vec.empty()) m_colliderMap.erase(mapiter);
				return;
			}
		}
	}

	throw std::logic_error("등록되지 않은 콜라이더 입니다");
}

void CollisionManager::Tick()
{
	// 다른 타입의 레이어에 속한 콜라이더끼리 충돌체크
	for (auto layerA = m_colliderMap.begin() ; layerA != m_colliderMap.end(); ++layerA)
	{
		auto layerB = layerA;
		for (++layerB; layerB != m_colliderMap.end(); ++layerB)
		{
			CheckCollision(layerA->first, layerB->first);
		}
	}
}

void CollisionManager::CheckCollision(LAYER_TYPE a, LAYER_TYPE b)
{
	auto& vecA = m_colliderMap.find(a)->second;
	auto& vecB = m_colliderMap.find(b)->second;

	for (auto& a : vecA)
	{
		for (auto& b : vecB)
		{
			if (IsCollision(a, b)) ChangeCollisionSet(a, b, true);
			else ChangeCollisionSet(a, b, false);
		}
	}
}

bool CollisionManager::IsCollision(const Ptr<Collider2D>& a, const Ptr<Collider2D>& b)
{
	static const UINT RECT = 4;
	static const Vec3 arrRect[RECT] =
	{
		Vec3(-0.5f, 0.5f, 0.f),
		Vec3(0.5f, 0.5f, 0.f),
		Vec3(0.5f, -0.5f, 0.f),
		Vec3(-0.5f, -0.5f, 0.f)
	};

	const Matrix& matA = a->GetWorldMatrix();
	const Matrix& matB = b->GetWorldMatrix();

	// 투영축(투영을 시킬 대상) 구하기
	Vec3 arrProj[RECT] = {};
	arrProj[0] = XMVector3TransformCoord(arrRect[1], matA) - XMVector3TransformCoord(arrRect[0], matA);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matA) - XMVector3TransformCoord(arrRect[0], matA);
	arrProj[2] = XMVector3TransformCoord(arrRect[1], matB) - XMVector3TransformCoord(arrRect[0], matB);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matB) - XMVector3TransformCoord(arrRect[0], matB);

	// 월드공간에서 두 충돌체의 중심을 이은 벡터
	Vec3 center = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matA) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matB);

	for (UINT i = 0 ; i < RECT; ++i)
	{
		Vec3 vProj = arrProj[i];
		vProj.Normalize();

		float fCenter = fabs(center.Dot(vProj));
		float fDistance = 0.f;

		for (UINT j = 0; j < RECT; ++j)
		{
			fDistance += fabs(vProj.Dot(arrProj[j]));
		}

		fDistance /= 2.f;

		if (fDistance < fCenter) return false;
	}

	return true;
}

void CollisionManager::ChangeCollisionSet(const Ptr<Collider2D>& a, const Ptr<Collider2D>& b, bool isCollision)
{
	COLLIDER_ID id = {};
	id.left = a->GetID();
	id.right = b->GetID();
	const auto iter = m_collisionSet.find(id.ID);

	// 이번 프레임 충돌
	if (isCollision)
	{
		// 저번 프레임에 충돌하지 않은 경우
		if (iter == m_collisionSet.end())
		{
			m_collisionSet.insert(id.ID);
			a->OnCollisionEnter(b->GetOwner()->GetLayer());
			b->OnCollisionEnter(a->GetOwner()->GetLayer());
		}
		// 저번 프레임에 충돌한 경우
		else
		{
			a->OnCollisionStay(b->GetOwner()->GetLayer());
			b->OnCollisionStay(a->GetOwner()->GetLayer());
		}
	}
	// 이번 프레임에 충돌하지 않음
	else
	{
		// 저번 프레임에 충돌한 경우
		if (iter != m_collisionSet.end())
		{
			m_collisionSet.erase(iter);
			a->OnCollisionExit(b->GetOwner()->GetLayer());
			b->OnCollisionExit(a->GetOwner()->GetLayer());
		}
	}
}