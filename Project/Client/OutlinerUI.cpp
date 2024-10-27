#include "pch.h"
#include "OutlinerUI.h"
#include "TreeUI.h"

OutlinerUI::OutlinerUI() 
	: EditorUI("OutlinerUI")
	, m_tree(AddChild<TreeUI>())
{
	// TEST
	TreeNode* root = m_tree->AddItem("Root", 0);
	TreeNode* child1 = m_tree->AddItem("child1", 0, root);
	m_tree->AddItem("childchild1", 0, child1);
	m_tree->AddItem("childchild2", 0, child1);
	m_tree->AddItem("child2", 0, root);
}

OutlinerUI::~OutlinerUI()
{
	m_tree = nullptr;
}

void OutlinerUI::RenderUpdate()
{
}
