#pragma once
#include "EditorUI.h"

class ContentUI final : public EditorUI
{
private:
	class TreeUI* m_tree;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::CONTENT;

public:
	ContentUI();
	~ContentUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }
};