#include "pch.h"
#include "Texture.h"
#include "Device.h"

Texture::Texture(const wstring& Key, const wstring& relativePath) 
	: Asset(Key, relativePath)
	, m_desc{}, m_registerNum(TEXTURE_PARAM::NULL_PARAM)
{
}

Texture::~Texture()
{
}

int Texture::Load()
{
	HRESULT result;
	const wstring Path = GetFullPath();

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
		, m_srv.GetAddressOf());

	// Shader Resource View 를 이용해 원본객체(Texture2D) 정보 알아내기
	// ScratchImage => Texture2D
	m_srv->GetResource((ID3D11Resource**)m_tex2D.GetAddressOf());

	// Texture2D의 desc 정보
	m_tex2D->GetDesc(&m_desc);

	return S_OK;
}

void Texture::BindOnGpu(TEXTURE_PARAM param)
{
	m_registerNum = param;
	CONTEXT->VSSetShaderResources(param, 1, m_srv.GetAddressOf());	// Vertex Shader
	CONTEXT->HSSetShaderResources(param, 1, m_srv.GetAddressOf());	// Hull Shader
	CONTEXT->DSSetShaderResources(param, 1, m_srv.GetAddressOf());	// Domain Shader
	CONTEXT->GSSetShaderResources(param, 1, m_srv.GetAddressOf());	// Geometry Shader
	CONTEXT->PSSetShaderResources(param, 1, m_srv.GetAddressOf());	// Pixel Shader
}

void Texture::Clear()
{
	if (m_registerNum == TEXTURE_PARAM::NULL_PARAM)
	{
		throw std::logic_error("레지스터에 등록되어 있지 않은 텍스처입니다");
	}

	ID3D11ShaderResourceView* srv = nullptr;
	CONTEXT->VSSetShaderResources(m_registerNum, 1, &srv);
	CONTEXT->HSSetShaderResources(m_registerNum, 1, &srv);
	CONTEXT->DSSetShaderResources(m_registerNum, 1, &srv);
	CONTEXT->GSSetShaderResources(m_registerNum, 1, &srv);
	CONTEXT->PSSetShaderResources(m_registerNum, 1, &srv);
	m_registerNum = TEXTURE_PARAM::NULL_PARAM;
}