#include "pch.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "Component.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Script.h"
#include "CollisionManager.h"
#include "Collider2D.h"

GameObject::GameObject() 
	: m_layer(LAYER_TYPE::NONE)
	, m_renderComponent(nullptr)
	, m_parent(nullptr)
{
	m_transform = AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin)  
	: m_name(origin.m_name), m_layer(origin.m_layer), m_parent(origin.m_parent)
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

		// 기본 엔진 컴포넌트 복제
		for (auto& component : other.m_components)
		{
			auto& origin = component.second;
			m_components.insert(make_pair(component.first, origin->Clone(origin, pObj)));
		}

		m_renderComponent = GetComponent<RenderComponent>();
		m_transform = GetComponent<Transform>();

		// 사용자 정의 컴포넌트 복제
		m_scripts.resize(other.m_scripts.size());
		for (int i = 0; i < m_scripts.size(); ++i)
		{
			auto& origin = other.m_scripts[i];
			m_scripts[i] = origin->Clone(origin, pObj);
		}

		// 자식 오브젝트 복제
		for (auto& child : other.m_children)
		{
			m_children.push_back(child->Clone());
		}
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
	Ptr<GameObject> obj = Ptr<GameObject>(this);
	Ptr<Collider2D> collider = GetComponent<Collider2D>();

	if (m_layer != LAYER_TYPE::NONE)
	{
		// 기존 레이어에 등록된 오브젝트 삭제
		LevelManager::GetInstance()->DeleteObject(obj);

		// 기존 레이어 타입으로 등록된 콜라이더 삭제
		if (collider != nullptr)
		{
			CollisionManager::GetInstance()->RemoveCollider(collider);
		}
	}

	// 새로운 레이어에 오브젝트 등록
	m_layer = layer;
	LevelManager::GetInstance()->AddObject(obj);

	// 새로운 레이어 타입으로 콜라이더 등록
	if (collider != nullptr)
	{
		CollisionManager::GetInstance()->AddCollider(collider);
	}
}

void GameObject::AddChild(const Ptr<GameObject>& child, bool isSameLayer)
{
	if(isSameLayer) child->SetLayer(m_layer);
	child->GetTransform()->SetLocalScale(Vec3(1.f, 1.f, 1.f));	// 디폴트값 : 부모와 같은 크기
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