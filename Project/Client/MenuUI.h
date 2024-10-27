#pragma once
#include "EditorUI.h"

// \Engine\Entity ��ü�� ������ �� �ִ� UI
class MenuUI final : public EditorUI
{
public:
	MenuUI();
	~MenuUI();

public:
	virtual void Render() final;
	virtual void RenderUpdate() final {}

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::MENU; }

private:
	void MenuAsset();
	void MenuEditor();
	void MenuFile();
	void MenuGameObject();
	void MenuLevel();
};