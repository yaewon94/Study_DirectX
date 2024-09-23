#include "pch.h"
#include "Collider2D.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "Render.h"
#include "GameObject.h"
#include "Transform.h"

Collider2D::Collider2D(const Ptr<GameObject>& owner)
	: Component(owner)
	, m_scale(Vec2(1.f, 1.f))
#ifdef _DEBUG
	, m_debugObj(nullptr)
#endif // _DEBUG

{
}

Collider2D::Collider2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(owner)
#ifdef _DEBUG
	, m_debugObj(nullptr)
#endif // _DEBUG
{
	auto _origin = origin.ptr_dynamic_cast<Collider2D>();
	m_offset = _origin->m_offset;
	m_scale = _origin->m_scale;
}

Collider2D::~Collider2D()
{
	// CollisionManager에 등록된 것 제거
	CollisionManager::GetInstance()->RemoveCollider(Ptr<Collider2D>(this));
}

void Collider2D::Init()
{
	// 멤버 초기화 (TODO : 필드값 변경될때마다 호출되도록 구현)
	m_matScale = XMMatrixScaling(m_scale.x, m_scale.y, 1.f);
	m_matTrans = XMMatrixTranslation(m_offset.x, m_offset.y, 0.f);

	// CollisionManager에 등록
	CollisionManager::GetInstance()->AddCollider(Ptr<Collider2D>(this));

#ifdef _DEBUG
	// 디버그 모드 렌더링 등록
	DebugShapeInfo info = {};
	info.shape = DEBUG_SHAPE::RECT;
	info.color = COLOR_GREEN;
	info.hasDepthTest = false;

	// 디버그 오브젝트를 현재 오브젝트의 자식으로 설정
	m_debugObj = RenderManager::GetInstance()->AddDebugShape(info);
	GetOwner()->AddChild(m_debugObj, false);
	m_debugObj->GetTransform()->SetLocalPos(Vec3(m_offset.x, m_offset.y, 0.f));
	m_debugObj->GetTransform()->SetLocalScale(Vec3(m_scale.x, m_scale.y, 0.f));
#endif // _DEBUG
}

void Collider2D::FinalTick()
{
	m_worldMat = m_matScale * m_matTrans * GetOwner()->GetTransform()->GetWorldMatrix();
}