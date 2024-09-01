#include "pch.h"
#include "RenderManager.h"
#include "Device.h"
#include "Camera.h"
#include "GameObject.h"

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

void RenderManager::AddCamera(const Ptr<Camera>& _camera)
{
	// 중복 체크
	for (auto& camera : cameras)
	{
		if (camera.GetAddressOf() == _camera.GetAddressOf())
		{
			MessageBoxA(nullptr, "이미 등록된 카메라 입니다", "카메라 등록 실패", MB_OK);
			return;
		}
	}

	// 카메라 등록
	cameras.push_back(_camera);
}

void RenderManager::Render()
{
	// 이전 프레임에 렌더링 된 것 지우기
	Device::GetInstance()->Clear();

	// 카메라 렌더링
	for (auto& cam : cameras)
	{
		cam->Render();
	}

	// RenderTarget -> 윈도우 출력
	Device::GetInstance()->Present();
}