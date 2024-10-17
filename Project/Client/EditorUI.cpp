#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::nextID = 0;

EditorUI::EditorUI(const Ptr<GameObject>& target)
	: m_ID(nextID++), m_isActive(true)
	, m_parent(nullptr)
	, m_target(target)
{
	m_name = "##" + std::to_string(m_ID);
}

EditorUI::~EditorUI()
{
	m_parent = nullptr;

	for (EditorUI* child : m_children)
	{
		if (child != nullptr)
		{
			delete child;
			child = nullptr;
		}
	}
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