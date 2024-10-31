#include "pch.h"
#include "SpriteUI.h"
#include "InspectorUI.h"
#include "Engine/Sprite.h"
#include "Engine/AssetManager.h"
#include "Engine/Texture.h"

SpriteUI::SpriteUI() : AssetUI("Sprite")
{
	m_sprite = ((InspectorUI*)ImguiManager::GetInstance()->FindUI(EDITOR_UI_TYPE::INSPECTOR))->GetTargetAsset().ptr_dynamic_cast<Sprite>();
}

SpriteUI::~SpriteUI()
{
}

void SpriteUI::RenderUpdate()
{
	RenderTitle();

	// IsRepeat
	ImGui::Text("Is Repeat");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::RadioButton("##sprite_repeat", m_sprite->IsRepeat()))
	{
		m_sprite->SetRepeatOnOff();
	}

	// FPS
	int fps = m_sprite->GetFPS();
	ImGui::Text("FPS");
	ImGui::SameLine(SAMELINE_VALUE);
	if (ImGui::InputInt("##sprite_fps", &fps, 0, 0, ImGuiInputTextFlags_::ImGuiInputTextFlags_EnterReturnsTrue))
	{
		if (fps <= 0 || fps > 60)
		{
			MessageBoxA(nullptr, "fps값은 1 이상 60 이하만 가능합니다", "컴포넌트 값 변경 실패", MB_OK);
		}
		else
		{
			m_sprite->SetFPS(fps);
		}
	}
	ImGui::NewLine();

	// Atlas Texture
	ImGui::Text("Atlas Texture");
	ImGui::SameLine(SAMELINE_VALUE);
	ImGui::BeginGroup();
		int frmCnt = m_sprite->GetFrameCount();
		ImGui::TextDisabled("frame count");
		ImGui::SameLine(SAMELINE_VALUE);
		if (ImGui::InputInt("##sprite_frmCnt", &frmCnt, 0, 0))
		{
			if(frmCnt > 0)
			{
				m_sprite->SetFrameCount(frmCnt);
			}
		}
		
		if (ImGui::BeginCombo("##sprite_atals", m_sprite->GetAtlasTexture()->GetKey().c_str()))
		{
			for (auto& pair : AssetManager::GetInstance()->GetAssets(ASSET_TYPE::TEXTURE))
			{
				if (ImGui::Selectable(pair.first.c_str(), m_sprite.Get() == pair.second.Get()))
				{
					m_sprite->SetAtlasTexture(pair.second.ptr_dynamic_cast<Texture>(), m_sprite->GetFrameCount());
				}
			}

			ImGui::EndCombo();
		}
	ImGui::EndGroup();
}