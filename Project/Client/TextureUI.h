#pragma once
#include "AssetUI.h"

class Texture;

class TextureUI final : public AssetUI
{
	NO_COPY_ASSIGN(TextureUI);

public:
	static constexpr auto Type = EDITOR_UI_TYPE::TEXTURE;

private:
	static constexpr auto ChildSize = ImVec2(0, CHILDSIZE_ROW * 7);
	Ptr<Texture> m_tex;

public:
	TextureUI();
	~TextureUI();

	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	virtual ImVec2 GetChildSize() final { return ChildSize; }

	virtual void RenderUpdate() final;
};