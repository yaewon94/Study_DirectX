#pragma once
#include "Asset.h"

// 텍스처 에셋
class Texture final : public Asset
{
	NO_COPY_ASSIGN(Texture);

private:
	ScratchImage m_img;						// 이미지파일 로딩, 저장 기능
	ComPtr<ID3D11Texture2D> m_tex2D;		// (ScratchImage)SysMem -> GPUMem
	ComPtr<ID3D11ShaderResourceView> m_srv;	// Shader 에서 자원으로 사용할 이미지
	D3D11_TEXTURE2D_DESC m_desc;

public:
	Texture(const wstring& Key, const wstring& relativePath);
	~Texture();

public:
	virtual int Load() final;

private:
	void BindOnGpu(int _registerNum);
	void Clear(int _registerNum);
};