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

// ==============================
// 외부변수
// ==============================
extern CB_Transform g_transform;