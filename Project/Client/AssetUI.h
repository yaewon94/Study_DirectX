#pragma once
#include "EditorUI.h"

class AssetUI : public EditorUI
{
	NO_COPY_ASSIGN(AssetUI);

protected:
	AssetUI(const string& name);
	~AssetUI();
};