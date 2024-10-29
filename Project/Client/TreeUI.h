#pragma once
#include "EditorUI.h"

// 트리노드
struct TreeNode
{
	friend class TreeUI;

private:
	class TreeUI* m_owner;
	string m_name;
	DWORD_PTR m_data;

	TreeNode* m_parent;
	vector<TreeNode*> m_children;

	bool m_isSelected;

	TreeNode();
	~TreeNode();

	void RenderUpdate();
	void AddChild(TreeNode* const child);

public:
	DWORD_PTR GetData() { return m_data; }
};

// 트리 형태의 UI
class TreeUI final : public EditorUI
{
	friend struct TreeNode;

private:
	TreeNode* m_root;
	TreeNode* m_selected;

	EditorUI* m_onSelectCallbackInst;
	EUI_CALLBACK m_onSelectCallbackFunc;

public:
	static const EDITOR_UI_TYPE Type = EDITOR_UI_TYPE::TREE;

public:
	TreeUI();
	~TreeUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return Type; }

	TreeNode* const AddItem(const string& name, DWORD_PTR data, TreeNode* const parent = nullptr);
	void ClearItems();

	void SetOnSelectCallback(EditorUI* const ui, EUI_CALLBACK func)
	{
		m_onSelectCallbackInst = ui;
		m_onSelectCallbackFunc = func;
	}

private:
	void SelectNode(TreeNode* const node);
};