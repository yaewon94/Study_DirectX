#pragma once
#include "EditorUI.h"

class Component;
class GameObject;

// 게임오브젝트가 가지고 있는 컴포넌트 관련 값을 설정하는 UI
class ComponentUI : public EditorUI
{
	NO_COPY_ASSIGN(ComponentUI);

protected:
	ComponentUI(const string& name);
	~ComponentUI();

protected:
	virtual void AddComponent() = 0;
	virtual Ptr<Component> GetComponent() = 0;

public:
	void CallbackCreateSuccess();

//protected:
//	void SetComponentTitle();
};