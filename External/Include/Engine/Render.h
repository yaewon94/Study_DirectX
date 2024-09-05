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

	Matrix wv;	// world * view
	Matrix wvp;	// world * view * projection
};

// 래스터라이즈 타입
enum class RASTERIZE_TYPE : UINT
{
	// culling : 오브젝트에서 필요없는 부분을 렌더링 하지 않게 하는 기법 
	CULL_BACK,	// 뒷면 컬링 (DEFAULT)
	CULL_FRONT,	// 앞면 컬링
	CULL_NONE,
	WIRE_FRAME,	// 와이어 프레임
	COUNT_END
};

// 샘플링 타입
enum class SAMPLER_TYPE : UINT
{
	AF,							// 이방성 필터링
	MIN_MAG_POINT_MIP_LINEAR,	// Minification, Magnification Mipmap 선형 필터링
	COUNT_END
};

// ==============================
// 외부변수
// ==============================
extern CB_Transform g_transform;