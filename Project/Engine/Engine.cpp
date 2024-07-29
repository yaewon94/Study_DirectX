#include "pch.h"
#include "Engine.h"
#include "Device.h"

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
	RECT rt = { 0, 0, resolution.x, resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, !!GetMenu(this->hwnd));
	SetWindowPos(this->hwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// 디바이스 초기화
	if (FAILED(Device::GetInstance()->Init(this->hwnd))) return E_FAIL;

	return S_OK;
}

void Engine::Progress()
{
}
