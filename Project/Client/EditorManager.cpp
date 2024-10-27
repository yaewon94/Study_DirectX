#include "pch.h"
#include "EditorManager.h"
#include "GameObjectEx.h"
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
	Ptr<GameObjectEx> obj;
	obj->SetName("Editor Camera");
	Ptr<Camera> camera = obj->AddComponent<Camera>();
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