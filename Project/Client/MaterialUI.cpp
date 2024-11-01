#include "pch.h"
#include "MaterialUI.h"
#include "InspectorUI.h"
#include "Engine/Material.h"
#include "Engine/AssetManager.h"
#include "Engine/GraphicShader.h"
#include "Engine/Texture.h"

MaterialUI::MaterialUI() : AssetUI("Material")
{
	m_mtrl = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetAsset().ptr_dynamic_cast<Material>();
}

MaterialUI::~MaterialUI()
{
}

void MaterialUI::RenderUpdate()
{
	RenderTitle();

	// Graphic Shader
	ImGui::Text("Graphic Shader");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::BeginCombo("##mtrl_gsShader", m_mtrl->GetShader()->GetKey().c_str()))
	{
		for (auto& pair : AssetManager::GetInstance()->GetAssets(ASSET_TYPE::GRAPHIC_SHADER))
		{
			if (ImGui::Selectable(pair.first.c_str(), m_mtrl->GetShader().Get() == pair.second.Get()))
			{
				m_mtrl->SetShader(pair.second.ptr_dynamic_cast<GraphicShader>());
				ImGui::SetItemDefaultFocus();
			}
		}

		ImGui::EndCombo();
	}

	// const buffer
	// TODO : shader별 const buffer 상수이름 출력하기 (ex. alphablend : (alpha == cb.float0)
	ImGui::Text("Const buffer");
	CB_Material cb = m_mtrl->GetConstBuffer();

	ImGui::TextDisabled("int");
	ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
	ImGui::BeginTable("##mtrl_cb_int", 4);
	for (int i=0; i < sizeof(cb.iArr)/sizeof(int); ++i)
	{
		ImGui::TableNextColumn();
		string idx = "[" + std::to_string(i) + "]";
		ImGui::TextDisabled(idx.c_str());
		ImGui::SameLine();
		if (ImGui::InputInt(("##mtrl_cb_int"+idx).c_str(), &cb.iArr[i], 0, 0))
		{
			m_mtrl->SetScalarParam<int>((SCALAR_PARAM)(INT_0+i), cb.iArr[i]);
		}
	}
	ImGui::EndTable();

	ImGui::TextDisabled("float");
	ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
	ImGui::BeginTable("##mtrl_cb_float", 4);
	for (int i = 0; i < sizeof(cb.fArr)/sizeof(float); ++i)
	{
		ImGui::TableNextColumn();
		string idx = "[" + std::to_string(i) + "]";
		ImGui::TextDisabled(idx.c_str());
		ImGui::SameLine();
		if (ImGui::InputFloat(("##mtrl_cb_float"+idx).c_str(), &cb.fArr[i]))
		{
			m_mtrl->SetScalarParam<float>((SCALAR_PARAM)(FLOAT_0 + i), cb.fArr[i]);
		}
	}
	ImGui::EndTable();

	ImGui::TextDisabled("vec2");
	ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
	ImGui::BeginTable("##mtrl_cb_vec2", 2);
	for (int i = 0; i < sizeof(cb.v2Arr)/sizeof(Vec2); ++i)
	{
		ImGui::TableNextColumn();
		string idx = "[" + std::to_string(i) + "]";
		ImGui::TextDisabled(idx.c_str());
		ImGui::SameLine();
		if (ImGui::InputFloat2(("##mtrl_cb_vec2"+idx).c_str(), cb.v2Arr[i]))
		{
			m_mtrl->SetScalarParam<Vec2>((SCALAR_PARAM)(VEC2_0 + i), cb.v2Arr[i]);
		}
	}
	ImGui::EndTable();

	ImGui::TextDisabled("vec4");
	ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
	ImGui::BeginTable("##mtrl_cb_vec4", 1);
	for (int i = 0; i < sizeof(cb.v4Arr) / sizeof(Vec4); ++i)
	{
		ImGui::TableNextColumn();
		string idx = "[" + std::to_string(i) + "]";
		ImGui::TextDisabled(idx.c_str());
		ImGui::SameLine();
		if (ImGui::InputFloat4(("##mtrl_cb_vec4"+idx).c_str(), cb.v4Arr[i]))
		{
			m_mtrl->SetScalarParam<Vec4>((SCALAR_PARAM)(VEC4_0 + i), cb.v4Arr[i]);
		}
	}
	ImGui::EndTable();

	ImGui::TextDisabled("matrix");
	ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
	ImGui::BeginTable("##mtrl_cb_matrix", 1);
	for (int i = 0; i < sizeof(cb.matrixArr) / sizeof(Matrix); ++i)
	{
		ImGui::TableNextColumn();
		string idx = "[" + std::to_string(i) + "]";
		ImGui::TextDisabled(idx.c_str());
		ImGui::SameLine();
		ImGui::BeginTable(("##mtrl_cb_matrix"+idx).c_str(), 4);
		float* value = &(cb.matrixArr[i]._11);
		for (int row = 0; row < sizeof(cb.matrixArr[i])/sizeof(Vec4); ++row)
		{
			for (int col = 0; col < sizeof(Vec4)/sizeof(float); ++col)
			{
				ImGui::TableNextColumn();
				string label = "##mtrl_cb_matrix" + std::to_string(i) + std::to_string(row) + std::to_string(col);
				if (ImGui::InputFloat(label.c_str(), value))
				{
					m_mtrl->SetScalarParam<Matrix>((SCALAR_PARAM)(MATRIX_0 + i), cb.matrixArr[i]);
				}

				++value;
			}
		}
		ImGui::EndTable();
	}
	ImGui::EndTable();

	//// Textures
	//// 얘는 텍스처끼리 렌더링하면서 레지스터 번호 공유하는거라 안넣어야 될듯?
	//ImGui::Text("Textures");
	//for (int i = 0; i < TEXTURE_PARAM::COUNT_END; ++i)
	//{
	//	string idx = "[" + std::to_string(i) + "]";
	//	ImGui::TextDisabled(idx.c_str());
	//	ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);

	//	const char* name = "null\0";
	//	if (m_mtrl->GetTexture((TEXTURE_PARAM)i) != nullptr) name = m_mtrl->GetTexture((TEXTURE_PARAM)i)->GetKey().c_str();
	//	
	//	string comboLabel = "##mtrl_tex" + std::to_string(i);
	//	if (ImGui::BeginCombo(comboLabel.c_str(), name))
	//	{
	//		for (auto& pair : AssetManager::GetInstance()->GetAssets(ASSET_TYPE::TEXTURE))
	//		{
	//			if (ImGui::Selectable(pair.first.c_str(), m_mtrl->GetTexture((TEXTURE_PARAM)i).Get() == pair.second.Get()))
	//			{
	//				m_mtrl->SetTextureParam((TEXTURE_PARAM)i, pair.second.ptr_dynamic_cast<Texture>());
	//				ImGui::SetItemDefaultFocus();
	//			}
	//		}

	//		ImGui::EndCombo();
	//	}
	//}	
}