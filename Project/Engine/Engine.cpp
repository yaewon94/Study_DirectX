#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "AssetManager.h"
#include "CollisionManager.h"
#include "KeyManager.h"
#include "PathManager.h"
#include "TimeManager.h"
#include "LevelManager.h"
#include "RenderManager.h"
#include "TaskManager.h"

Engine::Engine() : hwnd(nullptr)
{
}

Engine::~Engine()
{
}

int Engine::Init(HWND hwnd)
{
	this->hwnd = hwnd;

	// 해상도 초기화
	RECT rt = { 0, 0, (LONG)resolution.x, (LONG)resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, !!GetMenu(this->hwnd));
	SetWindowPos(this->hwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// 디바이스 초기화
	if (FAILED(Device::GetInstance()->Init(this->hwnd))) return E_FAIL;

	// 매니저 클래스 초기화
	PathManager::GetInstance()->Init();
	if (FAILED(AssetManager::GetInstance()->Init())) return E_FAIL;
	TimeManager::GetInstance()->Init();
	if (FAILED(RenderManager::GetInstance()->Init())) return E_FAIL;
	LevelManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();

	return S_OK;
}

void Engine::Progress()
{
	// 매니저 클래스 Tick()
	TimeManager::GetInstance()->Tick();
	KeyManager::GetInstance()->Tick();
	LevelManager::GetInstance()->Tick();
	CollisionManager::GetInstance()->Tick();
	
	// 렌더링
	RenderManager::GetInstance()->Render();

	// 다음 프레임에 처리할 작업 준비
	TaskManager::GetInstance()->Tick();
}