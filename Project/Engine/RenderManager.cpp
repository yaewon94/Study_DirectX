#include "pch.h"
#include "RenderManager.h"
#include "Engine.h"
#include "Device.h"
#include "ConstBuffer.h"
#include "StructuredBuffer.h"
#include "AssetManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Light2D.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"

#define CLEAR_COLOR Vec4(0.f, 0.f, 0.f, 1.f)

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

int RenderManager::ChangeCameraType(Ptr<Camera> camera, CAMERA_TYPE type)
{
	if (type == CAMERA_TYPE::NONE)
	{
		throw std::logic_error("CAMERA_TYPE::NONE 으로 변경할 수 없습니다");
	}

	// 중복 체크
	if (m_cameraMap.find(type) != m_cameraMap.end())
	{
		MessageBoxA(nullptr, "이미 같은 타입의 카메라가 등록되어 있습니다", "카메라 타입 변경 실패", MB_OK);
		return E_FAIL;
	}
	else
	{
		// 기존 내 타입으로 등록되어 있던 카메라 삭제
		const auto iter = m_cameraMap.find(camera->GetCameraType());
		if (iter != m_cameraMap.end())
		{
			m_cameraMap.erase(iter);
		}
		// 새 타입으로 등록
		m_cameraMap.insert(make_pair(type, camera));
		return S_OK;
	}
}

void RenderManager::AddRenderObj(Ptr<GameObject> obj, CAMERA_TYPE type)
{
	if (type == CAMERA_TYPE::NONE)
	{
		throw std::logic_error("잘못된 접근입니다");
	}

	const auto iter = m_cameraMap.find(type);

	if (iter != m_cameraMap.end())
	{
		iter->second->AddRenderObj(obj);
	}
	else
	{
		throw std::logic_error("등록되지 않은 카메라 입니다");
	}
}

void RenderManager::DeleteRenderObj(Ptr<GameObject> obj, CAMERA_TYPE type)
{
	if (type == CAMERA_TYPE::NONE)
	{
		throw std::logic_error("잘못된 접근입니다");
	}

	const auto iter = m_cameraMap.find(type);

	if (iter != m_cameraMap.end())
	{
		iter->second->DeleteRenderObj(obj);
	}
	else
	{
		throw std::logic_error("등록되지 않은 카메라 입니다");
	}
}

// 멤버변수로 vector<Ptr<Light2D>> 저장, AddLight2D()에 static으로 vector<Light2dInfo>를 저장하면 공간낭비가 아닌가 해서
// 1) 파라미터를 Light2dInfo* 로 받아도
///// vector<Light2dInfo> 에 추가하게 되면 객체가 복사되어 추가되므로 주소기반 중복체크를 할 수 없게 됨
// 2) vector<Light2dInfo*>로 받게되면 구조화 버퍼에 SetData(vector.data()) 호출 시
///// vector.data()가 데이터가 아닌 주소를 넘겨버리는 문제 발생
void RenderManager::AddLight2D(Ptr<Light2D> light)
{
	// 중복체크
	for (auto& _light : m_light2Ds)
	{
		if (_light.Get() == light.Get())
		{
			throw std::logic_error("이미 등록된 Light2D 입니다");
		}
	}

	m_light2Ds.push_back(light);

	// 2D 광원 정보 바인딩
	m_light2dInfos.push_back(light->GetInfo());

	if (m_light2dBuffer->GetElementCount() < m_light2dInfos.size())
	{
		m_light2dBuffer->CreateOnGpu(sizeof(Light2dInfo), (UINT)m_light2dInfos.size());
	}
	//m_light2dBuffer->SetData(m_infos.data(), m_infos.size());
	//m_light2dBuffer->BindOnGpu(TEXTURE_PARAM::LIGHT_2D);

	// 전역 정보 바인딩
	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::GLOBAL);
	g_global.Light2dCount = (int)m_light2Ds.size();
	cb->SetData(&g_global);
	cb->BindOnGpu();
}

int RenderManager::Init()
{
	// Render Target Texture, Depth Stencil Texture
	m_rtTex = AssetManager::GetInstance()->FindAsset<Texture>("RenderTargetTex");
	m_dsTex = AssetManager::GetInstance()->FindAsset<Texture>("DepthStencilTex");

	// ViewPort 설정 (Window 화면 영역 지정)
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;

	viewport.Width = Engine::GetInstance()->GetResolution().x;
	viewport.Height = Engine::GetInstance()->GetResolution().y;

	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;

	CONTEXT->RSSetViewports(1, &viewport);

	// Rendering 목적지를 지정
	CONTEXT->OMSetRenderTargets(1, m_rtTex->GetRenderTargetView().GetAddressOf(), m_dsTex->GetDepthStencilView().Get());

	// Post Process Texture
	m_postProcessTex = AssetManager::GetInstance()->CreateTexture("PostProcessTex"
																, Engine::GetInstance()->GetResolution()
																, DXGI_FORMAT_R8G8B8A8_UNORM
																, D3D11_BIND_SHADER_RESOURCE);

	if (m_postProcessTex == nullptr) return E_FAIL;
	else return S_OK;
}

void RenderManager::Render()
{
	// 이전 프레임 Target 클리어
	Clear();

	// 데이터 및 리소스 바인딩
	BindOnGpu();

	// 카메라 렌더링
	for (auto& pair : m_cameraMap)
	{
		pair.second->Render();
	}
}

void RenderManager::CopyRenderTarget()
{
	Ptr<Texture> rtTex = AssetManager::GetInstance()->FindAsset<Texture>(RENDER_TARGET_TEX_NAME);
	CONTEXT->CopyResource(m_postProcessTex->GetTexture2D().Get(), rtTex->GetTexture2D().Get());
}

void RenderManager::Clear()
{
	CONTEXT->ClearRenderTargetView(m_rtTex->GetRenderTargetView().Get(), CLEAR_COLOR);
	CONTEXT->ClearDepthStencilView(m_dsTex->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void RenderManager::BindOnGpu()
{
	int lightCount = m_light2dInfos.size();

	for (int i=0; i<lightCount; ++i)
	{
		m_light2dInfos[i] = m_light2Ds[i]->GetInfo();
	}
	m_light2dBuffer->SetData(m_light2dInfos.data(), lightCount);
	m_light2dBuffer->BindOnGpu(TEXTURE_PARAM::LIGHT_2D);
}

void RenderManager::InitDebugShape(Ptr<GameObject> obj, const DebugShapeInfo& info)
{
	ChangeDebugPos(obj, info.pos);
	ChangeDebugScale(obj, info.scale);
	obj->GetTransform()->SetLocalRotation(info.rotation);

	Ptr<MeshRender> meshRender = obj->AddComponent<MeshRender>();

	ChangeDebugShape(obj, info.shape);
	meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("Debug_Material"));
	meshRender->GetMaterial()->SetColor(info.color);

	obj->SetLayer(LAYER_TYPE::DEBUG);
	obj->Init();
}

void RenderManager::ChangeDebugShape(Ptr<GameObject> obj, DEBUG_SHAPE shape)
{
	switch (shape)
	{
	case DEBUG_SHAPE::RECT:
		obj->GetComponent<MeshRender>()->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh_D"));
		break;
	default:
		throw std::logic_error("에셋에 등록되지 않은 Debug Shape 입니다");
	}
}

void RenderManager::ChangeDebugPos(Ptr<GameObject> obj, Vec3 pos)
{
	obj->GetTransform()->SetLocalPos(pos);
}

void RenderManager::ChangeDebugScale(Ptr<GameObject> obj, Vec3 scale)
{
	obj->GetTransform()->SetLocalScale(scale);
}