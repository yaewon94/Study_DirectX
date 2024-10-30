#pragma once
#include "Shader.h"
#include "Render.h"

// Topology values for EditorUI
static const char* TopologyNameArr[] 
	= { "None"
	, "Point list"
	, "Line list"
	, "Line stripe"
	, "Triangle list" };
static constexpr auto TopologyArrSize = sizeof(TopologyNameArr) / sizeof(const char*);

// Graphic Shader
class GraphicShader final : public Shader
{
	NO_COPY_ASSIGN(GraphicShader);

public:
	static const ASSET_TYPE Type = ASSET_TYPE::GRAPHIC_SHADER;

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
	virtual ASSET_TYPE GetType() final { return Type; }

	D3D11_PRIMITIVE_TOPOLOGY GetTopology() { return topology; }
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { this->topology = topology; }

	SHADER_DOMAIN GetDomain() { return domain; }
	void SetDomain(SHADER_DOMAIN domain) { this->domain = domain; }

	RASTERIZE_TYPE GetRasterizeType() { return rsType; }
	void SetRasterizerType(RASTERIZE_TYPE type) { rsType = type; }

	BLEND_TYPE GetBlendType() { return bsType; }
	void SetBlendType(BLEND_TYPE type) { bsType = type; }

	DEPTH_STENCIL_TYPE GetDepthStencilType() { return dsType; }
	void SetDepthStencilType(DEPTH_STENCIL_TYPE type) { dsType = type; }

public:
	int CreateOnGpu(const string& vertexFuncName, const string& pixelFuncName);
	void BindOnGpu();
};