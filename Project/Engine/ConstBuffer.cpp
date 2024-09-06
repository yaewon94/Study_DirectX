#include "pch.h"
#include "ConstBuffer.h"
#include "Device.h"

ConstBuffer::ConstBuffer(const CB_TYPE Type) 
    : Type(Type), desc{}
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

int ConstBuffer::CreateOnGpu(UINT bufferSize)
{
    desc.ByteWidth = bufferSize;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;   // 값 변경 가능
    desc.Usage = D3D11_USAGE_DYNAMIC;               // CPUAccessFlags와 함께 사용

    if (FAILED(DEVICE->CreateBuffer(&desc, nullptr, buffer.GetAddressOf())))
    {
        return E_FAIL;
    }

    return S_OK;
}

void ConstBuffer::BindOnGpu()
{
    CONTEXT->VSSetConstantBuffers((UINT)Type, 1, buffer.GetAddressOf());    // Vertex Shader
    CONTEXT->HSSetConstantBuffers((UINT)Type, 1, buffer.GetAddressOf());    // Hull Shader
    CONTEXT->DSSetConstantBuffers((UINT)Type, 1, buffer.GetAddressOf());    // Domain Shader
    CONTEXT->GSSetConstantBuffers((UINT)Type, 1, buffer.GetAddressOf());    // Geometry Shader
    CONTEXT->PSSetConstantBuffers((UINT)Type, 1, buffer.GetAddressOf());    // Pixel Shader
}