#include "pch.h"
#include "Collider2D.h"
#include "RenderManager.h"
#include "Render.h"
#include "GameObject.h"
#include "Transform.h"

Collider2D::Collider2D(const Ptr<GameObject>& owner)
	: Component(owner)
	, m_offset(Vec3(0.f, 0.f, 0.f))
	, m_scale(GetOwner()->GetTransform()->GetLocalScale())
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
}

void Collider2D::Init()
{
#ifdef _DEBUG
	// 디버그 모드 렌더링 등록
	DebugShapeInfo info = {};
	info.shape = DEBUG_SHAPE::RECT;
	info.color = COLOR_GREEN;
	info.hasDepthTest = false;
	info.pos = GetOwner()->GetTransform()->GetLocalPos() + m_offset;
	info.scale = m_scale;

	// 디버그 오브젝트를 현재 오브젝트의 자식으로 설정
	m_debugObj = RenderManager::GetInstance()->AddDebugShape(info);
	GetOwner()->AddChild(m_debugObj, false);
	m_debugObj->GetTransform()->SetLocalPos(m_offset);
	m_debugObj->GetTransform()->SetLocalScale(m_scale / GetOwner()->GetTransform()->GetLocalScale());
#endif // _DEBUG
}