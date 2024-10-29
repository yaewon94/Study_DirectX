#include "pch.h"
#include "MeshUI.h"
#include "InspectorUI.h"
#include "Engine/Mesh.h"

MeshUI::MeshUI() : AssetUI("Mesh")
{
	m_mesh = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetAsset().ptr_dynamic_cast<Mesh>();
}

MeshUI::~MeshUI()
{
}

void MeshUI::RenderUpdate()
{
	constexpr auto SAMELINE_OFFSET = 50;

	RenderTitle();

	// 각 인덱스 정보
	const int IdxCnt = m_mesh->GetIndexCount();
	const UINT* const IdxInfo = m_mesh->GetIndexInfo();
	ImGui::Text("Index");
	ImGui::BeginTable("##mesh_idx_table", 10);
	for (int i = 0; i < IdxCnt; ++i)
	{
		ImGui::TableNextColumn();
		ImGui::InputInt("##mesh_idx", (int*)(&IdxInfo[i]), 0, 0, ImGuiInputTextFlags_ReadOnly);
	}
	ImGui::EndTable();

	// 각 정점 정보
	const int VertexCnt = m_mesh->GetVertexCount();
	ImGui::Text("Vertex");
	ImGui::BeginGroup();
	for (int i = 0; i < VertexCnt; ++i)
	{
		Vertex info = m_mesh->GetVertexInfo(i);

		//char fmt[] = {'[', i+'0', ']', '\0'};
		string fmt = "[" + std::to_string(i) + "]";
		ImGui::TextDisabled(fmt.c_str());
		ImGui::SameLine();

		ImGui::BeginGroup();
			ImGui::TextDisabled("pos");
			ImGui::SameLine(SAMELINE_OFFSET);
			ImGui::SetNextItemWidth(180);
			ImGui::InputFloat3("##mesh_vtxPos", info.pos, "%.1f", ImGuiInputTextFlags_ReadOnly);

			ImGui::TextDisabled("uv");
			ImGui::SameLine(SAMELINE_OFFSET);
			ImGui::SetNextItemWidth(120);
			ImGui::InputFloat2("##mesh_vtxUV", info.uv, "%.1f", ImGuiInputTextFlags_ReadOnly);

			ImGui::TextDisabled("color");
			ImGui::SameLine(SAMELINE_OFFSET);
			ImGui::SetNextItemWidth(240);
			ImGui::InputFloat4("##mesh_vtxColor", info.color, "%.1f", ImGuiInputTextFlags_ReadOnly);
		ImGui::EndGroup();


		//ImGui::SetColumnOffset();
		//ImGui::SetColumnWidth();
	}
	ImGui::EndGroup();
}