#pragma once

#define DEFAULT_SCALE_NO_PARENT Vec3(100.f, 100.f, 1.f)
#define DEFAULT_SCALE_HAS_PARENT Vec3(1.f, 1.f, 1.f)

// TODO : 나중에 3D 방향벡터로 구현
enum class DIRECTION_VEC : UINT
{
	RIGHT, UP, FRONT, COUNT_END
};

// 2D 방향벡터
enum class DIRECTION_2D : UINT
{
	LEFT, RIGHT, UP, DOWN
};

static Vec2 Direction2dValueArr[]
	= { Vec2(-1, 0)
	, Vec2(1, 0)
	, Vec2(0, 1)
	, Vec2(0, -1) };

static const char* Direction2dNameArr[] 
	= { "Left"
	, "Right"
	, "Up"
	, "Down" };

static int Direction2dNameArrSize = sizeof(Direction2dNameArr) / sizeof(const char*);