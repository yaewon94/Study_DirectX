#include "pch.h"
#include "MeshRenderUI.h"
#include "Engine/GameObject.h"
#include "Engine/MeshRender.h"
#include "Engine/Mesh.h"
#include "Engine/Material.h"

ImVec2 MeshRenderUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 2);

MeshRenderUI::MeshRenderUI(Ptr<GameObject> target) 
	: ComponentUI("MeshRender", target)
	, m_meshRender(target->GetComponent<MeshRender>())
{
}

MeshRenderUI::~MeshRenderUI()
{
}

Ptr<Component> MeshRenderUI::AddComponent()
{
	return GetTarget()->AddComponent<MeshRender>().ptr_dynamic_cast<Component>();
}

Ptr<Component> MeshRenderUI::GetComponent(bool isBaseType)
{
	if(isBaseType) return GetTarget()->GetRenderComponent().ptr_dynamic_cast<Component>();
	else return GetTarget()->GetComponent<MeshRender>().ptr_dynamic_cast<Component>();
}

void MeshRenderUI::RenderUpdate()
{
	Ptr<Mesh> mesh = m_meshRender->GetMesh();
	Ptr<Material> material = m_meshRender->GetMaterial();
	string meshName = "None";

	RenderTitle();

	ImGui::Text("Mesh");
	ImGui::SameLine(SAMELINE_VALUE);
	if(mesh != nullptr) meshName = mesh->GetKey();
	ImGui::InputText("##MeshName", (char*)meshName.c_str(), meshName.length(), ImGuiInputTextFlags_::ImGuiInputTextFlags_ReadOnly);
}