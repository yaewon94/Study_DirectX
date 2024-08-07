#pragma once
#include "Asset.h"

// 정점 정보 구조체
struct Vertex
{
	Vec3 pos;
	Vec2 uv;
	Vec4 color;
};

// 메쉬 에셋 클래스
class Mesh final : public Asset
{
	NO_COPY_ASSIGN(Mesh);
	friend class Asset;

private:
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	Vertex* vertexSysMem;
	UINT* indexSysMem;

	D3D11_BUFFER_DESC vertexBufferDesc;
	UINT vertexCount;

	D3D11_BUFFER_DESC indexBufferDesc;
	UINT indexCount;

private:
	Mesh(const wstring& key, const wstring& relativePath);
	~Mesh();

public:
	int GpuInit(Vertex* vertexSysMem, UINT vertexCount, UINT* indexSysMem, UINT indexCount);
	void Render();

private:
	void Bind();
};