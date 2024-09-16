#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Material.h"

Player::Player(const Ptr<GameObject>& owner) 
	: Script(owner)
{
}

Player::Player(const Ptr<Script>& origin, const Ptr<GameObject>& owner) 
	: Script(origin, owner)
{
}

Player::~Player()
{
}

void Player::Init()
{
	transform = GetOwner()->GetComponent<Transform>();
}

void Player::Move(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	// 방향에 맞게 오브젝트 이동
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	// Transform 컴포넌트에 반영
	transform->SetLocalPosX(transform->GetLocalPos().x + dir * DT * 500.f);

	// [TEST] 크기 변경
	//transform->SetLocalScaleX(transform->GetLocalScale().x * 0.1f * DT);

	// [TEST] 회전
	//transform->SetLocalRotationZ(transform->GetLocalRotation().z + (DT * XM_PI));
}