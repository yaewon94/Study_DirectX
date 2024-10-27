#include "pch.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "RenderManager.h"
#include "RenderComponent.h"
#include "Camera.h"
#include "Player.h"
#include "Transform.h"
#include "TaskManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "Collider.h"

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
	Ptr<GameObject> obj = Ptr<GameObject>();
	obj->SetName(L"Main Camera");
	Ptr<Camera> camera = obj->AddComponent<Camera>();
	camera->SetCameraType(CAMERA_TYPE::MAIN_CAMERA);

	// 플레이어 오브젝트 추가
	obj = Ptr<GameObject>();
	obj->SetName(L"Player");
	obj->GetTransform()->SetLocalPosX(-300.f);
	obj->AddComponent<Player>();

	// 레벨 플레이 준비
	TaskManager::GetInstance()->ChangeLevelState(LEVEL_STATE::STOP);
}

void LevelManager::Tick()
{
	if (curLevel->GetState() == LEVEL_STATE::PLAY)
	{
		curLevel->Tick();
		curLevel->FinalTick();
	}
}

Ptr<GameObject> LevelManager::AddObject(const Ptr<GameObject>& obj)
{
	if (obj->GetLayer() == LAYER_TYPE::NONE) return nullptr;
	if (obj->GetRenderComponent() != nullptr) RenderManager::GetInstance()->AddRenderObj(obj);
	if (obj->GetCollider() != nullptr) CollisionManager::GetInstance()->AddCollider(obj->GetCollider());
	return curLevel->AddObject(obj);
}

void LevelManager::DeleteObject(const Ptr<GameObject>& obj)
{
	if (obj->GetLayer() == LAYER_TYPE::NONE) return;
	curLevel->DeleteObject(obj);
	if (obj->GetRenderComponent() != nullptr) RenderManager::GetInstance()->DeleteRenderObj(obj);
	if (obj->GetCollider() != nullptr) CollisionManager::GetInstance()->RemoveCollider(obj->GetCollider());
}

Ptr<GameObject> LevelManager::GetGameObject(LAYER_TYPE layer)
{
	return curLevel->GetGameObject(layer);
}

void LevelManager::ChangeState(LEVEL_STATE state)
{
	if (curLevel->GetState() == state) return;

	if (state == LEVEL_STATE::NONE) throw std::logic_error("none으로 변경할 수 없습니다");
	else if (state == LEVEL_STATE::STOP || state == LEVEL_STATE::PAUSE)
	{
		TimeManager::GetInstance()->SetLevelStop(true);
		RenderManager::GetInstance()->SetEditorMode(true);
		curLevel->ChangeState(state);
	}
	else if (state == LEVEL_STATE::PLAY)
	{
		TimeManager::GetInstance()->SetLevelStop(false);
		RenderManager::GetInstance()->SetEditorMode(false);
		curLevel->ChangeState(state);
		if (curLevel->GetState() == LEVEL_STATE::STOP || curLevel->GetState() == LEVEL_STATE::NONE) curLevel->Init();
	}
}