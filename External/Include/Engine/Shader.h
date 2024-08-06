#pragma once
#include "Asset.h"

class Shader : public Asset
{
protected:
	ComPtr<ID3DBlob> errorBlob;

protected:
	Shader(ASSET_TYPE Type, const wstring& key, const wstring& relativePath);
	~Shader();
};