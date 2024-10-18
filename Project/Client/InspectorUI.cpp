#include "pch.h"
#include "InspectorUI.h"
#include "TransformUI.h"
#include "Collider2DUI.h"
#include "Engine/GameObject.h"

InspectorUI::InspectorUI(const Ptr<GameObject>& target) 
	: EditorUI("Inspector")
	, m_target(target)
{
	// 게임오브젝트가 필수로 가지고 있어야 하는 컴포넌트
	AddChild<TransformUI>();

	// TODO : 오브젝트가 가지고 있는 컴포넌트들 불러와서 UI 추가
	AddChild<Collider2DUI>();
}

InspectorUI::~InspectorUI()
{
}