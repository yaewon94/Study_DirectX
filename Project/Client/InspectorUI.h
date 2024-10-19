#pragma once
#include "EditorUI.h"

class ComponentUI;
class GameObject;

// 하나의 게임오브젝트가 가지고 있는 모든 컴포넌트들을 종합적으로 보여주는 UI
class InspectorUI final : public EditorUI
{
	NO_COPY_ASSIGN(InspectorUI);

public:
	InspectorUI(const Ptr<GameObject>& target);
	~InspectorUI();

public:
	template<typename T> requires std::derived_from<T, ComponentUI>
	void AddChild(Ptr<GameObject> target)
	{
		// UI 가 존재하는 경우
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("이미 가지고 있는 UI 입니다");
		}
		// UI 가 존재하지 않는 경우
		else
		{
			T* componentUI = new T(target);

			// 컴포넌트는 있는데 UI가 없는 경우
			if (componentUI->GetComponent() != nullptr)
			{
				// 동일한 상위 타입의 컴포넌트를 이미 가지고 있어서 추가할 수 없는 경우
				if (componentUI->GetComponent(false) == nullptr)
				{
					delete componentUI;
					MessageBox(nullptr, L"이미 동일한 타입의 상위 컴포넌트가 존재합니다", L"컴포넌트 추가 실패", MB_OK);
				}
				// 추가 가능한 경우
				else
				{
					RegisterChild<T>(*componentUI);
				}
			}
			// 컴포넌트가 없는 경우 : UI 추가, 컴포넌트 추가
			else
			{
				((ComponentUI&)RegisterChild<T>(*componentUI)).AddComponent();
			}
		}
	}

public:
	virtual void RenderUpdate() final {}
};