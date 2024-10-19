#include "pch.h"
#include "ComponentUI.h"
#include "Engine/GameObject.h"
#include "Engine/Component.h"

ComponentUI::ComponentUI(const string& name, Ptr<GameObject> target)
	: EditorUI(name), m_target(target)
{
}

ComponentUI::~ComponentUI()
{
}