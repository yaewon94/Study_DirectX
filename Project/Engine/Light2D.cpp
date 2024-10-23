#include "pch.h"
#include "Light2D.h"
#include "GameObject.h"
#include "LayerValues.h"
#include "Transform.h"
#include "RenderManager.h"

Light2D::Light2D(const Ptr<GameObject>& owner) 
	: Light(owner)
	, m_info{}, m_dirType(DIRECTION_2D::LEFT)
{
}

Light2D::Light2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Light(origin, owner)
{
	auto pOrigin = origin.ptr_dynamic_cast<Light2D>();
	m_info = pOrigin->m_info;
	m_dirType = pOrigin->m_dirType;
}

Light2D::~Light2D()
{
}

// @angle : 0 ~ 90
void Light2D::SetAngle(int angle)
{
	if (angle >= 0) angle %= 90;
	else angle = (angle % -90) + 90;
	m_info.angle = angle * XM_PI / 180.f;
}

void Light2D::SetRadius(float radius)
{
	if (radius < 0.f) throw std::logic_error("radius값은 양수여야 합니다");
	m_info.radius = radius;
}

void Light2D::Init()
{
	RenderManager::GetInstance()->AddLight2D(Ptr<Light2D>(this));
}

void Light2D::FinalTick()
{
	// TODO : 좌표 바뀔때만 호출하도록 구현
	m_info.worldPos = GetOwner()->GetTransform()->GetWorldPos();
}