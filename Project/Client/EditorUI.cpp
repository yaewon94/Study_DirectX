#include "pch.h"
#include "EditorUI.h"

EditorUI::EditorUI() 
	: m_isActive(true)
{
}

EditorUI::~EditorUI()
{
}

void EditorUI::Render()
{
	if (m_isActive)
	{
		// Begin() ~ End() 사이 호출된 위젯들은 같은 윈도우에 생성됨
		ImGui::Begin(m_name.c_str(), &m_isActive);
		RenderUpdate();
		ImGui::End();
	}
}