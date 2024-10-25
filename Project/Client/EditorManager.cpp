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
	// 에디터 카메라 등록
	Ptr<GameObject> obj;
	obj->SetName(L"Editor Camera");
	Ptr<Camera> camera = obj->AddComponent<Camera>(); // CHECK : 아직 SetLayer()에서 에디터모드일때 조건 분리 안함
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