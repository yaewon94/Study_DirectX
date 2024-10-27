#include "pch.h"
#include "OutlinerUI.h"
#include "TreeUI.h"

OutlinerUI::OutlinerUI() 
	: EditorUI("OutlinerUI")
{
	AddChild<TreeUI>();
}

OutlinerUI::~OutlinerUI()
{
}

void OutlinerUI::RenderUpdate()
{
}
