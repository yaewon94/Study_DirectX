#include "pch.h"
#include "Mesh.h"
#include "Device.h"

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

int Mesh::Create(Vertex* vertexSysMem, UINT vertexCount, UINT* indexSysMem, UINT indexCount)
{
	// =============================================
	// Vertex
	// =============================================
	this->vertexCount = vertexCount;
	this->vertexSysMem = new Vertex[vertexCount];
	memcpy(this->vertexSysMem, vertexSysMem, sizeof(Vertex) * vertexCount);

	// ���� ������ �ý��� �޸� => GPU �޸𸮷� �̵�
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;			// ���� �Ұ�
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;	// CPUAccessFlags�� �Բ� ����

	// ���� �ʱⵥ���� ����
	D3D11_SUBRESOURCE_DATA sub = {};
	sub.pSysMem = vertexSysMem;

	// ���� ��ü ����
	if (FAILED(DEVICE->CreateBuffer(&vertexBufferDesc, &sub, vertexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	//================
	// Index
	// ===============
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
	Bind();
	CONTEXT->DrawIndexed(indexCount, 0, 0);
}

void Mesh::Bind()
{
	// �������� ���� ���� ����
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	// Input Assembler
	// ���� ����, �ε��� ���� ���ε�
	CONTEXT->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	CONTEXT->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, offset);
}