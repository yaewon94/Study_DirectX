#pragma once
#include "Script.h"
#include "KeyEnums.h"

// 플레이어 컴포넌트
class Player final : public Script
{
	NO_COPY_ASSIGN(Player);

public:
	Player(const Ptr<GameObject>& owner);
	Player(const Ptr<Script>& origin, const Ptr<GameObject>& owner);
	~Player();

	virtual Ptr<Script> Clone(const Ptr<Script>& origin, const Ptr<GameObject>& owner) final
	{
		return Ptr<Player>(origin, owner).ptr_dynamic_cast<Script>();
	}

public:
	virtual void Tick() final {}

public:
	void Move(KEY_CODE key);

public:
	virtual void OnCollisionEnter(LAYER_TYPE other) final;
	virtual void OnCollisionStay(LAYER_TYPE other) final {}
	virtual void OnCollisionExit(LAYER_TYPE other) final {}
};