#pragma once

#define MAX_LAYER_TYPES 0xffffffff

// enum class LAYER_TYPE 값들을 | 로 조합한 결과
using LAYER_TYPES = UINT;

// 레이어 타입 (value : 렌더링 순서)
// TODO : 2의 배수로 늘릴 것
enum LAYER_TYPE : UINT
{
	CAMERA = 0,

	// LAYER_TYPES(int) 에 조합 가능한 레이어들
	DEFAULT = 0b1,
	MONSTER = 0b10,
	PLAYER = 0b100,
	SKILL = 0b1000,
	DEBUG = 0x80000000 // MAX
};