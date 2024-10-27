#include "pch.h"
#include "TreeUI.h"

TreeUI::TreeUI() 
	: EditorUI("TreeUI")
{
}

TreeUI::~TreeUI()
{
}

void TreeUI::RenderUpdate()
{
	if (ImGui::TreeNodeEx("TestNode"), ImGuiTreeNodeFlags_Leaf)
	{
		ImGui::TreePop();
	}
}