#pragma once
#include "EditorUI.h"

class Component;

// ���ӿ�����Ʈ�� ������ �ִ� ������Ʈ ���� ���� �����ϴ� UI
class ComponentUI : public EditorUI
{
	NO_COPY_ASSIGN(ComponentUI);

protected:
	ComponentUI(const string& name);
	~ComponentUI();

//public:
//	virtual Ptr<Component> AddComponent() = 0;
//	virtual Ptr<Component> GetComponent(bool isBaseType = true) = 0;
};