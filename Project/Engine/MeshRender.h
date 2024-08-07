#pragma once
#include "Component.h"
#include "Mesh.h"
#include "GraphicShader.h"

// 메쉬, 그래픽셰이더 렌더링 담당 컴포넌트
class MeshRender final : public Component
{
	NO_COPY_ASSIGN(MeshRender);

private:
	Ptr<Mesh> mesh;
	Ptr<GraphicShader> shader;

private:
	template<typename T> requires std::derived_from<T, Component>
	friend static T* Component::Create(const GameObject& Owner);

	MeshRender(const GameObject& Owner);
	MeshRender(const MeshRender& origin, const GameObject& Owner);
	~MeshRender();

public:
	virtual MeshRender* Clone(const GameObject& Owner) final { return new MeshRender(*this, Owner); }

public:
	void SetMesh(const Ptr<Mesh>& mesh) { this->mesh = mesh; }
	void SetShader(const Ptr<GraphicShader>& shader) { this->shader = shader; }

public:
	virtual void FinalTick() final;
	void Render();
};