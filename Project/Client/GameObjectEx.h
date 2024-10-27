#pragma once
#include "Engine/GameObject.h"

// 에디터 모드 게임 오브젝트
class GameObjectEx final : public GameObject
{
public:
	GameObjectEx();
	GameObjectEx(const GameObjectEx& origin);
	~GameObjectEx();
	// TODO : 부모 = 연산자 자동 호출되는지 확인
	GameObjectEx& operator=(const GameObjectEx& other);

public:
	virtual void SetLayer(LAYER_TYPE layer) final;

public:
	virtual void FinalTick() final;
};