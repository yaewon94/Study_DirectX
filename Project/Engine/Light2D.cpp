#include "pch.h"
#include "Light2D.h"
#include "GameObject.h"
#include "LayerEnums.h"
#include "Transform.h"
#include "TransformEnums.h"
#include "RenderManager.h"

Light2D::Light2D(const Ptr<GameObject>& owner) 
	: Component(owner)
{
	GetOwner()->SetLayer(LAYER_TYPE::LIGHT);
}

Light2D::Light2D(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
	auto pOrigin = origin.ptr_dynamic_cast<Light2D>();
	m_info = pOrigin->m_info;
	GetOwner()->SetLayer(LAYER_TYPE::LIGHT);
}

Light2D::~Light2D()
{
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