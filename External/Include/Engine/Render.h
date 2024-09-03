#pragma once

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
	Matrix viewMatrix;
	Matrix projMatrix;
};

// 래스터라이즈 타입
// 벡터 그래픽 형식 => 래스터 이미지(bit) 변환
enum class RASTERIZE_TYPE : UINT
{
	// culling : 오브젝트에서 필요없는 부분을 렌더링 하지 않게 하는 기법 
	CULL_BACK,	// 뒷면 컬링 (DEFAULT)
	CULL_FRONT,	// 앞면 컬링
	CULL_NONE,
	WIRE_FRAME,	// 와이어 프레임
	COUNT_END
};

// ==============================
// 외부변수
// ==============================
extern CB_Transform g_transform;