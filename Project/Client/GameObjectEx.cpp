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

	// ���� ���̾� ó��
	if (m_collider != nullptr) CollisionManager::GetInstance()->RemoveCollider(m_collider);

	// ���ο� ���̾� ó��
	m_layer = layer;
	if (m_collider != nullptr) CollisionManager::GetInstance()->AddCollider(m_collider);
}

void GameObjectEx::FinalTick()
{
	for (auto& component : m_components)
	{
		component.second->FinalTick();
	}

	// ������ �� �ڽ� ������Ʈ üũ
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