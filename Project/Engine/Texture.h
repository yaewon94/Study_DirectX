#pragma once
#include "Asset.h"
#include "Render.h"

// 텍스처 에셋
class Texture final : public Asset
{
	NO_COPY_ASSIGN(Texture);

private:
	ScratchImage m_img;						// 이미지파일 로딩, 저장 기능
	ComPtr<ID3D11Texture2D> m_tex2D;		// (ScratchImage)SysMem -> GPUMem

	ComPtr<ID3D11RenderTargetView> m_rtView;
	ComPtr<ID3D11DepthStencilView> m_dsView;
	ComPtr<ID3D11ShaderResourceView> m_srView;	// Shader 에서 자원으로 사용할 이미지

	D3D11_TEXTURE2D_DESC m_desc;

	TEXTURE_PARAM m_registerNum;

public:
	Texture(const wstring& Key, const wstring& relativePath);
	~Texture();

public:
	TEXTURE_PARAM GetRegisterNum() { return m_registerNum; }
	UINT GetWidth() { return m_desc.Width; }
	UINT GetHeight() { return m_desc.Height; }
	ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return m_rtView; }
	ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return m_dsView; }
	ComPtr<ID3D11Texture2D> GetTexture2D() { return m_tex2D; }

public:
	virtual int Load() final;

public:
	int CreateOnGpu(ComPtr<ID3D11Texture2D> texture);
	int CreateOnGpu(Vec2 size, DXGI_FORMAT format, UINT bindFlags, D3D11_USAGE usage);
	void BindOnGpu(TEXTURE_PARAM param);
	void Clear();

private:
	int CreateView(UINT bindFlags);
};