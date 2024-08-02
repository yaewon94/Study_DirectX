#pragma once
#include "Shader.h"

class GraphicShader final : public Shader
{
private:
	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3DBlob> vertexShaderBlob;

	ComPtr<ID3D11PixelShader> pixelShader;
	ComPtr<ID3DBlob> pixelShaderBlob;

	ComPtr<ID3D11InputLayout> layout;

	D3D11_PRIMITIVE_TOPOLOGY topology;

public:
	GraphicShader(const wstring& key, const wstring& relativePath);
	~GraphicShader();

public:
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { this->topology = topology; }

public:
	int Create(const string& vertexFuncName, const string& pixelFuncName);
	void Bind();
};