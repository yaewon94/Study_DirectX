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
	// ������ ���� �ڿ� ����
	ReleaseTest();
}

int Engine::Init(HWND hwnd)
{
	this->hwnd = hwnd;

	// �ػ� �ʱ�ȭ
	RECT rt = { 0, 0, resolution.x, resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPED, !!GetMenu(this->hwnd));
	SetWindowPos(this->hwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// ����̽� �ʱ�ȭ
	if (FAILED(Device::GetInstance()->Init(this->hwnd))) return E_FAIL;

	// �Ŵ��� Ŭ���� �ʱ�ȭ
	PathManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();

	// ������ �׽�Ʈ �ʱ�ȭ
	if (FAILED(InitTest())) return E_FAIL;

	return S_OK;
}

void Engine::Progress()
{
	// �Ŵ��� Ŭ���� Tick()
	TimeManager::GetInstance()->Tick();
	KeyManager::GetInstance()->Tick();

	// �� �����Ӹ��� ȣ��
	RenderTest();
}