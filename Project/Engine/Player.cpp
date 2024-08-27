#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Transform.h"

Player::Player(const Ptr<GameObject>& owner) : Script(owner)
{
}

Player::Player(const Player& origin, const Ptr<GameObject>& owner) : Script(origin, owner)
{
}

Player::~Player()
{
}

void Player::Init()
{
	transform = GetOwner()->GetTransform();
}

void Player::Move(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	// 방향에 맞게 오브젝트 이동
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	// Transform 컴포넌트에 반영
	transform->SetPosX(transform->GetLocalPos().x + dir * DT);

	// [TEST] 크기 변경
	transform->SetScaleX(transform->GetLocalScale().x * DT);
}