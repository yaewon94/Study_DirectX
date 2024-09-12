#pragma once
#include "Component.h"

class Material;

// ·»´õ¸µ ´ã´ç ÄÄÆ÷³ÍÆ®
class RenderComponent : public Component
{
protected:
	Ptr<Material> m_material;

protected:
	RenderComponent(const Ptr<GameObject>& owner);
	RenderComponent(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~RenderComponent();

public:
	void SetMaterial(const Ptr<Material>& material);

public:
	Ptr<Material> GetMaterial();

public:
	virtual void Render() = 0;
};