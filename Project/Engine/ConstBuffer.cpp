#include "pch.h"
#include "ConstBuffer.h"
#include "Device.h"

ConstBuffer::ConstBuffer(CB_TYPE type) 
    : type(type), desc{}
{
}

ConstBuffer::~ConstBuffer()
{
}

void ConstBuffer::SetData(void* data, UINT dataSize)
{
    D3D11_MAPPED_SUBRESOURCE sub = {};
    CONTEXT->Map(buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &sub);

    if (dataSize == 0) dataSize = desc.ByteWidth;
    memcpy(sub.pData, data, dataSize);

    CONTEXT->Unmap(buffer.Get(), 0);
}

int ConstBuffer::Create(UINT bufferSize)
{
    desc.ByteWidth = bufferSize;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // �� ���� ����
    desc.Usage = D3D11_USAGE_DYNAMIC;               // CPUAccessFlags�� �Բ� ���

    if (FAILED(DEVICE->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
    {
        return E_FAIL;
    }

    return S_OK;
}

void ConstBuffer::Bind()
{
    // Vertex Shader Stage
    CONTEXT->VSSetConstantBuffers((UINT)type, 1, buffer.GetAddressOf());
}