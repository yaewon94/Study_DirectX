#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Component.h"
#include "Transform.h"
#include "RenderManager.h"
#include "RenderComponent.h"
#include "Script.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Light.h"

GameObject::GameObject() 
	: m_layer(LAYER_TYPE::NONE)
	, m_renderComponent(nullptr)
	, m_collider(nullptr)
	, m_light(nullptr)
	, m_parent(nullptr)
	, m_isDead(false)
{
	m_transform = AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin)
	: m_name(origin.m_name)
	, m_layer(LAYER_TYPE::NONE)
	, m_renderComponent(nullptr)
	, m_collider(nullptr)
	, m_light(nullptr)
	, m_parent(nullptr)
	, m_isDead(origin.m_isDead)
{
	*this = origin;
}

GameObject::~GameObject()
{
}

GameObject& GameObject::operator=(const GameObject& other)
{
	if (this != &other)
	{
		auto pObj = Ptr<GameObject>(this);

		// �⺻ ���� ������Ʈ ����
		// TODO : AddComponent() ȣ���ؼ� ó���ϵ��� ����
		for (auto& component : other.m_components)
		{
			auto& origin = component.second;
			auto clone = origin->Clone(origin, pObj);
			COMPONENT_TYPE baseType = clone->GetBaseType();
			m_components.insert(make_pair(component.first, clone));
			
			if (baseType == COMPONENT_TYPE::RENDER) m_renderComponent = clone.ptr_dynamic_cast<RenderComponent>();
			else if (baseType == COMPONENT_TYPE::COLLIDER) m_collider = clone.ptr_dynamic_cast<Collider>();
			else if (baseType == COMPONENT_TYPE::LIGHT) m_light = clone.ptr_dynamic_cast<Light>();
		}

		m_transform = GetComponent<Transform>();
		
		// ����� ���� ������Ʈ ����
		m_scripts.resize(other.m_scripts.size());
		for (int i = 0; i < m_scripts.size(); ++i)
		{
			auto& origin = other.m_scripts[i];
			m_scripts[i] = origin->Clone(origin, pObj);
		}

		// �ڽ� ������Ʈ ����
		for (auto& child : other.m_children)
		{
			m_children.push_back(child.DeepCopy());
		}

		// ���̾� ����
		SetLayer(other.m_layer);
	}

	return *this;
}

Ptr<Transform> GameObject::GetTransform()
{
	return m_transform;
}

Ptr<RenderComponent> GameObject::GetRenderComponent()
{
	return m_renderComponent;
}

void GameObject::SetLayer(LAYER_TYPE layer)
{
	if (m_layer == layer) return;

	Ptr<GameObject> obj = Ptr<GameObject>(this);

	// ������ ���
	if (RenderManager::GetInstance()->IsEditorMode())
	{
		if (m_collider != nullptr) CollisionManager::GetInstance()->RemoveCollider(m_collider);

		m_layer = layer;
		if (m_collider != nullptr) CollisionManager::GetInstance()->AddCollider(m_collider);
	}
	// �ΰ��� ���
	else
	{
		LevelManager::GetInstance()->DeleteObject(obj);
		if (m_collider != nullptr) CollisionManager::GetInstance()->RemoveCollider(m_collider);

		m_layer = layer;
		LevelManager::GetInstance()->AddObject(obj);
		if (m_collider != nullptr) CollisionManager::GetInstance()->AddCollider(m_collider);
	}
}

void GameObject::AddChild(const Ptr<GameObject>& child, bool isSameLayer)
{
	if(isSameLayer) child->SetLayer(m_layer);
	child->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));	// ����Ʈ�� : �θ�� ���� ũ��
	child->m_parent = Ptr<GameObject>(this);
	m_children.push_back(child);
}

void GameObject::Init()
{
	for (auto& component : m_components)
	{
		component.second->Init();
	}

	for (auto& script : m_scripts)
	{
		script->Init();
	}
}

void GameObject::Tick()
{
	for (auto& script : m_scripts)
	{
		script->Tick();
	}
}

void GameObject::FinalTick()
{
	for (auto& component : m_components)
	{
		component.second->FinalTick();
	}

	// TODO : �ڽ� ������Ʈ�� ���� ����� �Ǹ� �ڷᱸ�� list�� ����
	// ������ ���
	if (RenderManager::GetInstance()->IsEditorMode())
	{
		for (auto iter = m_children.begin(); iter != m_children.end();)
		{
			if ((*iter)->IsDead())
			{
				if ((*iter)->m_collider != nullptr) CollisionManager::GetInstance()->RemoveCollider((*iter)->m_collider);
				iter = m_children.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
	// �ΰ��� ���
	else
	{
		for (auto iter = m_children.begin(); iter != m_children.end();)
		{
			if ((*iter)->IsDead())
			{
				LevelManager::GetInstance()->DeleteObject(*iter);
				if ((*iter)->m_collider != nullptr) CollisionManager::GetInstance()->RemoveCollider((*iter)->m_collider);
				iter = m_children.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

}

void GameObject::Render()
{
	m_renderComponent->Render();
}

void GameObject::OnCollisionEnter(LAYER_TYPE other)
{
	for (auto& script : m_scripts)
	{
		script->OnCollisionEnter(other);
	}
}

void GameObject::OnCollisionStay(LAYER_TYPE other)
{
	for (auto& script : m_scripts)
	{
		script->OnCollisionStay(other);
	}
}

void GameObject::OnCollisionExit(LAYER_TYPE other)
{
	for (auto& script : m_scripts)
	{
		script->OnCollisionExit(other);
	}
}