#pragma once
#include "EditorUI.h"

struct TreeNode;
class GameObject;

class OutlinerUI final : public EditorUI
{
private:
	class TreeUI* m_tree;

public:
	OutlinerUI();
	~OutlinerUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::OUTLINER; }

private:
	void AddGameObject(TreeNode* const parent, Ptr<GameObject> obj);
	void RenewGameObjects();
	void SelectGameObject(TreeNode* const node);
};