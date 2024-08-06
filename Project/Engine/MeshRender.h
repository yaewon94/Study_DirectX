#pragma once
#include "Component.h"

class MeshRender final : public Component
{
	NO_COPY_ASSIGN(MeshRender);
	friend class GameObject;

private:
	const static COMPONENT_TYPE Type = COMPONENT_TYPE::MESH_RENDER;

private:
	MeshRender(const GameObject& Owner);
	MeshRender(const MeshRender& origin, const GameObject& Owner);
	~MeshRender();

private:
	virtual MeshRender* Clone(const GameObject& Owner) final { return new MeshRender(*this, Owner); }
};