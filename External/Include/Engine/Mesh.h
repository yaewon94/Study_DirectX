#pragma once
#include "Asset.h"

// 정점 정보 구조체
struct Vertex
{
	Vec3 pos;
	Vec2 uv;	// 텍스처를 3차원에 매핑하기 위해 변환 기준이 되는 2차원 좌표계
	Vec4 color;
};

// 메쉬 에셋 클래스
class Mesh final : public Asset
{
	NO_COPY_ASSIGN(Mesh);

public:
	static const ASSET_TYPE Type = ASSET_TYPE::MESH;

private:
	ComPtr<ID3D11Buffer> vertexBuffer;
	ComPtr<ID3D11Buffer> indexBuffer;

	Vertex* vertexSysMem;
	UINT* indexSysMem;

	D3D11_BUFFER_DESC vertexBufferDesc;
	UINT vertexCount;

	D3D11_BUFFER_DESC indexBufferDesc;
	UINT indexCount;

public:
	Mesh(const string& key, const string& relativePath);
	~Mesh();

public:
	virtual ASSET_TYPE GetType() final { return Type; }

	int GetVertexCount() { return vertexCount; }
	const Vertex& GetVertexInfo(int idx) { return vertexSysMem[idx]; }

	int GetIndexCount() { return indexCount; }
	const UINT* const GetIndexInfo() { return indexSysMem; }

public:
	int CreateOnGpu(Vertex* vertexSysMem, UINT vertexCount, UINT* indexSysMem, UINT indexCount);
	void Render();
	virtual int Load() final { return S_OK; }

private:
	void BindOnGpu();
};