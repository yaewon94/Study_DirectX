#pragma once
#include "Component.h"

class Material;

// ·»´õ¸µ ´ã´ç ÄÄÆ÷³ÍÆ®
class RenderComponent : public Component
{
	NO_COPY_ASSIGN(RenderComponent);

protected:
	Ptr<Material> m_material;

protected:
	RenderComponent(const Ptr<GameObject>& owner);
	RenderComponent(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~RenderComponent();

public:
	void SetMaterial(const Ptr<Material>& material);
	Ptr<Material> GetMaterial();

	virtual COMPONENT_TYPE GetBaseType() final { return COMPONENT_TYPE::RENDER; }

public:
	virtual void FinalTick() override {}
	virtual void Render() = 0;
};