#include "pch.h"
#include "Device.h"
#include "Engine.h"
#include "ConstBuffer.h"
#include "AssetManager.h"
#include "Texture.h"

#define CLEAR_COLOR Vec4(0.f, 0.f, 0.f, 1.f)

Device::Device() 
	: m_hwnd(nullptr), m_viewPort{}
{
}

Device::~Device()
{
	//// delete 를 직접 하지 말고, DirectX 에 위임 (각각 다른 crt.dll 을 사용하고 있을 수 있으므로)
	//if(rsState != nullptr) rsState->Release();
	//if(dsState != nullptr) dsState->Release();
	//if(bsState != nullptr) bsState->Release();
	//if(samplerState != nullptr) samplerState->Release();
}

Ptr<ConstBuffer> Device::GetConstBuffer(CB_TYPE type)
{
	return m_cbArr[(UINT)type];
}

int Device::Init(HWND hwnd)
{
	m_hwnd = hwnd;

	// ============================================================
	// Device, Context 생성
	// ============================================================
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE
		, nullptr, iFlag
		, nullptr, 0, D3D11_SDK_VERSION
		, m_device.GetAddressOf()
		, &level
		, m_context.GetAddressOf())))
	{
		return E_FAIL;
	}

	// =========================================
	// SwapChain 생성
	// =========================================
	if (FAILED(CreateSwapChain())) return E_FAIL;

	// =====================================
	// RenderTargetView, DepthStencilView 생성
	// =====================================
	if (FAILED(CreateView())) return E_FAIL;

	// ============================================
	// Rasterizer State 생성
	// 벡터 그래픽 형식 => 래스터 이미지(bit) 변환
	//=============================================
	if (FAILED(CreateRasterizerState())) return E_FAIL;

	// ============================================
	// Blend State 생성
	// 픽셀 셰이더를 거쳐 생성된 단편이 렌더 타겟에 어떻게 적용될지를 결정
	//=============================================
	if (FAILED(CreateBlendState())) return E_FAIL;

	// ===========================================================
	// Depth Stencil State 생성
	// - depth : 깊이 판정 (각 픽셀의 z축값을 판별)
	// - stencil : 특정 조건을 이용해 픽셀의 렌더링 허용 or 차단
	//============================================================
	if (FAILED(CreateDepthStencilState())) return E_FAIL;

	// ==============================================================================
	// Sampler State 생성
	// 텍스처에서 색상 데이터를 어떻게 추출할지 정의
	// 특히 텍스처 확대, 축소, 회전 또는 뷰포트의 픽셀과 정확히 일치하지 않을 때 중요
	//===============================================================================
	if (FAILED(CreateSamplerState())) return E_FAIL;

	// ====================================================
	// ViewPort 설정
	// 뷰포트 범위는 윈도우 크기를 기준으로 0~1 정규화된 값
	// ====================================================
	m_viewPort.TopLeftX = 0;
	m_viewPort.TopLeftY = 0;
	m_viewPort.Width = Engine::GetInstance()->GetResolution().x;
	m_viewPort.Height = Engine::GetInstance()->GetResolution().y;

	m_viewPort.MinDepth = 0.f;
	m_viewPort.MaxDepth = 1.f;

	m_context->RSSetViewports(1, &m_viewPort);

	// Rendering 목적지를 지정
	m_context->OMSetRenderTargets(1, m_rtTex->GetRenderTargetView().GetAddressOf(), m_dsTex->GetDepthStencilView().Get());

	// ===============
	// 상수버퍼 생성
	// ===============
	if (FAILED(CreateConstBuffer()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Device::Clear()
{
	// RenderTarget, DepthStencilTexture 클리어
	m_context->ClearRenderTargetView(m_rtTex->GetRenderTargetView().Get(), CLEAR_COLOR);
	m_context->ClearDepthStencilView(m_dsTex->GetDepthStencilView().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Device::Present()
{
	// 윈도우에 RenderTarget에 그려진 이미지 출력
	m_swapChain->Present(0, 0);
}

int Device::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc = {};

	desc.BufferCount = 1;	// 백버퍼 개수
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 백버퍼 용도 설정

	desc.BufferDesc.Width = (UINT)Engine::GetInstance()->GetResolution().x;	// 해상도
	desc.BufferDesc.Height = (UINT)Engine::GetInstance()->GetResolution().y;

	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 픽셀 포맷

	desc.BufferDesc.RefreshRate.Denominator = 1;	// 화면 갱신 비율
	desc.BufferDesc.RefreshRate.Numerator = 60;

	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	desc.OutputWindow = m_hwnd;	// 백버퍼에 그려진 이미지를 출력시킬 윈도우
	desc.Windowed = true;	// 창모드(true) or 전체화면(false) 모드
	
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;	// 이전 프레임 정보는 버림
	desc.Flags = 0;

	// ==============================
	// SwapChain 객체 생성
	// ==============================
	ComPtr<IDXGIDevice> giDevice;
	ComPtr<IDXGIAdapter> adapter;
	ComPtr<IDXGIFactory> factory;

	// GUID(Global Unique ID, 128 비트) 
	m_device->QueryInterface(__uuidof(IDXGIDevice), (void**)giDevice.GetAddressOf());
	giDevice->GetAdapter(adapter.GetAddressOf());
	adapter->GetParent(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
	if(FAILED(factory->CreateSwapChain(m_device.Get(), &desc, m_swapChain.GetAddressOf()))) return E_FAIL;

	return S_OK;
}

int Device::CreateView()
{
	// ==============================================
	// Render Target Texture
	// SwapChain이 생성될 때 만들어진 텍스처를 가리킴
	// ==============================================
	ComPtr<ID3D11Texture2D> pTex2D = nullptr;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)pTex2D.GetAddressOf());
	m_rtTex = AssetManager::GetInstance()->CreateTexture(RENDER_TARGET_TEX_NAME, pTex2D);
	if (m_rtTex == nullptr)
	{
		throw std::logic_error("RenderTarget 텍스처 생성 실패");
	}

	// ==============================================
	// Depth Stencil Texture
	// ==============================================
	m_dsTex = AssetManager::GetInstance()->CreateTexture(DEPTH_STENCIL_TEX_NAME
														, Engine::GetInstance()->GetResolution()
														, DXGI_FORMAT_D24_UNORM_S8_UINT
														, D3D11_BIND_DEPTH_STENCIL);
	if (m_dsTex == nullptr)
	{
		throw std::logic_error("DepthStencil 텍스처 생성 실패");
	}

	return S_OK;
}

int Device::CreateConstBuffer()
{
	m_cbArr[(UINT)CB_TYPE::TRANSFORM] = Ptr<ConstBuffer>(CB_TYPE::TRANSFORM);
	m_cbArr[(UINT)CB_TYPE::TRANSFORM]->CreateOnGpu(sizeof(CB_Transform));

	m_cbArr[(UINT)CB_TYPE::MATERIAL] = Ptr<ConstBuffer>(CB_TYPE::MATERIAL);
	m_cbArr[(UINT)CB_TYPE::MATERIAL]->CreateOnGpu(sizeof(CB_Material));

	m_cbArr[(UINT)CB_TYPE::SPRITE] = Ptr<ConstBuffer>(CB_TYPE::SPRITE);
	m_cbArr[(UINT)CB_TYPE::SPRITE]->CreateOnGpu(sizeof(CB_Sprite));

	return S_OK;
}

int Device::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};

	// 뒷면 컬링
	m_rsState[(UINT)RASTERIZE_TYPE::CULL_BACK] = nullptr;

	// 앞면 컬링
	desc.CullMode = D3D11_CULL_FRONT;
	desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&desc, m_rsState[(UINT)RASTERIZE_TYPE::CULL_FRONT].GetAddressOf());

	// 컬링 X
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&desc, m_rsState[(UINT)RASTERIZE_TYPE::CULL_NONE].GetAddressOf());

	// 와이어프레임 모드
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&desc, m_rsState[(UINT)RASTERIZE_TYPE::WIRE_FRAME].GetAddressOf());

	return S_OK;
}

