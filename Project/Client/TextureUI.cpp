#include "pch.h"
#include "TextureUI.h"
#include "InspectorUI.h"
#include "Engine/Texture.h"

TextureUI::TextureUI() : AssetUI("Texture")
{
	m_tex = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetAsset().ptr_dynamic_cast<Texture>();
}

TextureUI::~TextureUI()
{
}

void TextureUI::RenderUpdate()
{
	RenderTitle();

	// view (bindflags)
	ImGui::Text("View");
	ImGui::SameLine(MAIN_TITLE_SAMELINE_VALUE);
	ImGui::BeginGroup();
		ImGui::Selectable("Shader Resource", m_tex->GetShaderResourceView(), ImGuiSelectableFlags_Disabled);
		ImGui::Selectable("Render Target", m_tex->GetRenderTargetView(), ImGuiSelectableFlags_Disabled);
		ImGui::Selectable("Depth Stencil", m_tex->GetDepthStencilView(), ImGuiSelectableFlags_Disabled);
	ImGui::EndGroup();
	ImGui::NewLine();

	// Å©±â
	ImGui::Text("Size");
	ImGui::SameLine(MAIN_TITLE_SAMELINE_VALUE);
	ImGui::BeginGroup();
		int width = m_tex->GetWidth();
		ImGui::TextDisabled("width");
		ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
		ImGui::InputInt("##width", &width, 0, 0, ImGuiInputTextFlags_ReadOnly);

		int height = m_tex->GetHeight();
		ImGui::TextDisabled("height");
		ImGui::SameLine(SMALL_TITLE_SAMELINE_VALUE);
		ImGui::InputInt("##height", &height, 0, 0, ImGuiInputTextFlags_ReadOnly);
	ImGui::EndGroup();
	ImGui::NewLine();

	// Image
	ImGui::Text("Image");
	int imgWidth = 400;
	int imgHeight = imgWidth * (height / (float)width);
	ImGui::Image(m_tex->GetShaderResourceView().Get(), ImVec2(imgWidth, imgHeight));
}