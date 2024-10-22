#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Component.h"
#include "Transform.h"
#include "RenderManager.h"
#include "RenderComponent.h"
#include "Script.h"
#include "CollisionManager.h"
#include "Collider2D.h"

GameObject::GameObject() 
	: m_layer(LAYER_TYPE::NONE)
	, m_renderComponent(nullptr)
	, m_collider(nullptr)
	, m_parent(nullptr)
{
	m_transform = AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin)
	: m_name(origin.m_name)
	, m_layer(LAYER_TYPE::NONE)
	, m_renderComponent(nullptr)
	, m_collider(nullptr)
	, m_parent(nullptr)
{
	*this = origin;
}

GameObject::~GameObject()
{
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this != &other)
	{
		auto pObj = Ptr<GameObject>(this);

		// 기본 엔진 컴포넌트 복제
		for (auto& component : other.m_components)
		{
			auto& origin = component.second;
			m_components.insert(make_pair(component.first, origin->Clone(origin, pObj)));
		}

		m_renderComponent = GetComponent<RenderComponent>();
		m_transform = GetComponent<Transform>();

		// 사용자 정의 컴포넌트 복제
		m_scripts.resize(other.m_scripts.size());
		for (int i = 0; i < m_scripts.size(); ++i)
		{
			auto& origin = other.m_scripts[i];
			m_scripts[i] = origin->Clone(origin, pObj);
		}

		// 자식 오브젝트 복제
		for (auto& child : other.m_children)
		{
			m_children.push_back(child.DeepCopy());
		}

		// 레이어 설정
		SetLayer(other.m_layer);
	}

	return *this;
}

Ptr<Transform> GameObject::GetTransform()
{
	return m_transform;
}

Ptr<RenderComponent> GameObject::GetRenderComponent()
{
	return m_renderComponent;
}

Ptr<Collider> GameObject::GetCollider()
{
	return m_collider;
}

// TODO : 레벨매니저, 렌더매니저 오브젝트 등록,삭제를 Init() 호출 이전에는 하지 않게 해야함
void GameObject::SetLayer(LAYER_TYPE layer)
{
	if (m_layer == layer) return;

	Ptr<GameObject> obj = Ptr<GameObject>(this);

	if (m_layer != LAYER_TYPE::NONE)
	{
		// 기존 레이어에 등록된 오브젝트 삭제
		LevelManager::GetInstance()->DeleteObject(obj);

		if (m_layer > LAYER_TYPE::CAMERA)
		{
			// 기존 레이어 타입으로 등록된 콜라이더 삭제
			CollisionManager::GetInstance()->RemoveCollider(m_collider);
			// 기존 레이어 타입으로 등록된 메인카메라 렌더맵 삭제
			RenderManager::GetInstance()->DeleteRenderObj(obj);
		}
	}

	m_layer = layer;
	if (m_layer != LAYER_TYPE::NONE)
	{
		// 새로운 레이어에 오브젝트 등록
		LevelManager::GetInstance()->AddObject(obj);

		if (m_layer > LAYER_TYPE::CAMERA)
		{
			// 새로운 레이어 타입으로 콜라이더 등록
			if (m_collider != nullptr)
			{
				CollisionManager::GetInstance()->AddCollider(m_collider);
			}
			// 새로운 레이어 타입으로 메인카메라 렌더맵 등록
			if (m_renderComponent != nullptr)
			{
				RenderManager::GetInstance()->AddRenderObj(obj);
			}
		}
	}
}

void GameObject::AddChild(const Ptr<GameObject>& child, bool isSameLayer)
{
	if(isSameLayer) child->SetLayer(m_layer);
	child->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));	// 디폴트값 : 부모와 같은 크기
	child->m_parent = Ptr<GameObject>(this);
	m_children.push_back(child);
}

void GameObject::Init()
{
	for (auto& component : m_components)
	{
		component.second->Init();
	}

	for (auto& script : m_scripts)
	{
		script->Init();
	}
}

void GameObject::Tick()
{
	for (auto& script : m_scripts)
	{
		script->Tick();
	}
}

void GameObject::FinalTick()
{
	for (auto& component : m_components)
	{
		component.second->FinalTick();
	}
}

void GameObject::Render()
{
	m_renderComponent->Render();
}

void GameObject::OnCollisionEnter(LAYER_TYPE other)
{
	for (auto& script : m_scripts)
	{
		script->OnCollisionEnter(other);
	}
}

void GameObject::OnCollisionStay(LAYER_TYPE other)
{
	for (auto& script : m_scripts)
	{
		script->OnCollisionStay(other);
	}
}

void GameObject::OnCollisionExit(LAYER_TYPE other)
{
	for (auto& script : m_scripts)
	{
		script->OnCollisionExit(other);
	}
}