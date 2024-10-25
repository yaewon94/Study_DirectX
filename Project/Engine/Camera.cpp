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
	, m_type(CAMERA_TYPE::NONE)
	, m_projType(PROJECTION_TYPE::ORTHOGRAPHIC)
	, m_near(1.f), m_far(500.f)
	, m_viewWidth(Engine::GetInstance()->GetResolution().x)
	, m_viewHeight(Engine::GetInstance()->GetResolution().y)
	, m_layers(MAX_LAYER_TYPES)	// 모든 레이어 렌더링
	, m_fov(XM_PI / 2.f)
	, m_scale(1.f)
{
	GetOwner()->SetLayer(LAYER_TYPE::CAMERA);
}

Camera::Camera(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
	auto cam = origin.ptr_dynamic_cast<Camera>();
	m_type = cam->m_type;
	m_projType = cam->m_projType;
	m_near = cam->m_near;
	m_far = cam->m_far;
	m_viewWidth = cam->m_viewWidth;
	m_viewHeight = cam->m_viewHeight;
	m_layers = cam->m_layers;
	m_fov = cam->m_fov;
	m_scale = cam->m_scale;
	GetOwner()->SetLayer(LAYER_TYPE::CAMERA);
}

Camera::~Camera()
{
}

void Camera::SetCameraType(CAMERA_TYPE type)
{
	if (RenderManager::GetInstance()->ChangeCameraType(Ptr<Camera>(this), type) == S_OK)
	{
		m_type = type;
	}
}

void Camera::SetNear(float Near)
{
	if (Near >= m_far) throw std::logic_error("near값은 far값보다 작아야 합니다");
	m_near = Near;
	OnChangeProjectionMatrix();
}

void Camera::SetFar(float Far)
{
	if (Far <= m_near) throw std::logic_error("far값은 near값보다 커야 합니다");
	m_far = Far;
	OnChangeProjectionMatrix();
}

void Camera::SetViewWidth(float width)
{
	if (width <= 0.f) throw std::logic_error("view width 값은 양수여야 합니다");
	m_viewWidth = width;
	OnChangeProjectionMatrix();
}

void Camera::SetViewHeight(float height)
{
	if (height <= 0.f) throw std::logic_error("view height 값은 양수여야 합니다");
	m_viewHeight = height;
	OnChangeProjectionMatrix();
}

// @ fov : 0 ~ 360
void Camera::SetFieldOfView(int fov)
{
	if (fov >= 0) fov %= 360;
	else fov = (fov % -360) + 360;
	m_fov = fov * XM_PI / 180.f; 
	OnChangeProjectionMatrix();
}

void Camera::SetScale(float scale)
{
	if (scale <= 0.f) throw std::logic_error("view scale 값은 양수여야 합니다");
	m_scale = scale;
	OnChangeProjectionMatrix();
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
	SHADER_DOMAIN domain = obj->GetRenderComponent()->GetMaterial()->GetShader()->GetDomain();

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
	SHADER_DOMAIN domain = obj->GetRenderComponent()->GetMaterial()->GetShader()->GetDomain();

	// array<map<LAYER_TYPE, RenderComponent vec>>
	auto& layerMap = m_renderObjs[(UINT)domain];
	const auto layerMap_iter = layerMap.find(layer);

	// map<LAYER_TYPE, RenderComponent vec>
	if (layerMap_iter != layerMap.end())
	{
		auto& renderVec = layerMap_iter->second;

		for (auto vec_iter = renderVec.begin(); vec_iter != renderVec.end(); ++vec_iter)
		{
			if (obj->GetRenderComponent().Get() == vec_iter->Get())
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
	// 필드 초기화
	OnChangeProjectionType();
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

void Camera::OnChangeProjectionType()
{
	if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC)
	{
		Vec3 pos = GetOwner()->GetTransform()->GetLocalPos();
		g_transform.viewMatrix = XMMatrixTranslation(-pos.x, -pos.y, -pos.z);
	}
	else if (m_projType == PROJECTION_TYPE::PERSPECTIVE)
	{
		OnChangeRotation();
	}

	OnChangeProjectionMatrix();
}

void Camera::OnChangeProjectionMatrix()
{
	if (m_projType == PROJECTION_TYPE::ORTHOGRAPHIC)
	{
		g_transform.projMatrix = XMMatrixOrthographicLH(m_viewWidth * (1.f / m_scale), m_viewHeight * (1.f / m_scale), m_near, m_far);
	}
	else if (m_projType == PROJECTION_TYPE::PERSPECTIVE)
	{
		g_transform.projMatrix = XMMatrixPerspectiveFovLH(m_fov, m_viewHeight / m_viewWidth, m_near, m_far);
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

	g_transform.viewMatrix = matTrans * matRot;
}