#pragma once
#include "Asset.h"

// ���� ���� ����ü
struct Vertex
{
	Vec3 pos;
	Vec2 uv;
	Vec4 color;
};

// �޽� ���� Ŭ����
class Mesh final : public Asset
{
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
	Mesh(const wstring& key, const wstring& relativePath);
	~Mesh();

public:
	int Create(Vertex* vertexSysMem, UINT vertexCount, UINT* indexSysMem, UINT indexCount);
	void Render();

private:
	void Bind();
};