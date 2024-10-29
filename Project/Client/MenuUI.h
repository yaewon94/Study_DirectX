#pragma once
#include "EditorUI.h"

// \Engine\Entity 개체를 편집할 수 있는 UI
class MenuUI final : public EditorUI
{
public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::MENU;

public:
	MenuUI();
	~MenuUI();

public:
	virtual void Render() final;
	virtual void RenderUpdate() final {}

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }
	
private:
	void MenuAsset();
	void MenuEditor();
	void MenuFile();
	void MenuGameObject();
	void MenuLevel();
};