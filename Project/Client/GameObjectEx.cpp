#include "pch.h"
#include "GameObjectEx.h"
#include "Engine/CollisionManager.h"
#include "Engine/Collider.h"

GameObjectEx::GameObjectEx()
{
}

GameObjectEx::GameObjectEx(const GameObjectEx& origin) 
	: GameObject(origin)
{
}

GameObjectEx::~GameObjectEx()
{
}

GameObjectEx& GameObjectEx::operator=(const GameObjectEx& other)
{
	return *this;
}

void GameObjectEx::SetLayer(LAYER_TYPE layer)
{
	if (GetLayer() == layer) return;

	// 이전 레이어 처리
	if (m_collider != nullptr) CollisionManager::GetInstance()->RemoveCollider(m_collider);

	// 새로운 레이어 처리
	m_layer = layer;
	if (m_collider != nullptr) CollisionManager::GetInstance()->AddCollider(m_collider);
}

void GameObjectEx::FinalTick()
{
	for (auto& component : m_components)
	{
		component.second->FinalTick();
	}

	// 지워야 할 자식 오브젝트 체크
	for (auto iter = m_children.begin(); iter != m_children.end();)
	{
		if ((*iter)->IsDead())
		{
			if ((*iter)->GetCollider() != nullptr) CollisionManager::GetInstance()->RemoveCollider((*iter)->GetCollider());
			iter = m_children.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}