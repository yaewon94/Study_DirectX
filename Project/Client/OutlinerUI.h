#pragma once
#include "EditorUI.h"

struct TreeNode;
class GameObject;

class OutlinerUI final : public EditorUI
{
private:
	class TreeUI* m_tree;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::OUTLINER;

public:
	OutlinerUI();
	~OutlinerUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }

private:
	void AddGameObject(TreeNode* const parent, Ptr<GameObject> obj);
	void RenewGameObjects();
	void SelectGameObject(TreeNode* const node);
};