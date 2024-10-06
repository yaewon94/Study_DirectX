#pragma once
#include "Entity.h"
#include "Render.h"

// 기존 ConstBuffer의 단점(크기고정, 크기제한)을 해결
// ConstBuffer 보다는 느리다
class StructuredBuffer final : public Entity
{
	NO_COPY_ASSIGN(StructuredBuffer);

private:
	ComPtr<ID3D11Buffer> m_buffer;
	ComPtr<ID3D11ShaderResourceView> m_srv;
	D3D11_BUFFER_DESC m_desc;

	UINT m_elementCount;	// 요소 개수
	UINT m_elementSize;		// 요소당 크기

public:
	StructuredBuffer();
	~StructuredBuffer();

public:
	void SetData(void* sysMem, UINT elementCount);

public:
	int CreateOnGpu(UINT elementSize, UINT elementCount, void* sysMem = nullptr);
	void BindOnGpu(TEXTURE_PARAM registerNum);
};