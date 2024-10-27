#pragma once
#include "Engine/GameObject.h"

// ������ ��� ���� ������Ʈ
class GameObjectEx final : public GameObject
{
public:
	GameObjectEx();
	GameObjectEx(const GameObjectEx& origin);
	~GameObjectEx();
	// TODO : �θ� = ������ �ڵ� ȣ��Ǵ��� Ȯ��
	GameObjectEx& operator=(const GameObjectEx& other);

public:
	virtual void SetLayer(LAYER_TYPE layer) final;

public:
	virtual void FinalTick() final;
};