#include "pch.h"
#include "StructedBuffer.h"
#include "Device.h"

StructedBuffer::StructedBuffer() 
	: m_desc{}
	, m_elementCount(0), m_elementSize(0)
{
}

StructedBuffer::~StructedBuffer()
{
}

void StructedBuffer::SetData(void* sysMem, UINT elementCount)
{
	D3D11_MAPPED_SUBRESOURCE sub = {};

	CONTEXT->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);
	memcpy(sub.pData, sysMem, m_elementSize * m_elementCount);	// TODO : 오버플로 감지
	CONTEXT->Unmap(m_buffer.Get(), 0);
}

int StructedBuffer::CreateOnGpu(UINT elementSize, UINT elementCount, void* sysMem)
{
	if (elementSize % BUFFER_SIZE_UNIT != 0)
	{
		throw std::logic_error("구조화 버퍼의 크기는" + std::to_string(BUFFER_SIZE_UNIT) + "의 배수여야 합니다");
	}

	HRESULT result;

	m_elementCount = elementCount;
	m_elementSize = elementSize;

	// desc 설정
	m_desc.ByteWidth = m_elementCount * m_elementSize;

	m_desc.Usage = D3D11_USAGE_DYNAMIC;
	m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	m_desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

	m_desc.StructureByteStride = m_elementSize;

	// sysMem => GPU
	if (sysMem != nullptr)
	{
		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = sysMem;
		result = DEVICE->CreateBuffer(&m_desc, &sub, m_buffer.GetAddressOf());
	}
	else
	{
		result = DEVICE->CreateBuffer(&m_desc, nullptr, m_buffer.GetAddressOf());
	}

	if (FAILED(result))
	{
		MessageBox(nullptr, L"구조화 버퍼 생성 실패", L"구조화 버퍼 생성 실패", MB_OK);
		return E_FAIL;
	}

	// Shader Resource View 생성
	D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};

	desc.BufferEx.NumElements = m_elementCount;
	desc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

	if (FAILED(DEVICE->CreateShaderResourceView(m_buffer.Get(), &desc, m_srv.GetAddressOf())))
	{
		return E_FAIL;
	}
	
	return S_OK;
}

void StructedBuffer::BindOnGpu(UINT registerNum)
{
	CONTEXT->VSSetShaderResources(registerNum, 1, m_srv.GetAddressOf());
	CONTEXT->HSSetShaderResources(registerNum, 1, m_srv.GetAddressOf());
	CONTEXT->DSSetShaderResources(registerNum, 1, m_srv.GetAddressOf());
	CONTEXT->GSSetShaderResources(registerNum, 1, m_srv.GetAddressOf());
	CONTEXT->PSSetShaderResources(registerNum, 1, m_srv.GetAddressOf());
}