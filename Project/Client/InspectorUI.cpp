#include "pch.h"
#include "InspectorUI.h"
#include "TransformUI.h"
#include "Collider2DUI.h"
#include "CameraUI.h"
#include "Light2DUI.h"
#include "MeshRenderUI.h"
#include "MeshUI.h"
#include "Engine/GameObject.h"
#include "Engine/Component.h"
#include "Engine/Asset.h"

InspectorUI::InspectorUI() 
	: EditorUI("Inspector")
	, m_targetObj(nullptr)
	, m_targetAsset(nullptr)
{
}

InspectorUI::~InspectorUI()
{
}

void InspectorUI::SetTargetObject(Ptr<GameObject> obj)
{
	if (m_targetObj.Get() == obj.Get()) return;

	m_targetObj = obj;

	// 새로운 오브젝트가 기존 오브젝트의 컴포넌트를 가지고 있는지 일일이 비교하는것도 비용이 들것 같아서
	// 오브젝트 바뀔 때마다 기존 컴포넌트 UI 제거하고
	DeleteChildren();
	// 새로운 UI 추가하는 식으로 구현
	for (auto& pair : obj->GetComponents())
	{	
		AddChild(pair.first);
	}
}

Ptr<GameObject> InspectorUI::GetTargetObject()
{
	return m_targetObj;
}

void InspectorUI::SetTargetAsset(Ptr<Asset> asset)
{
	if (m_targetAsset.Get() == asset.Get()) return;
	m_targetAsset = asset;

	DeleteChildren();
	AddChild(asset->GetType());
}

Ptr<Asset> InspectorUI::GetTargetAsset()
{
	return m_targetAsset;
}

void InspectorUI::AddChild(COMPONENT_TYPE type)
{
	// TODO : if문 안쓰고 바로 매칭할 수 있는 방법 찾기
	// Engine은 Client에 종속적이지 않아서 \Engine\Component클래스에 virtual AddUI() 구현 안할거임
	if (type == COMPONENT_TYPE::TRANSFORM) EditorUI::AddChild<TransformUI>();
	else if (type == COMPONENT_TYPE::MESH_RENDER) EditorUI::AddChild<MeshRenderUI>();
	else if (type == COMPONENT_TYPE::COLLIDER_2D) EditorUI::AddChild<Collider2DUI>();
	else if (type == COMPONENT_TYPE::LIGHT_2D) EditorUI::AddChild<Light2DUI>();
	else if (type == COMPONENT_TYPE::CAMERA) EditorUI::AddChild<CameraUI>();
}

void InspectorUI::AddChild(ASSET_TYPE type)
{
	if (type == ASSET_TYPE::MESH) EditorUI::AddChild<MeshUI>();
}