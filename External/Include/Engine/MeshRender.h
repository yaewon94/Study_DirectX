#pragma once
#include "RenderComponent.h"

class Mesh;

// ·»´õ¸µ ´ã´ç ÄÄÆ÷³ÍÆ®
class MeshRender final : public RenderComponent
{
	NO_COPY_ASSIGN(MeshRender);

private:
	Ptr<Mesh> mesh;

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

public:
	virtual void FinalTick() final {}
	virtual void Render() final;
};