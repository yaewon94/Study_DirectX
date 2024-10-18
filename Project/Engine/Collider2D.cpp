#include "pch.h"
#include "Collider2D.h"
#include "RenderManager.h"
#include "GameObject.h"
#include "Transform.h"

Collider2D::Collider2D(const Ptr<GameObject>& owner)
	: Collider(owner)
	, m_scale(Vec2(1.f, 1.f))
{
}

Collider2D::Collider2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Collider(origin, owner)
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
	m_matScale = XMMatrixScaling(m_scale.x, m_scale.y, 1.f);
	m_matTrans = XMMatrixTranslation(m_offset.x, m_offset.y, 0.f);

#ifdef _DEBUG
	// 디버그 모드 렌더링 등록
	DebugShapeInfo info = {};
	info.pos = Vec3(m_offset.x, m_offset.y, 0.f);
	info.scale = Vec3(m_scale.x, m_scale.y, 0.f);
	info.shape = DEBUG_SHAPE::RECT;
	info.color = COLOR_DEFAULT;
	info.hasDepthTest = false;


	// 디버그 오브젝트를 현재 오브젝트의 자식으로 설정
	RenderManager::GetInstance()->InitDebugShape(m_debugObj, info);
	GetOwner()->AddChild(m_debugObj, false);
#endif // _DEBUG
}

void Collider2D::OnChangeOffset()
{
	m_matTrans = XMMatrixTranslation(m_offset.x, m_offset.y, 0.f);

#ifdef _DEBUG
	RenderManager::GetInstance()->ChangeDebugPos(m_debugObj, Vec3(m_offset.x, m_offset.y, 0.f));
#endif // _DEBUG
}

void Collider2D::OnChangeScale()
{
	m_matScale = XMMatrixScaling(m_scale.x, m_scale.y, 1.f);

#ifdef _DEBUG
	RenderManager::GetInstance()->ChangeDebugScale(m_debugObj, Vec3(m_scale.x, m_scale.y, 1.f));
#endif // _DEBUG
}