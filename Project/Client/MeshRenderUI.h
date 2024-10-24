#pragma once
#include "ComponentUI.h"

class Component;
class GameObject;
class MeshRender;

class MeshRenderUI final : public ComponentUI
{
	NO_COPY_ASSIGN(MeshRenderUI);

private:
	static ImVec2 s_childSize;
	Ptr<MeshRender> m_meshRender;

public:
	MeshRenderUI(Ptr<GameObject> target);
	~MeshRenderUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::MESH_RENDER; }

	virtual Ptr<Component> AddComponent() final;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) final;

	virtual ImVec2 GetChildSize() final { return s_childSize; }

public:
	virtual void RenderUpdate() final;

private:
	void OnSelectMesh(void* _name);
	void OnSelectMaterial(void* _name);
};