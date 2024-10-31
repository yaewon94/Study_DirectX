#include "pch.h"
#include "Mesh.h"
#include "Device.h"

Mesh::Mesh(const string& key, const string& relativePath) 
	: Asset(key, relativePath)
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

int Mesh::CreateOnGpu(Vertex* vertexSysMem, UINT vertexCount, UINT* indexSysMem, UINT indexCount)
{
	// =============================================
	// Vertex
	// =============================================
	if (this->vertexSysMem != nullptr)
	{
		delete this->vertexSysMem;
	}

	this->vertexCount = vertexCount;
	this->vertexSysMem = new Vertex[vertexCount];
	memcpy(this->vertexSysMem, vertexSysMem, sizeof(Vertex) * vertexCount);

	// 정점 데이터 시스템 메모리 => GPU 메모리로 이동
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;			// 변경 불가
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;	// CPUAccessFlags와 함께 쓰임

	// 버퍼 초기데이터 전달
	D3D11_SUBRESOURCE_DATA sub = {};
	sub.pSysMem = vertexSysMem;

	// 정점 객체 생성
	if (FAILED(DEVICE->CreateBuffer(&vertexBufferDesc, &sub, vertexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	//================
	// Index
	// ===============
	if (this->indexSysMem != nullptr)
	{
		delete this->indexSysMem;
	}

	this->indexCount = indexCount;
	this->indexSysMem = new UINT[indexCount];
	memcpy(this->indexSysMem, indexSysMem, sizeof(UINT) * indexCount);

	indexBufferDesc.ByteWidth = sizeof(UINT) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	sub.pSysMem = indexSysMem;

	if (FAILED(DEVICE->CreateBuffer(&indexBufferDesc, &sub, indexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void Mesh::Render()
{
	BindOnGpu();
	CONTEXT->DrawIndexed(indexCount, 0, 0);
}

void Mesh::BindOnGpu()
{
	// 렌더링할 정점 정보 전달
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// Input Assembler
	// 정점 버퍼, 인덱스 버퍼 바인딩
	CONTEXT->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	CONTEXT->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}