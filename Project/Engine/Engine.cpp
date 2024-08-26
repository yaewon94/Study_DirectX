#include "pch.h"
#include "Engine.h"
#include "Device.h"
#include "KeyManager.h"
#include "PathManager.h"
#include "TimeManager.h"
#include "RenderTest.h"

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
	//KeyManager::GetInstance()->Init();

	// 렌더링 테스트 초기화
	if (FAILED(InitTest())) return E_FAIL;

	return S_OK;
}

void Engine::Progress()
{
	// 매니저 클래스 Tick()
	TimeManager::GetInstance()->Tick();
	//KeyManager::GetInstance()->Tick();
	TickTest();

	// 매 프레임마다 호출
	RenderTest();
}
