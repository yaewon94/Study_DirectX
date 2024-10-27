#include "pch.h"
#include "TreeUI.h"

TreeUI::TreeUI() 
	: EditorUI("TreeUI")
	, m_root(nullptr)
{
}

TreeUI::~TreeUI()
{
	if (m_root != nullptr)
	{
		delete m_root;
		m_root = nullptr;
	}
}

void TreeUI::RenderUpdate()
{
	m_root->RenderUpdate();
}

TreeNode* const TreeUI::AddItem(const string& name, DWORD_PTR data, TreeNode* const parent)
{
	TreeNode* node = new TreeNode;
	node->m_name = name;
	node->m_data = data;

	if (parent == nullptr)
	{
		if (m_root == nullptr) m_root = node;
		else throw std::logic_error("루트노드가 이미 존재합니다");
	}
	else
	{
		parent->AddChild(node);
	}

	return node;
}

TreeNode::TreeNode() 
	: m_data(0), m_parent(nullptr)
{
}

TreeNode::~TreeNode()
{
	m_data = 0;
	m_parent = 0;
	for (auto child : m_children)
	{
		if (child != nullptr)
		{
			delete child;
			child = nullptr;
		}
	}
}

void TreeNode::RenderUpdate()
{
	if (ImGui::TreeNodeEx(m_name.c_str(), ImGuiTreeNodeFlags_Leaf))
	{
		for (auto child : m_children)
		{
			child->RenderUpdate();
		}

		ImGui::TreePop();
	}
}

void TreeNode::AddChild(TreeNode* const child)
{
	// 중복 체크
	for (auto _child : m_children)
	{
		if (child == _child)
		{
			throw std::logic_error("이미 존재하는 노드입니다");
		}
	}

	m_children.push_back(child);
	child->m_parent = this;
}