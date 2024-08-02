#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(const wstring& key, const wstring& relativePath) 
	: Asset(key, L"Mesh\\" + relativePath)
	, vertexSysMem(nullptr), indexSysMem(nullptr)
	, vertexBufferDesc{}, vertexCount(0)
	, indexBufferDesc{}, indexCount(0)
{
}

Mesh::~Mesh()
{
	if (vertexSysMem != nullptr)
	{
		delete vertexSysMem;
		vertexSysMem = nullptr;
	}

	if (indexSysMem != nullptr)
	{
		delete indexSysMem;
		indexSysMem = nullptr;
	}
}

void Mesh::Create(Vertex* vertexSysMem, UINT vertexCount, UINT* indexSysMem, UINT indexCount)
{
}