#pragma once
#include "AssetUI.h"

class Material;

class MaterialUI final : public AssetUI
{
	NO_COPY_ASSIGN(MaterialUI);

public:
	static constexpr auto Type = EDITOR_UI_TYPE::MATERIAL;

private:
	static constexpr auto ChildSize = ImVec2(0, CHILDSIZE_ROW * 10);
	Ptr<Material> m_mtrl;

public:
	MaterialUI();
	~MaterialUI();

	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	virtual ImVec2 GetChildSize() final { return ChildSize; }

	virtual void RenderUpdate() final;
};