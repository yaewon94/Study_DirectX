#include "pch.h"
#include "MenuUI.h"
#include "Engine/LevelManager.h"
#include "Engine/TaskManager.h"

MenuUI::MenuUI() 
	: EditorUI("MenuUI")
{
}

MenuUI::~MenuUI()
{
}

void MenuUI::Render()
{
	if (IsActive())
	{
		if(ImGui::BeginMainMenuBar())
		{
			MenuFile();
			MenuLevel();
			MenuGameObject();
			MenuEditor();
			MenuAsset();

			ImGui::EndMainMenuBar();
		}
	}
}

void MenuUI::MenuAsset()
{
	if (ImGui::BeginMenu("Asset"))
	{
		ImGui::EndMenu();
	}
}

void MenuUI::MenuEditor()
{
	if (ImGui::BeginMenu("Editor"))
	{
		ImGui::EndMenu();
	}
}

void MenuUI::MenuFile()
{
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("Level Save"))
		{
		}

		if (ImGui::MenuItem("Level Load"))
		{
		}

		ImGui::EndMenu();
	}
}

void MenuUI::MenuGameObject()
{
	if (ImGui::BeginMenu("GameObject"))
	{
		if (ImGui::MenuItem("Undo", "Ctrl + Z"))
		{
		}

		if (ImGui::MenuItem("Redo", "Ctrl + Y", false, false))
		{
		}

		ImGui::Separator();

		if (ImGui::MenuItem("Cut", "Ctrl + X"))
		{
		}

		if (ImGui::MenuItem("Copy", "Ctrl + C"))
		{
		}

		if (ImGui::MenuItem("Paste", "Ctrl + V"))
		{
		}

		ImGui::EndMenu();
	}
}

void MenuUI::MenuLevel()
{
	if (ImGui::BeginMenu("Level"))
	{
		bool isPlay = LevelManager::GetInstance()->GetState() == LEVEL_STATE::PLAY;
		bool isStop = LevelManager::GetInstance()->GetState() == LEVEL_STATE::STOP;

		// 현재상태가 Stop, Pause 일때 활성화
		if (ImGui::MenuItem("Play", nullptr, nullptr, !isPlay))
		{
			TaskManager::GetInstance()->ChangeLevelState(LEVEL_STATE::PLAY);
		}

		// 현재상태가 Play 일때 활성화
		if (ImGui::MenuItem("Pause", nullptr, nullptr, isPlay))
		{
			TaskManager::GetInstance()->ChangeLevelState(LEVEL_STATE::PAUSE);
		}

		// 현재상태가 Play, Pause 일때 활성화
		if (ImGui::MenuItem("Stop", nullptr, nullptr, !isStop))
		{
		}

		ImGui::EndMenu();
	}
}