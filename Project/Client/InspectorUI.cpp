#include "pch.h"
#include "InspectorUI.h"
#include "TransformUI.h"
#include "Collider2DUI.h"
#include "CameraUI.h"
#include "Light2DUI.h"
#include "MeshRenderUI.h"
#include "Engine/GameObject.h"
#include "Engine/Component.h"

InspectorUI::InspectorUI() 
	: EditorUI("Inspector")
{
}

InspectorUI::~InspectorUI()
{
}

void InspectorUI::SetTargetObject(Ptr<GameObject> obj)
{
}