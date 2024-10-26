#include "pch.h"
#include "LevelManager.h"
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

	// ===================== �ʼ� ������Ʈ �߰� =======================
	// ����ī�޶� �߰�
	Ptr<GameObject> cameraObj = Ptr<GameObject>();
	cameraObj->SetName(L"Main Camera");
	Ptr<Camera> camera = cameraObj->AddComponent<Camera>();
	camera->SetCameraType(CAMERA_TYPE::MAIN_CAMERA);

	// ���緹�� Init()
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

void LevelManager::ChangeState(LEVEL_STATE state)
{
	if (curLevel->GetState() == state) return;
	if (state == LEVEL_STATE::NONE) throw std::logic_error("none���� ������ �� �����ϴ�");

	curLevel->ChangeState(state);
}