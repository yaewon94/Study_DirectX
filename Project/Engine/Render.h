#pragma once


// 색상
#define COLOR_GREEN Vec4(0.f, 1.f, 0.f, 1.f);

// 텍스처 타입 (value : 레지스터 번호)
enum TEXTURE_PARAM
{
	NULL_PARAM = -1,	// 레지스터 할당 이전 값
	TEX_0, TEX_1, TEX_2, TEX_3, TEX_4, TEX_5,
	TEXARR_0, TEXARR_1, TEXARR_2, TEXARR_3,
	CUBE_0, CUBE_1,
	COUNT_END
};

// Blend State
enum class BLEND_TYPE : UINT
{
	DEFAULT,				// 강제출력
	ALPHABLEND,				// 알파값 적용
	ALPHABLEND_COVERAGE,	// 알파블렌드 + AlphaToCoverage
	ONE_ONE,				// 1:1 블렌딩
	COUNT_END
};

// 상수 버퍼 타입
enum class CB_TYPE : UINT
{
	TRANSFORM, MATERIAL, COUNT_END
};

// 재질 상수버퍼
struct CB_Material
{
	int iArr[4];
	float fArr[4];
	Vec2 v2Arr[4];
	Vec4 v4Arr[4];
	Matrix matrixArr[2];
	int bTex[TEXTURE_PARAM::COUNT_END];	// 바이너리 텍스처
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

// 디버깅 모드 shape
enum class DEBUG_SHAPE
{
	RECT, CIRCLE, CROSS, LINE
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

// 파라미터 타입
enum SCALAR_PARAM
{
	INT_0, INT_1, INT_2, INT_3,
	FLOAT_0, FLOAT_1, FLOAT_2, FLOAT_3,
	VEC2_0, VEC2_1, VEC2_2, VEC2_3,
	VEC4_0, VEC4_1, VEC4_2, VEC4_3,
	MATRIX_0, MATRIX_1
};

// 셰이더 동작 분류
enum class SHADER_DOMAIN
{
	DOMAIN_OPAQUE,			// 불투명
	DOMAIN_MASK,			// 불투명 or 투명
	DOMAIN_TRANSPARENT,		// 반투명 + 투명
	DOMAIN_POSTPROCESS		// 후처리
};

// ==============================
// 외부변수
// ==============================
extern CB_Transform g_transform;