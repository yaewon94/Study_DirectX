#pragma once

// 키 값
enum KEY_CODE
{
	LEFT = VK_LEFT, RIGHT = VK_RIGHT
};

// 키 상태
enum class KEY_STATE
{
	NONE, TAP, KEY_DOWN, RELEASED
};