#include "pch.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Material.h"

RenderComponent::RenderComponent(const Ptr<GameObject>& owner)
	: Component(owner)
{
}

RenderComponent::RenderComponent(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: Component(origin, owner)
{
	auto component = origin.ptr_dynamic_cast<RenderComponent>();
	m_material = component->m_material;
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::SetMaterial(const Ptr<Material>& material)
{
	m_material = material;
}

Ptr<Material> RenderComponent::GetMaterial()
{
	return m_material;
}