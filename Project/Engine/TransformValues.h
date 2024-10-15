#pragma once

#define DEFAULT_SCALE_NO_PARENT Vec3(100.f, 100.f, 1.f)
#define DEFAULT_SCALE_HAS_PARENT Vec3(1.f, 1.f, 1.f)

// πÊ«‚∫§≈Õ
enum class DIRECTION_VEC : UINT
{
	RIGHT, UP, FRONT, LEFT, DOWN, BACK, COUNT_END
};

static array<Vec3, (UINT)DIRECTION_VEC::COUNT_END> Directions =
{
	Vec3(1, 0, 0),
	Vec3(0, 1, 0),
	Vec3(0, 0, 1),
	Vec3(-1, 0, 0),
	Vec3(0, -1, 0),
	Vec3(0, 0, -1)
};