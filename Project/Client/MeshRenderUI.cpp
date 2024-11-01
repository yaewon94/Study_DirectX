#include "pch.h"
#include "MeshRenderUI.h"
#include "InspectorUI.h"
#include "ListUI.h"
#include "Engine/GameObject.h"
#include "Engine/AssetManager.h"
#include "Engine/MeshRender.h"
#include "Engine/Mesh.h"
#include "Engine/Material.h"

ImVec2 MeshRenderUI::s_childSize = ImVec2(0, CHILDSIZE_ROW * 2);

MeshRenderUI::MeshRenderUI() 
	: ComponentUI("MeshRender")
{
	m_meshRender = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetObject()->GetComponent<MeshRender>();
}

MeshRenderUI::~MeshRenderUI()
{
}

//Ptr<Component> MeshRenderUI::AddComponent()
//{
//	return GetTarget()->AddComponent<MeshRender>().ptr_dynamic_cast<Component>();
//}
//
//Ptr<Component> MeshRenderUI::GetComponent(bool isBaseType)
//{
//	if(isBaseType) return GetTarget()->GetRenderComponent().ptr_dynamic_cast<Component>();
//	else return GetTarget()->GetComponent<MeshRender>().ptr_dynamic_cast<Component>();
//}

void MeshRenderUI::RenderUpdate()
{
	RenderTitle();

	// Mesh
	string meshName = "null";
	Ptr<Mesh> mesh = m_meshRender->GetMesh();
	if (mesh != nullptr) meshName = mesh->GetKey();
	ImGui::Text("Mesh");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::BeginCombo("##meshRender_mesh", meshName.c_str()))
	{
		for (auto& pair : AssetManager::GetInstance()->GetAssets(ASSET_TYPE::MESH))
		{
			if (ImGui::Selectable(pair.first.c_str(), mesh.Get() == pair.second.Get()))
			{
				m_meshRender->SetMesh(pair.second.ptr_dynamic_cast<Mesh>());
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}

	// Material
	string mtrlName = "null";
	Ptr<Material> mtrl = m_meshRender->GetMaterial();
	if (mtrl != nullptr) mtrlName = mtrl->GetKey();
	ImGui::Text("Material");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::BeginCombo("##meshRender_mtrl", mtrlName.c_str()))
	{
		for (auto& pair : AssetManager::GetInstance()->GetAssets(ASSET_TYPE::MATERIAL))
		{
			if (ImGui::Selectable(pair.first.c_str(), mtrl.Get() == pair.second.Get()))
			{
				m_meshRender->SetMaterial(pair.second.ptr_dynamic_cast<Material>());
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
}

void MeshRenderUI::OnSelectMesh(void* _name)
{
	string* name = (string*)(_name);

	if (*name != "None")
	{
		m_meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(*name));
	}
	else
	{
		m_meshRender->SetMesh(nullptr);
	}
}

void MeshRenderUI::OnSelectMaterial(void* _name)
{
	string* name = (string*)(_name);

	if (*name != "None")
	{
		m_meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(*name));
	}
	else
	{
		m_meshRender->SetMaterial(nullptr);
	}
}