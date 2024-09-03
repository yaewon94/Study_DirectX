#include "pch.h"
#include "Device.h"
#include "Engine.h"
#include "ConstBuffer.h"

Device::Device() 
	: hwnd(nullptr), viewPort{}
	/*, rsState(nullptr), dsState(nullptr), bsState(nullptr), samplerState(nullptr)*/
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
	return cbArr[(UINT)type];
}

int Device::Init(HWND hwnd)
{
	this->hwnd = hwnd;

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
		, device.GetAddressOf()
		, &level
		, context.GetAddressOf())))
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

	// =====================================
	// Rasterizer State 생성
	//======================================
	if (FAILED(CreateRasterizerState())) return E_FAIL;

	// ====================================================
	// ViewPort 설정
	// 뷰포트 범위는 윈도우 크기를 기준으로 0~1 정규화된 값
	// ====================================================
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = Engine::GetInstance()->GetResolution().x;
	viewPort.Height = Engine::GetInstance()->GetResolution().y;

	viewPort.MinDepth = 0.f;
	viewPort.MaxDepth = 1.f;

	context->RSSetViewports(1, &viewPort);

	// Rendering 목적지를 지정
	context->OMSetRenderTargets(1, rtView.GetAddressOf(), dsView.Get());

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
	Vec4 clearColor = Vec4(0.f, 0.f, 0.f, 1.f);
	context->ClearRenderTargetView(rtView.Get(), clearColor);
	context->ClearDepthStencilView(dsView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Device::Present()
{
	// 윈도우에 RenderTarget에 그려진 이미지 출력
	swapChain->Present(0, 0);
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

	desc.OutputWindow = hwnd;	// 백버퍼에 그려진 이미지를 출력시킬 윈도우
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
	device->QueryInterface(__uuidof(IDXGIDevice), (void**)giDevice.GetAddressOf());
	giDevice->GetAdapter(adapter.GetAddressOf());
	adapter->GetParent(__uuidof(IDXGIFactory), (void**)factory.GetAddressOf());
	if(FAILED(factory->CreateSwapChain(device.Get(), &desc, swapChain.GetAddressOf()))) return E_FAIL;

	return S_OK;
}

int Device::CreateView()
{
	// ==============================================
	// Render Target Texture
	// SwapChain이 생성될 때 만들어진 텍스처를 가리킴
	// ==============================================
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)rtTex.GetAddressOf());

	// Render Target View 생성
	if (FAILED(device->CreateRenderTargetView(rtTex.Get(), nullptr, rtView.GetAddressOf())))
	{
		return E_FAIL;
	}

	// ==============================================
	// Depth Stencil Texture
	// ==============================================
	D3D11_TEXTURE2D_DESC desc = {};

	desc.Width = (UINT)Engine::GetInstance()->GetResolution().x;
	desc.Height = (UINT)Engine::GetInstance()->GetResolution().y;

	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	// 생성 이후 CPU에서 접근이 가능한지 옵션
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;

	// 밉맵 개수가 1 ==> 원본만 존재함 
	desc.MipLevels = 1;

	desc.MiscFlags = 0;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	// Depth Stencil Texture 생성
	if (FAILED(device->CreateTexture2D(&desc, nullptr, dsTex.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Depth Stencil View 생성
	if (FAILED(device->CreateDepthStencilView(dsTex.Get(), nullptr, dsView.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

int Device::CreateConstBuffer()
{
	cbArr[(UINT)CB_TYPE::TRANSFORM] = Ptr<ConstBuffer>(CB_TYPE::TRANSFORM);
	cbArr[(UINT)CB_TYPE::TRANSFORM]->CreateOnGpu(sizeof(CB_Transform));

	return S_OK;
}

int Device::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc = {};

	// 뒷면 컬링
	rsState[(UINT)RASTERIZE_TYPE::CULL_BACK] = nullptr;

	// 앞면 컬링
	desc.CullMode = D3D11_CULL_FRONT;
	desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&desc, rsState[(UINT)RASTERIZE_TYPE::CULL_FRONT].GetAddressOf());

	// 컬링 X
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_SOLID;
	DEVICE->CreateRasterizerState(&desc, rsState[(UINT)RASTERIZE_TYPE::CULL_NONE].GetAddressOf());

	// 와이어프레임 모드
	desc.CullMode = D3D11_CULL_NONE;
	desc.FillMode = D3D11_FILL_WIREFRAME;
	DEVICE->CreateRasterizerState(&desc, rsState[(UINT)RASTERIZE_TYPE::WIRE_FRAME].GetAddressOf());

	return S_OK;
}