#include "pch.h"
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() : components{}
{
	AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin) : components{}
{
	*this = origin;
}

GameObject::~GameObject()
{
	for (auto component : components)
	{
		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
	}
}

GameObject& GameObject::operator=(const GameObject& other)
{
	// 내가 가지고 있던 컴포넌트 삭제
	for (auto component : components)
	{
		if (component != nullptr)
		{
			delete component;
			component = nullptr;
		}
	}

	// other이 가지고 있는 컴포넌트 복제
	for (int i = 0; i < components.size(); ++i)
	{
		if (other.components[i] != nullptr) components[i] = other.components[i]->Clone(*this);
	}

	return *this;
}

void GameObject::Init()
{
	for (auto component : components)
	{
		if (component != nullptr) component->Init();
	}
}

void GameObject::Tick()
{
	for (auto component : components)
	{
		if (component != nullptr) component->Tick();
	}
}

void GameObject::FinalTick()
{
	for (auto component : components)
	{
		if (component != nullptr) component->FinalTick();
	}
}

void GameObject::Render()
{
	if (meshRender.Get() != nullptr) meshRender->Render();
}