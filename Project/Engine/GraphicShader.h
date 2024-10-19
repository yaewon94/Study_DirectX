#pragma once
#include "Shader.h"
#include "Render.h"

class GraphicShader final : public Shader
{
	NO_COPY_ASSIGN(GraphicShader);

private:
	SHADER_DOMAIN domain;

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3DBlob> vertexShaderBlob;

	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3DBlob> pixelShaderBlob;

	ComPtr<ID3D11InputLayout> layout;

	D3D11_PRIMITIVE_TOPOLOGY topology;

	RASTERIZE_TYPE rsType;
	BLEND_TYPE bsType;
	DEPTH_STENCIL_TYPE dsType;

public:
	GraphicShader(const string& key, const string& relativePath);
	~GraphicShader();

public:
	SHADER_DOMAIN GetDomain() { return domain; }
	BLEND_TYPE GetBlendType() { return bsType; }

	void SetDomain(SHADER_DOMAIN domain) { this->domain = domain; }
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { this->topology = topology; }
	void SetRasterizerType(RASTERIZE_TYPE type) { rsType = type; }
	void SetBlendType(BLEND_TYPE type) { bsType = type; }
	void SetDepthStencilType(DEPTH_STENCIL_TYPE type) { dsType = type; }

public:
	int CreateOnGpu(const string& vertexFuncName, const string& pixelFuncName);
	void BindOnGpu();
};