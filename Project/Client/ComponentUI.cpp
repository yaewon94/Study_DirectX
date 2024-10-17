#include "pch.h"
#include "ComponentUI.h"
#include "Engine/GameObject.h"
#include "Engine/Component.h"

ComponentUI::ComponentUI(const string& name)
	: EditorUI(name)
{
}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::CallbackCreateSuccess()
{
	if (this->GetComponent() == nullptr)
	{
		this->AddComponent();
	}
}

//void ComponentUI::SetComponentTitle()
//{
//    ImGui::PushID(0);
//
//    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
//    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
//    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
//
//    ImGui::Button(GetName().c_str());
//
//    ImGui::PopStyleColor(3);
//    ImGui::PopID();
//}