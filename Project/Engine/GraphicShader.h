#pragma once
#include "Shader.h"
#include "Render.h"

class GraphicShader final : public Shader
{
	NO_COPY_ASSIGN(GraphicShader);

private:
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3DBlob> vertexShaderBlob;

	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3DBlob> pixelShaderBlob;

	ComPtr<ID3D11InputLayout> layout;

	D3D11_PRIMITIVE_TOPOLOGY topology;

	RASTERIZE_TYPE rsType;

public:
	GraphicShader(const wstring& key, const wstring& relativePath);
	~GraphicShader();

public:
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { this->topology = topology; BindOnGpu(); }
	void SetRasterizerType(RASTERIZE_TYPE type) { rsType = type; }

public:
	int CreateOnGpu(const string& vertexFuncName, const string& pixelFuncName);

private:
	void BindOnGpu();
};