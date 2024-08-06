#include "pch.h"
#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() : components{}
{
	AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin) : components{}
{
	for (int i=0; i<components.size(); ++i)
	{
		if(origin.components[i] != nullptr) components[i] = origin.components[i]->Clone(*this);
	}
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