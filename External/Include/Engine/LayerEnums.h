#pragma once

// enum class LAYER_TYPE 값들을 | 로 조합한 결과
using LAYER_TYPES = UINT;

// 레이어 타입
// TODO : 2의 배수로 늘릴 것(+값들만), MAX(0x40000000)
enum class LAYER_TYPE
{
	CAMERA = -2,
	NONE = -1,

	// LAYER_TYPES 에 조합 가능한 레이어들
	PLAYER = 0,
};