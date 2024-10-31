#include "pch.h"
#include "Texture.h"
#include "Device.h"

Texture::Texture(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
	, m_desc{}
{
}

Texture::~Texture()
{
}

int Texture::Load()
{
	HRESULT result;
	const wstring Path = GetFullPathW();

	// ==========================
	// 파일 => System Memory
	// ==========================
	wchar_t szExt[10] = {};
	_wsplitpath_s(Path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);
	wstring strExt = szExt;

	if (strExt == L".dds" || strExt == L".DDS")
	{
		result = LoadFromDDSFile(Path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, m_img);
	}
	else if (strExt == L".tga" || strExt == L".TGA")
	{
		result = LoadFromTGAFile(Path.c_str(), nullptr, m_img);
	}
	else
	{
		// WIC : Window Image Component (.png, .jpg, .jpeg, .bmp)
		result = LoadFromWICFile(Path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, m_img);
	}

	if (FAILED(result))
	{
		MessageBox(nullptr, L"텍스처 로딩 실패", L"텍스처 로딩 실패", MB_OK);
		return E_FAIL;
	}

	// ==========================
	// System Memory => GPU
	// ==========================
	CreateShaderResourceView(DEVICE.Get()
		, m_img.GetImages()
		, m_img.GetImageCount()
		, m_img.GetMetadata()
		, m_srView.GetAddressOf());

	// Shader Resource View 를 이용해 원본객체(Texture2D) 정보 알아내기
	// ScratchImage => Texture2D
	m_srView->GetResource((ID3D11Resource**)m_tex2D.GetAddressOf());

	// Texture2D의 desc 정보
	m_tex2D->GetDesc(&m_desc);

	return S_OK;
}

int Texture::CreateOnGpu(ComPtr<ID3D11Texture2D> texture)
{
	m_tex2D = texture;
	m_tex2D->GetDesc(&m_desc);
	if (FAILED(CreateView(m_desc.BindFlags))) return E_FAIL;

	return S_OK;
}

int Texture::CreateOnGpu(Vec2 size, DXGI_FORMAT format, UINT bindFlags, D3D11_USAGE usage)
{
	// DESC 작성
	m_desc.Width = size.x;
	m_desc.Height = size.y;
	m_desc.ArraySize = 1;
	m_desc.Format = format;
	m_desc.BindFlags = bindFlags;	// 텍스처 용도
	m_desc.Usage = usage;	// 생성 이후, CPU에서 접근 가능한지 옵션

	if (m_desc.Usage == D3D11_USAGE_DYNAMIC)
	{
		m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else if(m_desc.Usage == D3D11_USAGE_STAGING)
	{
		m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	}

	m_desc.MipLevels = 1;	// 밉맵 개수 1 (원본만 존재)
	m_desc.MiscFlags = 0;
	m_desc.SampleDesc.Count = 1;
	m_desc.SampleDesc.Quality = 0;

	if (FAILED(DEVICE->CreateTexture2D(&m_desc, nullptr, m_tex2D.GetAddressOf())))
	{
		MessageBox(nullptr, L"DESC 오류", L"텍스처 생성 실패", MB_OK);
		return E_FAIL;
	}

	// view 생성
	if (FAILED(CreateView(m_desc.BindFlags))) return E_FAIL;
	
	return S_OK;
}

void Texture::BindOnGpu(TEXTURE_PARAM registerNum)
{
	CONTEXT->VSSetShaderResources(registerNum, 1, m_srView.GetAddressOf());	// Vertex Shader
	CONTEXT->HSSetShaderResources(registerNum, 1, m_srView.GetAddressOf());	// Hull Shader
	CONTEXT->DSSetShaderResources(registerNum, 1, m_srView.GetAddressOf());	// Domain Shader
	CONTEXT->GSSetShaderResources(registerNum, 1, m_srView.GetAddressOf());	// Geometry Shader
	CONTEXT->PSSetShaderResources(registerNum, 1, m_srView.GetAddressOf());	// Pixel Shader
}

void Texture::Clear(TEXTURE_PARAM registerNum)
{
	ID3D11ShaderResourceView* srv = nullptr;
	CONTEXT->VSSetShaderResources(registerNum, 1, &srv);
	CONTEXT->HSSetShaderResources(registerNum, 1, &srv);
	CONTEXT->DSSetShaderResources(registerNum, 1, &srv);
	CONTEXT->GSSetShaderResources(registerNum, 1, &srv);
	CONTEXT->PSSetShaderResources(registerNum, 1, &srv);
}

int Texture::CreateView(UINT bindFlags)
{
	// view 생성
	if (m_desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
	{
		if (FAILED(DEVICE->CreateDepthStencilView(m_tex2D.Get(), nullptr, m_dsView.GetAddressOf())))
		{
			MessageBox(nullptr, L"Depth Stencil View 생성 실패", L"텍스처 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	if (m_desc.BindFlags & D3D11_BIND_RENDER_TARGET)
	{
		if (FAILED(DEVICE->CreateRenderTargetView(m_tex2D.Get(), nullptr, m_rtView.GetAddressOf())))
		{
			MessageBox(nullptr, L"RenderTarget View 생성 실패", L"텍스처 생성 실패", MB_OK);
			return E_FAIL;
		}
	}
	if (m_desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
	{
		if (FAILED(DEVICE->CreateShaderResourceView(m_tex2D.Get(), nullptr, m_srView.GetAddressOf())))
		{
			MessageBox(nullptr, L"Shader Resource View 생성 실패", L"텍스처 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}