#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Material.h"

Player::Player(const Ptr<GameObject>& owner) 
	: Script(owner), paperBurnIntense(0.0f)
{
}

Player::Player(const Ptr<Script>& origin, const Ptr<GameObject>& owner) 
	: Script(origin, owner), paperBurnIntense(0.0f)
{
	auto component = origin.ptr_dynamic_cast<Player>();
	paperBurnIntense = component->paperBurnIntense;
}

Player::~Player()
{
}

void Player::Init()
{
	transform = GetOwner()->GetComponent<Transform>();
}

void Player::Tick()
{
	// TEST : paper burn material
	float DT = TimeManager::GetInstance()->GetDeltaTime();

	paperBurnIntense += DT * 0.4f;

	Ptr<Material> material = GetOwner()->GetComponent<RenderComponent>()->GetMaterial();
	material->SetScalarParam(FLOAT_0, paperBurnIntense);
}

void Player::Move(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	// 방향에 맞게 오브젝트 이동
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	// Transform 컴포넌트에 반영
	transform->SetPosX(transform->GetLocalPos().x + dir * DT * 500.f);

	// [TEST] 크기 변경
	//transform->SetScaleX(transform->GetLocalScale().x * 0.1f * DT);

	// [TEST] 회전
	//transform->SetRotationZ(transform->GetLocalRotation().z + (DT * XM_PI));
}