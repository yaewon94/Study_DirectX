#include "pch.h"
#include "KeyManager.h"
#include "Engine.h"
#include "Player.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Level.h"

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

void KeyManager::Init()
{
	// 키 값 초기화
	AddKey(KEY_CODE::LEFT);
	AddKey(KEY_CODE::RIGHT);

	// 플레이어 초기화
	player = LevelManager::GetInstance()->GetGameObject(LAYER_TYPE::PLAYER)->GetComponent<Player>();
}

void KeyManager::Tick()
{
	// 윈도우가 포커싱 중일때
	if (Engine::GetInstance()->GetHwnd() == GetFocus())
	{
		for (auto& key : keyMap)
		{
			// 이번 프레임에 해당 키가 눌림
			if (GetAsyncKeyState(key.first) & 0x8001)
			{
				if (key.second == KEY_STATE::NONE) key.second = KEY_STATE::TAP;
				else if (key.second == KEY_STATE::TAP) key.second = KEY_STATE::KEY_DOWN;

				// TODO : 각각 KEY마다 호출하는 함수 일반화 하기
				player->Move(key.first);	// 임시코드
			}
			// 안눌림
			else
			{
				if (key.second == KEY_STATE::NONE) continue;
				else if (key.second == KEY_STATE::RELEASED) key.second = KEY_STATE::NONE;
				else key.second = KEY_STATE::RELEASED;
			}
		}

		// 마우스 좌표 체크
		POINT pos;
		GetCursorPos(&pos);
		ScreenToClient(Engine::GetInstance()->GetHwnd(), &pos);
		mousePos = Vec2((float)pos.x, (float)pos.y);
	}
	// 윈도우가 포커싱 중이 아님
	else
	{
		for (auto& key : keyMap)
		{
			key.second = KEY_STATE::NONE;
		}
	}
}

void KeyManager::AddKey(KEY_CODE keyCode)
{
	const auto iter = keyMap.find(keyCode);

	if (iter != keyMap.end())
	{
		keyMap.erase(iter);
	}

	keyMap.insert(make_pair(keyCode, KEY_STATE::NONE));
}