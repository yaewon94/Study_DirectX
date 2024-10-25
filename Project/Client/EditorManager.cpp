#include "pch.h"
#include "EditorManager.h"
#include "Engine/GameObject.h"
#include "Engine/Camera.h"

EditorManager::EditorManager()
{
}

EditorManager::~EditorManager()
{
}

int EditorManager::Init()
{
	// ������ ī�޶� ���
	Ptr<GameObject> obj;
	obj->SetName(L"Editor Camera");
	Ptr<Camera> camera = obj->AddComponent<Camera>(); // CHECK : ���� SetLayer()���� �����͸���϶� ���� �и� ����
	camera->SetCameraType(CAMERA_TYPE::EDITOR_CAMERA);
	camera->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
	m_objs.push_back(obj);

	return S_OK;
}

void EditorManager::Progress()
{
	for (auto& obj : m_objs)
	{
		obj->Tick();
	}

	for (auto& obj : m_objs)
	{
		obj->FinalTick();
	}
}