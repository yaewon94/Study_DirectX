#pragma once
#include "EditorUI.h"

// 트리노드
struct TreeNode
{
	friend class TreeUI;

private:
	string m_name;
	DWORD_PTR m_data;

	TreeNode* m_parent;
	vector<TreeNode*> m_children;

	TreeNode();
	~TreeNode();

	void RenderUpdate();
	void AddChild(TreeNode* const child);
};

// 트리 형태의 UI
class TreeUI final : public EditorUI
{
private:
	TreeNode* m_root;

public:
	TreeUI();
	~TreeUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::TREE; }
	TreeNode* const AddItem(const string& name, DWORD_PTR data, TreeNode* const parent = nullptr);
};