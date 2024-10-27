#pragma once
#include "EditorUI.h"

class OutlinerUI final : public EditorUI
{
public:
	OutlinerUI();
	~OutlinerUI();

public:
	virtual void RenderUpdate() final;

public:
	virtual EDITOR_UI_TYPE GetType() final { return EDITOR_UI_TYPE::OUTLINER; }
};