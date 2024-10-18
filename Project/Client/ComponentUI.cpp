#include "pch.h"
#include "ComponentUI.h"
#include "Engine/GameObject.h"
#include "Engine/Component.h"

ComponentUI::ComponentUI(const string& name)
	: EditorUI(name)
{
}

ComponentUI::~ComponentUI()
{
}

void ComponentUI::CallbackCreateSuccess()
{
	if (this->GetComponent() == nullptr)
	{
		this->AddComponent();
	}
}