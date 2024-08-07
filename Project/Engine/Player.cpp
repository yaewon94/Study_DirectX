#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "GameObject.h"

Player::Player(const GameObject& Owner) : Script(Owner)
{
}

Player::Player(const Player& origin, const GameObject& Owner) : Script(origin, Owner)
{
}

Player::~Player()
{
}

void Player::Init()
{
	transform = GetOwner().GetComponent<Transform>();
}

void Player::Tick()
{
}

void Player::Move(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	// 방향에 맞게 오브젝트 이동
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	// Transform 컴포넌트에 반영
	transform->SetPosX(transform->GetPos().x + dir * DT);
	transform->Bind();
}