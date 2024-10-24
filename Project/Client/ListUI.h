#pragma once
#include "EditorUI.h"

// 리스트 출력용 UI
class ListUI final : public EditorUI
{
	NO_COPY_ASSIGN(ListUI);

private:
	vector<string> m_nameList;
	int m_selectIdx;

	EditorUI* m_onDoubleClickedUI;
	EUI_CALLBACK m_onDoubleClickedFunc;

public:
	ListUI();
	virtual ~ListUI();

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::LIST; }

	void AddItem(const string& name);

	void SetDoubleClick(EditorUI& ui, EUI_CALLBACK func)
	{ 
		m_onDoubleClickedUI = &ui;
		m_onDoubleClickedFunc = func;
	}

public:
	virtual void RenderUpdate() final;
	virtual void ActivateOnOff() final;
};