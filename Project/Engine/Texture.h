#pragma once
#include "Asset.h"
#include "Render.h"

// 텍스처 에셋
class Texture final : public Asset
{
	NO_COPY_ASSIGN(Texture);

public:
	static const ASSET_TYPE Type = ASSET_TYPE::TEXTURE;

private:
	ScratchImage m_img;						// 이미지파일 로딩, 저장 기능
	ComPtr<ID3D11Texture2D> m_tex2D;		// (ScratchImage)SysMem -> GPUMem

	ComPtr<ID3D11RenderTargetView> m_rtView;
	ComPtr<ID3D11DepthStencilView> m_dsView;
	ComPtr<ID3D11ShaderResourceView> m_srView;	// Shader 에서 자원으로 사용할 이미지

	D3D11_TEXTURE2D_DESC m_desc;

public:
	Texture(const string& Key, const string& relativePath);
	~Texture();

public:
	virtual ASSET_TYPE GetType() final { return Type; }

	ComPtr<ID3D11Texture2D> GetTexture2D() { return m_tex2D; }

	int GetWidth() { return m_desc.Width; }
	int GetHeight() { return m_desc.Height; }

	ComPtr<ID3D11RenderTargetView> GetRenderTargetView() { return m_rtView; }
	ComPtr<ID3D11DepthStencilView> GetDepthStencilView() { return m_dsView; }
	ComPtr<ID3D11ShaderResourceView> GetShaderResourceView() { return m_srView; }

public:
	virtual int Load() final;

public:
	int CreateOnGpu(ComPtr<ID3D11Texture2D> texture);
	int CreateOnGpu(Vec2 size, DXGI_FORMAT format, UINT bindFlags, D3D11_USAGE usage);
	void BindOnGpu(TEXTURE_PARAM registerNum);
	void Clear(TEXTURE_PARAM registerNum);

private:
	int CreateView();
};