#pragma once

#define MAX_LAYER_TYPES 0x7fffffff

// enum class LAYER_TYPE 값들을 | 로 조합한 결과
using LAYER_TYPES = int;

// 레이어 타입 (value : 렌더링 순서)
// TODO : 2의 배수로 늘릴 것
enum LAYER_TYPE : int
{
	NONE = -100,
	LIGHT = -1,
	CAMERA = 0,

	// LAYER_TYPES(int) 에 조합 가능한 레이어들
	DEFAULT = 1,
	GROUND = DEFAULT << 1,
	MONSTER = GROUND << 1,
	PLAYER = MONSTER << 1,
	SKILL = PLAYER << 1,
#ifdef _DEBUG
	DEBUG = SKILL << 1,
#endif // _DEBUG
	// 0x40000000 // MAX
};

#ifdef _DEBUG
static tuple<LAYER_TYPE, const char*> LayerTypeArr[]
= { tuple(DEFAULT, "Default")
, tuple(GROUND, "Ground")
, tuple(MONSTER, "Monster")
, tuple(PLAYER, "Player")
, tuple(SKILL, "Skill")
, tuple(DEBUG, "Debug")};
#elif
static tuple<LAYER_TYPE, const char*> LayerTypeArr[]
= { tuple(DEFAULT, "Default")
, tuple(GROUND, "Ground")
, tuple(MONSTER, "Monster")
, tuple(PLAYER, "Player")
, tuple(SKILL, "Skill") };
#endif // _DEBUG