#pragma once
#include "EditorUI.h"

class Component;
class GameObject;

// 게임오브젝트가 가지고 있는 컴포넌트 관련 값을 설정하는 UI
class ComponentUI : public EditorUI
{
	NO_COPY_ASSIGN(ComponentUI);

private:
	Ptr<GameObject> m_target;

protected:
	ComponentUI(const string& name, Ptr<GameObject> target);
	~ComponentUI();

public:
	virtual Ptr<Component> AddComponent() = 0;
	virtual Ptr<Component> GetComponent(bool isBaseType = true) = 0;

protected:
	Ptr<GameObject> GetTarget() const { return m_target; }
};