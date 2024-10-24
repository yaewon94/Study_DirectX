#include "pch.h"
#include "EditorUI.h"

UINT EditorUI::nextID = 0;

EditorUI::EditorUI(const string& name)
	: m_name(name + "##" + std::to_string(nextID++))
	, m_isActive(true)
	, m_parent(nullptr)
	, m_isModal(false)
{
}

EditorUI::~EditorUI()
{
	m_parent = nullptr;
}

void EditorUI::Destroy()
{
	for (EditorUI* child : m_children)
	{
		if (child != nullptr)
		{
			child->Destroy();
			child = nullptr;
		}
	}

	ImguiManager::GetInstance()->DeleteUI(*this); // 소멸자에서 이거 호출하면 this->GetType() 순수가상함수라 쓰레기값 나옴
	delete this;
}

void EditorUI::SetActive(bool isActive)
{
	if (m_isActive != isActive)
	{
		m_isActive = isActive;

		for (const auto& child : m_children)
		{
			child->SetActive(isActive);
		}

		ActivateOnOff();
	}
}

void EditorUI::Tick()
{
	if (m_isActive) TickUpdate();
}

void EditorUI::Render()
{
	if (m_isActive)
	{
		if (m_parent == nullptr)
		{
			if (m_isModal) RenderModal();
			else RenderModalless();
		}
		else
		{
			RenderChild();
		}
	}
}

void EditorUI::RenderTitle()
{
	// TODO : 버튼 말고 다른 타입으로 출력되게 (텍스트 종류로 하면 ## 뒤의 문자열도 출력되어버림)
	ImGui::Button(GetName().c_str());

	/*ImGui::PushID(0);

	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.f, 0.6f, 0.6f));

	ImGui::PopStyleColor(1);
	ImGui::PopID();*/
}

void EditorUI::RenderModal()
{
	bool preActive = m_isActive;
	const char* szName = m_name.c_str();

	ImGui::OpenPopup(szName);
	if (ImGui::BeginPopupModal(szName, &preActive))
	{
		RenderUpdate();
		for (EditorUI* child : m_children)
		{
			child->Render();
			//ImGui::Separator();
		}

		ImGui::EndPopup();
	}
	else
	{
		SetActive(preActive);
	}
}

void EditorUI::RenderModalless()
{
	bool preActive = m_isActive;

	// Begin() ~ End() 사이 호출된 위젯들은 같은 윈도우에 생성됨
	ImGui::Begin(m_name.c_str(), &m_isActive);
	if (preActive != m_isActive) SetActive(preActive);
	RenderUpdate();
	for (EditorUI* child : m_children)
	{
		child->Render();
		//ImGui::Separator();
	}
	ImGui::End();
}

void EditorUI::RenderChild()
{
	ImGui::BeginChild(m_name.c_str(), GetChildSize());
	RenderUpdate();
	for (EditorUI* child : m_children)
	{
		child->Render();
		//ImGui::Separator();
	}
	ImGui::EndChild();
}