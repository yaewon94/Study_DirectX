#include "pch.h"
#include "TreeUI.h"

//#define DEFAULT_TREE_FLAGS ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick
#define DEFAULT_TREE_FLAGS ImGuiTreeNodeFlags_Leaf

TreeUI::TreeUI() 
	: EditorUI("TreeUI")
	, m_root(nullptr), m_selected(nullptr)
	, m_onSelectCallbackInst(nullptr), m_onSelectCallbackFunc(nullptr)
{
}

TreeUI::~TreeUI()
{
	ClearItems();
	m_root = nullptr;
	m_selected = nullptr;
	m_onSelectCallbackInst = nullptr;
}

void TreeUI::RenderUpdate()
{
	m_root->RenderUpdate();
}

TreeNode* const TreeUI::AddItem(const string& name, DWORD_PTR data, TreeNode* const parent)
{
	TreeNode* node = new TreeNode;
	node->m_owner = this;
	node->m_name = name;
	node->m_data = data;

	if (parent == nullptr)
	{
		if (m_root == nullptr)
		{
			m_root = node;
		}
		else
		{
			delete node;
			node = nullptr;
			throw std::logic_error("��Ʈ��尡 �̹� �����մϴ�");
		}
	}
	else
	{
		parent->AddChild(node);
	}

	return node;
}

void TreeUI::ClearItems()
{
	if (m_root)
	{
		delete m_root;
		m_root = nullptr;
	}
}

void TreeUI::SelectNode(TreeNode* const node)
{
	if(m_selected != nullptr) m_selected->m_isSelected = false;
	m_selected = node;
	m_selected->m_isSelected = true;

	if (m_onSelectCallbackInst != nullptr && m_onSelectCallbackFunc != nullptr)
	{
		(m_onSelectCallbackInst->*m_onSelectCallbackFunc)(m_selected);
	}
}

TreeNode::TreeNode() 
	: m_owner(nullptr), m_data(0), m_parent(nullptr), m_isSelected(false)
{
}

TreeNode::~TreeNode()
{
	m_owner = nullptr;
	m_data = 0;
	m_parent = nullptr;
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
	// TODO : ���� ������ �ִ� Ʈ���� ���� �÷��� ������ ����
	// �÷��� ����
	ImGuiTreeNodeFlags flags = DEFAULT_TREE_FLAGS;
	if (!m_children.empty()) flags |= ImGuiTreeNodeFlags_Framed;
	else if (m_isSelected) flags |= ImGuiTreeNodeFlags_Selected;	// ��������̸鼭 ���õ� ��

	// �ڽĳ����� Ʈ�������� ������
	if (ImGui::TreeNodeEx(m_name.c_str(), flags))
	{
		// ���콺 ���ʹ�ư Ŭ����, ��� ����
		if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			m_owner->SelectNode(this);
		}

		// �ڽĳ�� ������ ȣ��
		for (auto child : m_children)
		{
			child->RenderUpdate();
		}

		ImGui::TreePop();
	}
}

void TreeNode::AddChild(TreeNode* const child)
{
	// �ߺ� üũ
	for (auto _child : m_children)
	{
		if (child == _child)
		{
			throw std::logic_error("�̹� �����ϴ� ����Դϴ�");
		}
	}

	m_children.push_back(child);
	child->m_parent = this;
}