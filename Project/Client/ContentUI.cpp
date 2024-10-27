#include "pch.h"
#include "ContentUI.h"
#include "TreeUI.h"

ContentUI::ContentUI() 
	: EditorUI("ContentUI")
{
	AddChild<TreeUI>();
}

ContentUI::~ContentUI()
{
}

void ContentUI::RenderUpdate()
{
}