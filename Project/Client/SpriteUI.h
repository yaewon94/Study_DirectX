#pragma once
#include "AssetUI.h"

class Sprite;

class SpriteUI final : public AssetUI
{
	NO_COPY_ASSIGN(SpriteUI);

public:
	static constexpr auto Type = EDITOR_UI_TYPE::SPRITE;

private:
	static constexpr auto ChildSize = ImVec2(0, CHILDSIZE_ROW * 4);
	Ptr<Sprite> m_sprite;

public:
	SpriteUI();
	~SpriteUI();

	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	virtual ImVec2 GetChildSize() final { return ChildSize; }

	virtual void RenderUpdate() final;
};