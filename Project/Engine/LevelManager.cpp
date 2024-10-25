#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "GameObject.h"
#include "Camera.h"
#include "RenderManager.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init()
{
	curLevel = Ptr<Level>();

	// ===================== 필수 오브젝트 추가 =======================
	// 메인카메라 추가
	Ptr<GameObject> cameraObj = Ptr<GameObject>();
	cameraObj->SetName(L"Main Camera");
	Ptr<Camera> camera = cameraObj->AddComponent<Camera>();
	camera->SetCameraType(CAMERA_TYPE::MAIN_CAMERA);

	// 현재레벨 Init()
	curLevel->Init();
}

void LevelManager::Tick()
{
	curLevel->Tick();
	curLevel->FinalTick();
}

Ptr<GameObject> LevelManager::AddObject(const Ptr<GameObject>& obj)
{
	return curLevel->AddObject(obj);
}

void LevelManager::DeleteObject(const Ptr<GameObject>& obj)
{
	curLevel->DeleteObject(obj);
}

Ptr<GameObject> LevelManager::GetGameObject(LAYER_TYPE layer)
{
	return curLevel->GetGameObject(layer);
}