int Device::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};

	// 강제출력
	m_bsState[(UINT)BLEND_TYPE::DEFAULT] = nullptr;
	
	// 알파블렌드
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;       // 색상끼리 더하기
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;    // Source : PixelShader return 값에 곱할 계수
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;// Destination : 색상이 출력될 렌더타겟
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	if (FAILED(DEVICE->CreateBlendState(&desc, m_bsState[(UINT)BLEND_TYPE::ALPHABLEND].GetAddressOf())))
	{
		MessageBox(nullptr, L"알파블렌드 생성 실패", L"BlendState 생성 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

int Device::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC desc = {};

	// LESS : Z축값이 가장 작은 것 통과
	m_dsState[(UINT)DEPTH_STENCIL_TYPE::LESS] = nullptr;

	// LESS EQUAL : Z축값이 가장 작은 것 통과 (중복가능)
	desc.StencilEnable = false;
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DEVICE->CreateDepthStencilState(&desc, m_dsState[(UINT)DEPTH_STENCIL_TYPE::LESS_EQUAL].GetAddressOf());

	// GREATER : Z축값이 가장 큰 것 통과
	desc.StencilEnable = false;
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_GREATER;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DEVICE->CreateDepthStencilState(&desc, m_dsState[(UINT)DEPTH_STENCIL_TYPE::GREATER].GetAddressOf());

	// 깊이판정 X
	desc.StencilEnable = false;
	desc.DepthEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;	// 항상 통과
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DEVICE->CreateDepthStencilState(&desc, m_dsState[(UINT)DEPTH_STENCIL_TYPE::NO_TEST].GetAddressOf());

	// 깊이기록 X
	desc.StencilEnable = false;
	desc.DepthEnable = true;
	desc.DepthFunc = D3D11_COMPARISON_LESS;
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;	// 기록 X
	DEVICE->CreateDepthStencilState(&desc, m_dsState[(UINT)DEPTH_STENCIL_TYPE::NO_WRITE].GetAddressOf());

	// 깊이판정 X, 기록 X
	desc.StencilEnable = false;
	desc.DepthEnable = false;
	desc.DepthFunc = D3D11_COMPARISON_ALWAYS;			// 항상 통과
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;	// 기록 X
	DEVICE->CreateDepthStencilState(&desc, m_dsState[(UINT)DEPTH_STENCIL_TYPE::NO_TEST_WRITE].GetAddressOf());

	return S_OK;
}

int Device::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc = {};

	// 이방성 (비등방성) 필터링
	// 가로축과 세로축 각각에 대해 밉맵을 따로 만들어두는 것
	// * 비등방성 : 방향에 따라 물체의 물리적 성질이 다르게 변화하는 현상
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.Filter = D3D11_FILTER_ANISOTROPIC;
	DEVICE->CreateSamplerState(&desc, m_spState[(UINT)SAMPLER_TYPE::AF].GetAddressOf());

	// Minification, Magnification Mipmap 선형 필터링
	// 필터 마스크 영역 중 최솟값(또는 최댓값)을 출력 화소로 결정
	desc.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	DEVICE->CreateSamplerState(&desc, m_spState[(UINT)SAMPLER_TYPE::MIN_MAG_POINT_MIP_LINEAR].GetAddressOf());

	// 바인딩
	// Vertex Shader : 정점 처리. 노멀공간, 탄젠트공간 => 월드공간
	// Hull Shader : 표면을 여러 개의 삼각형으로 분할
	// Domain Shader : 삼각형으로 쪼개어진 지점의 정점 위치 계산
	// Geometry Shader : 인접한 정점, 삼각형, 선, 점의 기본 형식 처리
	// Pixel Shader : 픽셀 별 색상 출력 (보간 적용)
	UINT index = (UINT)SAMPLER_TYPE::AF;
	CONTEXT->VSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->HSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->DSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->GSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->PSSetSamplers(index, 1, m_spState[index].GetAddressOf());

	index = (UINT)SAMPLER_TYPE::MIN_MAG_POINT_MIP_LINEAR;
	CONTEXT->VSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->HSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->DSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->GSSetSamplers(index, 1, m_spState[index].GetAddressOf());
	CONTEXT->PSSetSamplers(index, 1, m_spState[index].GetAddressOf());

	return S_OK;
}