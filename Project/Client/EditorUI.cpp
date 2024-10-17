#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::nextID = 0;

EditorUI::EditorUI(const string& name)
	: m_name(name + "##" + std::to_string(nextID++))
	, m_isActive(true)
	, m_parent(nullptr)
{
}

EditorUI::~EditorUI()
{
	for (EditorUI* child : m_children)
	{
		if (child != nullptr)
		{
			delete child;
			child = nullptr;
		}
	}

	m_parent = nullptr;

	ImguiManager::GetInstance()->DeleteUI(*this);
}

void EditorUI::Render()
{
	if (m_isActive)
	{
		if (m_parent == nullptr)
		{
			// Begin() ~ End() 사이 호출된 위젯들은 같은 윈도우에 생성됨
			ImGui::Begin(m_name.c_str(), &m_isActive);
			RenderUpdate();
			for (EditorUI* child : m_children)
			{
				child->Render();
			}
			ImGui::End();
		}
		else
		{
			// TODO : 프레임이 보이게 출력되도록 수정
			ImGui::BeginChild(m_name.c_str());
			RenderUpdate();
			for (EditorUI* child : m_children)
			{
				child->Render();
			}
			ImGui::EndChild();
		}
	}
}