#pragma once
#include "Script.h"
#include "Transform.h"

class GameObject;

// 플레이어 컴포넌트
class Player final : public Script
{
	NO_COPY_ASSIGN(Player);

private:
	Ptr<Transform> transform;

private:
	template<typename T> requires std::derived_from<T, Component>
	friend static T* Component::Create(const GameObject& Owner);

	Player(const GameObject& Owner);
	Player(const Player& origin, const GameObject& Owner);
	~Player();

public:
	virtual Player* Clone(const GameObject& Owner) final { return new Player(*this, Owner); }

public:
	virtual void Init() final;
	virtual void Tick() final;

public:
	void Move(KEY_CODE key);
};