#include "pch.h"
#include "Camera.h"
#include "Engine.h"
#include "RenderManager.h"
#include "LevelManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "TransformValues.h"
#include "RenderManager.h"
#include "RenderComponent.h"
#include "GraphicShader.h"
#include "Material.h"

Camera::Camera(const Ptr<GameObject>& owner)
	: Component(owner)
	, m_projType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_near(1.f), m_far(500.f)
	, m_aspectRatio(Engine::GetInstance()->GetResolution().y / Engine::GetInstance()->GetResolution().x)
	, m_layers(MAX_LAYER_TYPES)	// 모든 레이어 렌더링
	, m_fov(XM_PI / 2.f)
	, m_width(Engine::GetInstance()->GetResolution().x)
	, m_scale(1.f)
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
	if (layer <= LAYER_TYPE::CAMERA)
	{
		throw std::logic_error("양의 정수값을 가진 레이어만 등록/제거 가능합니다");
	}

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

void Camera::AddRenderObj(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer <= LAYER_TYPE::CAMERA)
	{
		throw std::logic_error("잘못된 접근입니다");
	}
	SHADER_DOMAIN domain = obj->GetComponent<RenderComponent>()->GetMaterial()->GetShader()->GetDomain();

	// array<map<LAYER_TYPE, RenderComponent vec>>
	auto& layerMap = m_renderObjs[(UINT)domain];
	const auto layerMap_iter = layerMap.find(layer);

	// map<LAYER_TYPE, RenderComponent vec>
	if (layerMap_iter != layerMap.end())
	{
		layerMap_iter->second.push_back(obj->GetRenderComponent());
	}
	else
	{
		vector<Ptr<RenderComponent>> renderVec;
		renderVec.push_back(obj->GetRenderComponent());
		layerMap.insert(make_pair(layer, renderVec));
	}
}

void Camera::DeleteRenderObj(const Ptr<GameObject>& obj)
{
	if (obj->GetRenderComponent() == nullptr) return;

	LAYER_TYPE layer = obj->GetLayer();
	if (layer <= LAYER_TYPE::CAMERA)
	{
		throw std::logic_error("잘못된 접근입니다");
	}
	SHADER_DOMAIN domain = obj->GetComponent<RenderComponent>()->GetMaterial()->GetShader()->GetDomain();

	// array<map<LAYER_TYPE, RenderComponent vec>>
	auto& layerMap = m_renderObjs[(UINT)domain];
	const auto layerMap_iter = layerMap.find(layer);

	// map<LAYER_TYPE, RenderComponent vec>
	if (layerMap_iter != layerMap.end())
	{
		auto& renderVec = layerMap_iter->second;

		for (auto vec_iter = renderVec.begin(); vec_iter != renderVec.end(); ++vec_iter)
		{
			if (obj->GetRenderComponent().GetAddressOf() == vec_iter->GetAddressOf())
			{
				renderVec.erase(vec_iter);

				// 해당 layer에 등록된 렌더컴포넌트가 없는 경우 map에서 제거
				if (renderVec.empty())
				{
					layerMap.erase(layerMap_iter);
				}

				break;
			}
		}
	}
}

void Camera::Init()
{
	// RenderManager에 카메라 등록
	RenderManager::GetInstance()->AddCamera(Ptr<Camera>(this));

	// View행렬 계산 (TODO : 값 변동시 변동될 때 마다 호출되도록 구현)
	if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC)
	{
		Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
		Matrix matTrans = XMMatrixTranslation(-pos.x, -pos.y, -pos.z);
		m_matView = matTrans;
	}
	else if(m_projType == PROJECTION_TYPE::PERSPECTIVE)
	{
		OnChangeRotation();
	}
	g_transform.viewMatrix = m_matView;

	// 투영행렬 계산 (TODO : 값 변동시 변동될 때 마다 호출되도록 구현)
	if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC)
	{
		m_matProj = XMMatrixOrthographicLH(m_width * m_scale, m_width * m_aspectRatio * m_scale, m_near, m_far);
	}
	else if (m_projType == PROJECTION_TYPE::PERSPECTIVE)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fov, m_aspectRatio, m_near, m_far);
	}
	g_transform.projMatrix = m_matProj;
}

void Camera::FinalTick()
{
	// TODO : 매 틱마다 말고, 카메라 rotation이 변경되었을 때만 호출되도록 구현 생각해보기
	if (m_projType == PROJECTION_TYPE::PERSPECTIVE) OnChangeRotation();
}

void Camera::Render()
{
	// Post Process가 아닌 Domain Shader
	for (UINT domain = 0; domain < (UINT)SHADER_DOMAIN::DOMAIN_POSTPROCESS; ++domain)
	{
		for (auto& layerPair : m_renderObjs[domain])
		{
			// 렌더링할 LAYER만 호출
			if (m_layers & layerPair.first)
			{
				for (auto& renderComponent : layerPair.second)
				{
					renderComponent->Render();
				}
			}
		}
	}

	// Post Process Domain Shader
	for (auto& layerPair : m_renderObjs[(UINT)SHADER_DOMAIN::DOMAIN_POSTPROCESS])
	{
		if (m_layers & layerPair.first)
		{
			for (auto& renderComponent : layerPair.second)
			{
				RenderManager::GetInstance()->CopyRenderTarget();
				renderComponent->Render();
			}
		}
	}
}

void Camera::OnChangeRotation()
{
	Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
	Matrix matTrans = XMMatrixTranslation(-pos.x, -pos.y, -pos.z);
	Matrix matRot = XMMatrixIdentity();

	Vec3 right = GetOwner()->GetTransform()->GetWorldDirection(DIRECTION_VEC::RIGHT);
	Vec3 up = GetOwner()->GetTransform()->GetWorldDirection(DIRECTION_VEC::UP);
	Vec3 front = GetOwner()->GetTransform()->GetWorldDirection(DIRECTION_VEC::FRONT);

	matRot._11 = right.x;	matRot._12 = up.x;	matRot._13 = front.x;
	matRot._21 = right.y;	matRot._22 = up.y;	matRot._23 = front.y;
	matRot._31 = right.z;	matRot._32 = up.z;	matRot._33 = front.z;

	m_matView = matTrans * matRot;
}