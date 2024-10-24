#include "pch.h"
#include "MeshRenderUI.h"
#include "ImguiManager.h"
#include "ListUI.h"
#include "Engine/GameObject.h"
#include "Engine/AssetManager.h"
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
	RenderTitle();

	// Mesh
	string meshName = "None";
	Ptr<Mesh> mesh = m_meshRender->GetMesh();
	if (mesh != nullptr) meshName = mesh->GetKey();
	ImGui::Text("Mesh");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::SetNextItemWidth(150);
	ImGui::InputText("##mesh", (char*)meshName.c_str(), meshName.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Select##mesh"))
	{
		ListUI* ui = (ListUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::LIST);
		ui->SetActive(true);
		ui->AddItem("None");
		vector<const char*> vec;
		AssetManager::GetInstance()->GetAssetNames(ASSET_TYPE::MESH, vec);
		for (auto item : vec)
		{
			ui->AddItem(item);
		}
		ui->SetDoubleClick(*this, (EUI_CALLBACK)&MeshRenderUI::OnSelectMesh);
	}

	// Material
	string mtrlName = "None";
	Ptr<Material> mtrl = m_meshRender->GetMaterial();
	if (mtrl != nullptr) mtrlName = mtrl->GetKey();
	ImGui::Text("Material");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::SetNextItemWidth(150);
	ImGui::InputText("##material", (char*)mtrlName.c_str(), mtrlName.length(), ImGuiInputTextFlags_ReadOnly);
	ImGui::SameLine();
	if (ImGui::Button("Select##material"))
	{
		ListUI* ui = (ListUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::LIST);
		ui->SetActive(true);
		ui->AddItem("None");
		vector<const char*> vec;
		AssetManager::GetInstance()->GetAssetNames(ASSET_TYPE::MATERIAL, vec);
		for (auto item : vec)
		{
			ui->AddItem(item);
		}
		ui->SetDoubleClick(*this, (EUI_CALLBACK)&MeshRenderUI::OnSelectMaterial);
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