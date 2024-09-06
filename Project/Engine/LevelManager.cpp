#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"

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
	Ptr<GameObject> camera = Ptr<GameObject>();
	camera->GetTransform()->SetPos(Vec3(0.f, 0.f, -100.f));
	camera->AddComponent<Camera>();
	curLevel->AddObject(LAYER_TYPE::CAMERA, camera);

	// 현재레벨 Init()
	curLevel->Init();
}

void LevelManager::Tick()
{
	curLevel->Tick();
	curLevel->FinalTick();
}

void LevelManager::Render(LAYER_TYPES layers)
{
	curLevel->Render(layers);
}

void LevelManager::AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj)
{
	curLevel->AddObject(layer, obj);
}

Ptr<GameObject> LevelManager::GetGameObject(LAYER_TYPE layer)
{
	return curLevel->GetGameObject(layer);
}