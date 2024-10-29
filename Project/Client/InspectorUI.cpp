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
	, m_target(nullptr)
{
}

InspectorUI::~InspectorUI()
{
}

void InspectorUI::SetTargetObject(Ptr<GameObject> obj)
{
	if (m_target.Get() == obj.Get()) return;

	m_target = obj;

	// ���ο� ������Ʈ�� ���� ������Ʈ�� ������Ʈ�� ������ �ִ��� ������ ���ϴ°͵� ����� ��� ���Ƽ�
	// ������Ʈ �ٲ� ������ ���� ������Ʈ UI �����ϰ�
	DeleteChildren();
	// ���ο� UI �߰��ϴ� ������ ����
	for (auto& pair : obj->GetComponents())
	{	
		AddChild(pair.first);
	}
}

Ptr<GameObject> InspectorUI::GetTargetObject()
{
	return m_target;
}

void InspectorUI::AddChild(COMPONENT_TYPE type)
{
	ComponentUI* child = nullptr;

	// TODO : if�� �Ⱦ��� �ٷ� ��Ī�� �� �ִ� ��� ã��
	// Engine�� Client�� ���������� �ʾƼ� \Engine\ComponentŬ������ virtual AddUI() ���� ���Ұ���
	if (type == COMPONENT_TYPE::TRANSFORM) EditorUI::AddChild<TransformUI>();
	else if (type == COMPONENT_TYPE::MESH_RENDER) EditorUI::AddChild<MeshRenderUI>();
	else if (type == COMPONENT_TYPE::COLLIDER_2D) EditorUI::AddChild<Collider2DUI>();
	else if (type == COMPONENT_TYPE::LIGHT_2D) EditorUI::AddChild<Light2DUI>();
	else if (type == COMPONENT_TYPE::CAMERA) EditorUI::AddChild<CameraUI>();
}