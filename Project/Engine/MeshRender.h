#pragma once
#include "Component.h"

class Mesh;
class Material;

// ·»´õ¸µ ´ã´ç ÄÄÆ÷³ÍÆ®
class MeshRender final : public Component
{
	NO_COPY_ASSIGN(MeshRender);

private:
	Ptr<Mesh> mesh;
	Ptr<Material> material;

public:
	MeshRender(const Ptr<GameObject>& owner);
	MeshRender(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~MeshRender();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<MeshRender>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	void SetMesh(const Ptr<Mesh>& mesh);
	void SetMaterial(const Ptr<Material>& material);
	Ptr<Material> GetMaterial();

public:
	virtual void FinalTick() final {}
	void Render();
};