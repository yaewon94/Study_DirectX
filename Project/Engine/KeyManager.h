#pragma once
#include "KeyEnums.h"

class Player;

// 사용자 입력 처리 클래스
class KeyManager final : public Singleton<KeyManager>
{
	SINGLETON(KeyManager);

private:
	map<KEY_CODE, KEY_STATE> keyMap;
	Vec2 mousePos;
	Ptr<Player> player;

public:
	void Init();
	void Tick();

public:
	void AddKey(KEY_CODE keyCode);
};