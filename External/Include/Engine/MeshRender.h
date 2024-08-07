#pragma once
#include "Component.h"
#include "Mesh.h"
#include "GraphicShader.h"

// 메쉬, 그래픽셰이더 렌더링 담당 컴포넌트
class MeshRender final : public Component
{
	NO_COPY_ASSIGN(MeshRender);
	friend class GameObject;

private:
	const static COMPONENT_TYPE Type = COMPONENT_TYPE::MESH_RENDER;

private:
	Ptr<Mesh> mesh;
	Ptr<GraphicShader> shader;

private:
	MeshRender(const GameObject& Owner);
	MeshRender(const MeshRender& origin, const GameObject& Owner);
	~MeshRender();
	virtual MeshRender* Clone(const GameObject& Owner) final { return new MeshRender(*this, Owner); }

private:
	void SetMesh(Ptr<Mesh> mesh) { this->mesh = mesh; }
	void SetShader(Ptr<GraphicShader> shader) { this->shader = shader; }

private:
	virtual void FinalTick() final;
	void Render();
};