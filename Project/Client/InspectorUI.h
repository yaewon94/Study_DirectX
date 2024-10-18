#pragma once
#include "EditorUI.h"

class ComponentUI;
class GameObject;

// 하나의 게임오브젝트가 가지고 있는 모든 컴포넌트들을 종합적으로 보여주는 UI
class InspectorUI final : public EditorUI
{
	NO_COPY_ASSIGN(InspectorUI);

private:
	Ptr<GameObject> m_target;

public:
	InspectorUI(const Ptr<GameObject>& target);
	~InspectorUI();

public:
	Ptr<GameObject> GetTarget() const { return m_target; }

	template<typename T> requires std::derived_from<T, ComponentUI>
	void AddChild()
	{
		// UI 가 존재하는 경우
		if (GetChild<T>() != nullptr)
		{
			throw std::logic_error("이미 가지고 있는 UI 입니다");
		}
		// UI 가 존재하지 않는 경우
		else
		{
			ComponentUI& ui = (ComponentUI&)(RegisterChild<T>(*new T));
			ui.CallbackCreateSuccess();
		}
	}

public:
	virtual void RenderUpdate() final {}
};