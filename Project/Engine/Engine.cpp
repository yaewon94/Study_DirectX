#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "KeyManager.h"
#include "PathManager.h"
#include "TimeManager.h"
#include "LevelManager.h"

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
	TimeManager::GetInstance()->Init();
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

	// 이전 프레임 RenderTarget, DepthStencil 클리어
	Device::GetInstance()->Clear();
	// 게임오브젝트 렌더링
	LevelManager::GetInstance()->Render();
	// 윈도우에 RenderTarget에 그려진 것 출력
	Device::GetInstance()->Present();
}
