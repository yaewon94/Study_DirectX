#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Material.h"

Collider::Collider(const Ptr<GameObject>& owner) 
	: Component(owner)

{
}

Collider::Collider(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
}

Collider::~Collider()
{
	// CollisionManager에 등록된 것 제거
	CollisionManager::GetInstance()->RemoveCollider(Ptr<Collider>(this));
}

void Collider::FinalTick()
{
	m_worldMat = m_matScale * m_matTrans * GetOwner()->GetTransform()->GetWorldMatrix();
}

void Collider::OnCollisionEnter(LAYER_TYPE other)
{
#ifdef _DEBUG
	// 디버그 라인 색상 변경
	m_debugObj->GetRenderComponent()->GetMaterial()->SetColor(COLOR_COLLISION);
#endif // _DEBUG

	GetOwner()->OnCollisionEnter(other);
}

void Collider::OnCollisionStay(LAYER_TYPE other)
{
	GetOwner()->OnCollisionStay(other);
}

void Collider::OnCollisionExit(LAYER_TYPE other)
{
#ifdef _DEBUG
	// 디버그 라인 색상 변경
	m_debugObj->GetRenderComponent()->GetMaterial()->SetColor(COLOR_DEFAULT);
#endif // _DEBUG

	GetOwner()->OnCollisionExit(other);
}