#include "pch.h"
#include "Light2D.h"
#include "GameObject.h"
#include "LayerValues.h"
#include "Transform.h"
#include "RenderManager.h"

Light2D::Light2D(const Ptr<GameObject>& owner) 
	: Light(owner)
{
	GetOwner()->SetLayer(LAYER_TYPE::LIGHT);
}

Light2D::Light2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Light(origin, owner)
{
	auto pOrigin = origin.ptr_dynamic_cast<Light2D>();
	m_info = pOrigin->m_info;
	GetOwner()->SetLayer(LAYER_TYPE::LIGHT);
}

Light2D::~Light2D()
{
}

const Light2dInfo& Light2D::GetInfo()
{
	m_info.worldPos = GetOwner()->GetTransform()->GetWorldPos();
	return m_info;
}

// @angle : 0 ~ 360
void Light2D::SetAngle(int angle)
{
	if (angle >= 0) angle %= 360;
	else angle = (angle % -360) + 360;
	m_info.angle = angle * XM_PI / 180.f;
}
void Light2D::Init()
{
	RenderManager::GetInstance()->AddLight2D(Ptr<Light2D>(this));
}

void Light2D::FinalTick()
{
	Ptr<Transform> tr = GetOwner()->GetTransform();

	// 위치정보 갱신
	m_info.worldPos = tr->GetWorldPos();
	m_info.dir = tr->GetWorldDirection(DIRECTION_VEC::RIGHT);
}