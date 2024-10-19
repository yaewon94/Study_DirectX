#include "pch.h"
#include "Player.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Material.h"
#include "Collider2D.h"
#include "AssetManager.h"
#include "Sprite.h"
#include "Texture.h"
#include "Animator2D.h"

Player::Player(const Ptr<GameObject>& owner) 
	: Script(owner)
{
	// 이름, 좌표 설정
	owner->SetName(L"Player");
	owner->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 0.f));

	//=======================================
	// 컴포넌트 추가
	// ======================================
	// 콜라이더 추가
	owner->AddComponent<Collider2D>();
	// 애니메이터 추가
	Ptr<Sprite> sprite = AssetManager::GetInstance()->AddAsset<Sprite>("PlayerIdleSprite", "");
	sprite->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>("PlayerIdleTexture", "Player/Idle.png"), 3);
	Ptr<Animator2D> animator = owner->AddComponent<Animator2D>();
	animator->AddSprite("Idle", sprite);
	animator->ChangeAnimation("Idle");

	//=======================================
	// 레이어 설정 (레벨에 오브젝트 등록)
	// ======================================
	owner->SetLayer(LAYER_TYPE::PLAYER);
}

Player::Player(const Ptr<Script>& origin, const Ptr<GameObject>& owner) 
	: Script(origin, owner)
{
	owner->SetLayer(LAYER_TYPE::PLAYER);
}

Player::~Player()
{
}

void Player::Move(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;
	Ptr<Transform>tr = GetOwner()->GetTransform();

	// 방향에 맞게 오브젝트 이동
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	// Transform 컴포넌트에 반영
	tr->SetLocalPosX(tr->GetLocalPos().x + dir * DT * 500.f);

	// [TEST] 크기 변경
	//transform->SetLocalScaleX(transform->GetLocalScale().x * 0.1f * DT);

	// [TEST] 회전
	//transform->SetLocalRotationZ(transform->GetLocalRotation().z + (DT * XM_PI));
}

void Player::OnCollisionEnter(LAYER_TYPE other)
{
	if (other & LAYER_TYPE::MONSTER)
	{
		//MessageBox(nullptr, L"You Lose", L"Game Over", MB_OK);
	}
}