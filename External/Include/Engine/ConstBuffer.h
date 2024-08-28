#pragma once
#include "Entity.h"

// 상수 버퍼 타입
enum class CB_TYPE : UINT
{
	TRANSFORM, COUNT_END
};

// 오브젝트의 위치,크기,회전값 상수버퍼
struct CB_Transform
{
	//Vec4 pos;
	//Vec4 scale;
	Matrix worldMatrix;
};

// 상수 버퍼 클래스
class ConstBuffer final : public Entity
{
	NO_COPY_ASSIGN(ConstBuffer);

private:
	const CB_TYPE Type;
	ComPtr<ID3D11Buffer> buffer;
	D3D11_BUFFER_DESC desc;

public:
	ConstBuffer(const CB_TYPE Type);
	~ConstBuffer();

public:
	void SetData(void* data, UINT dataSize = 0);

public:
	int CreateOnGpu(UINT bufferSize);
	void BindOnGpu();
};