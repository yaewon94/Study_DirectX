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

// 사용자 입력 처리 클래스
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	map<KEY_CODE, KEY_STATE> keyMap;
	Vec2 mousePos;

public:
	void Init();
	void Tick();

public:
	void AddKey(KEY_CODE keyCode);
};