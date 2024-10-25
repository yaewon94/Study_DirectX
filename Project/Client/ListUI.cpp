#include "pch.h"
#include "ListUI.h"

ListUI::ListUI() 
	: EditorUI("ListUI")
	, m_selectIdx(-1)
	, m_onDoubleClickedUI(nullptr)
	, m_onDoubleClickedFunc(nullptr)
{
}

ListUI::~ListUI()
{
}

void ListUI::AddItem(const string& name)
{
	// 중복체크
	for (auto& _name : m_nameList)
	{
		if (name == _name)
		{
			throw std::logic_error("이미 존재하는 name 입니다");
		}
	}

	m_nameList.push_back(name);
}

void ListUI::RenderUpdate()
{
	const int Size = m_nameList.size();
	bool isDoubleClicked = false;

	for (int i = 0; i < Size; ++i)
	{
		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf;

		if (m_selectIdx == i)
		{
			flags |= ImGuiTreeNodeFlags_Selected;
		}

		if (ImGui::TreeNodeEx(m_nameList[i].c_str(), flags))
		{
			if (ImGui::IsItemHovered())
			{
				if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
				{
					if (m_onDoubleClickedUI != nullptr && m_onDoubleClickedFunc != nullptr)
					{
						(m_onDoubleClickedUI->*m_onDoubleClickedFunc)(&m_nameList[i]);
						isDoubleClicked = true;
					}
				}
				else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					m_selectIdx = i;
				}
			}

			ImGui::TreePop();
			if (isDoubleClicked) break;
		}
	}

	if(isDoubleClicked) SetActive(false);
}

void ListUI::ActivateOnOff()
{
	if (!IsActive())
	{
		m_nameList.clear();
		m_selectIdx = -1;
		m_onDoubleClickedUI = nullptr;
		m_onDoubleClickedFunc = nullptr;
	}
}