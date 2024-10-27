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
	// �̸�, ��ǥ ����
	owner->SetName("Player");
	owner->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 0.f));

	//=======================================
	// ������Ʈ �߰�
	// ======================================
	// �ݶ��̴� �߰�
	owner->AddComponent<Collider2D>();
	// �ִϸ����� �߰�
	Ptr<Sprite> sprite = AssetManager::GetInstance()->AddAsset<Sprite>("PlayerIdleSprite", "");
	sprite->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>("PlayerIdleTexture", "Player/Idle.png"), 3);
	Ptr<Animator2D> animator = owner->AddComponent<Animator2D>();
	animator->AddSprite("Idle", sprite);
	animator->ChangeAnimation("Idle");

	//=======================================
	// ���̾� ���� (������ ������Ʈ ���)
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

	// ���⿡ �°� ������Ʈ �̵�
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	// Transform ������Ʈ�� �ݿ�
	tr->SetLocalPosX(tr->GetLocalPos().x + dir * DT * 500.f);

	// [TEST] ũ�� ����
	//transform->SetLocalScaleX(transform->GetLocalScale().x * 0.1f * DT);

	// [TEST] ȸ��
	//transform->SetLocalRotationZ(transform->GetLocalRotation().z + (DT * XM_PI));
}

void Player::OnCollisionEnter(LAYER_TYPE other)
{
	if (other & LAYER_TYPE::MONSTER)
	{
		//MessageBox(nullptr, L"You Lose", L"Game Over", MB_OK);
	}
}