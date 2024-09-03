#pragma once
#include "Component.h"

class Mesh;
class GraphicShader;
class Texture;

// ·»´õ¸µ ´ã´ç ÄÄÆ÷³ÍÆ®
class MeshRender final : public Component
{
	NO_COPY_ASSIGN(MeshRender);

private:
	Ptr<Mesh> mesh;
	Ptr<GraphicShader> shader;
	Ptr<Texture> texture;

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
	void SetShader(const Ptr<GraphicShader>& shader);
	void SetTexture(const Ptr<Texture>& texture);

public:
	virtual void FinalTick() final {}
	void Render();
};