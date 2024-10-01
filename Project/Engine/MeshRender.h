#pragma once
#include "RenderComponent.h"

class Mesh;

// ·»´õ¸µ ´ã´ç ÄÄÆ÷³ÍÆ®
class MeshRender : public RenderComponent
{
	NO_COPY_ASSIGN(MeshRender);

private:
	Ptr<Mesh> mesh;

public:
	MeshRender(const Ptr<GameObject>& owner);
	MeshRender(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~MeshRender();

	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) override
	{
		return Ptr<MeshRender>(origin, owner).ptr_dynamic_cast<Component>();
	}

public:
	Ptr<Mesh> GetMesh();
	void SetMesh(const Ptr<Mesh>& mesh);

public:
	virtual void FinalTick() override {}
	virtual void Render() override;
};