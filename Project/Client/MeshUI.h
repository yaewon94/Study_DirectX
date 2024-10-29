#pragma once
#include "AssetUI.h"

class Mesh;

class MeshUI final : public AssetUI
{
	NO_COPY_ASSIGN(MeshUI);

public:
	static constexpr auto Type = EDITOR_UI_TYPE::MESH;

private:
	static constexpr auto ChildSize = ImVec2(0, CHILDSIZE_ROW * 11);
	Ptr<Mesh> m_mesh;

public:
	MeshUI();
	~MeshUI();

	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	virtual ImVec2 GetChildSize() final { return ChildSize; }

	virtual void RenderUpdate() final;
};