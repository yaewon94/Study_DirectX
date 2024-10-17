#include "pch.h"
#include "InspectorUI.h"
#include "TransformUI.h"
#include "Engine/GameObject.h"

InspectorUI::InspectorUI(const Ptr<GameObject>& target) 
	: EditorUI("Inspector")
	, m_target(target)
{
	AddChild<TransformUI>();
}

InspectorUI::~InspectorUI()
{
}

void InspectorUI::RenderUpdate()
{
}