#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "RenderManager.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Render.h"

Ptr<Camera> Camera::mainCamera = nullptr;

Camera::Camera(const Ptr<GameObject>& owner)
	: Component(owner)
	, m_projType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_near(1.f), m_far(500.f)
	, m_aspectRatio(Engine::GetInstance()->GetResolution().y / Engine::GetInstance()->GetResolution().x)
	, m_layers(0xffffffff)	// 모든 레이어 렌더링
	, m_fov(XM_PI / 2.f)
	, m_width(Engine::GetInstance()->GetResolution().x)
	, m_scale(m_aspectRatio)
{
}

Camera::Camera(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
	auto cam = origin.ptr_dynamic_cast<Camera>();
	m_projType = cam->m_projType;
	m_near = cam->m_near;
	m_far = cam->m_far;
	m_aspectRatio = cam->m_aspectRatio;
	m_layers = cam->m_layers;
	m_fov = cam->m_fov;
	m_width = cam->m_width;
	m_scale = cam->m_scale;
}

Camera::~Camera()
{
}

void Camera::SetLayerOnOff(LAYER_TYPE layer)
{
	// 등록된 레이어인 경우
	if (m_layers & layer)
	{
		// ex. ???????1 & 00000001 => 00000001
		// layer 비트반전 11111110
		// ???????1 & 11111110 => #######0
		// ? 비트에 위치한 레이어가 등록되어 있는 경우는 어차피 #값이 1이 나오고,
		// 등록되어 있지 않은 경우는 #값이 0이 되므로 다른 레이어 값엔 영향을 주지 않음
		m_layers &= ~layer;
	}
	// 등록되지 않은 경우
	else
	{
		// ex. ???????0 | 00000001 => ???????1
		m_layers |= layer;
	}
}

void Camera::Init()
{
	// 메인 카메라 설정
	if (mainCamera == nullptr)
	{
		this->GetOwner()->SetName(L"Main Camera");
		mainCamera = Ptr<Camera>(this);
	}

	// RenderManager에 카메라 등록
	RenderManager::GetInstance()->AddCamera(Ptr<Camera>(this));

	// View행렬 계산 (TODO : 값 변동시 변동될 때 마다 호출되도록 구현)
	Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
	Matrix matTrans = XMMatrixTranslation(pos.x, pos.y, pos.z);
	m_matView = matTrans;
	g_transform.viewMatrix = m_matView;

	// 투영행렬 계산 (TODO : 값 변동시 변동될 때 마다 호출되도록 구현)
	m_matProj = XMMatrixOrthographicLH(m_width, m_width * m_aspectRatio, m_near, m_far);
	g_transform.projMatrix = m_matProj;
}

void Camera::FinalTick()
{
}

void Camera::Render()
{
	LevelManager::GetInstance()->Render(m_layers);
}