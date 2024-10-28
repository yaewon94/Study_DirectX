#pragma once
#include "EditorUI.h"

// Ʈ�����
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

// Ʈ�� ������ UI
class TreeUI final : public EditorUI
{
	friend struct TreeNode;

private:
	TreeNode* m_root;
	TreeNode* m_selected;

	EditorUI* m_onSelectCallbackInst;
	EUI_CALLBACK m_onSelectCallbackFunc;

public:
	TreeUI();
	~TreeUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::TREE; }

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