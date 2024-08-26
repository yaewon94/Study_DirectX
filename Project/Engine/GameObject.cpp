#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Script.h"

GameObject::GameObject() : components{}
{
	transform = AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin) : components{}
{
	*this = origin;
}

GameObject::~GameObject()
{
}

GameObject& GameObject::operator=(const GameObject& other)
{
	for (int i=0; i<components.size(); ++i)
	{
		components[i] = other.components[i];
	}

	scripts.resize(other.scripts.size());
	for (int i=0; i<scripts.size(); ++i)
	{
		scripts[i] = other.scripts[i];
	}

	return *this;
}

Ptr<Transform> GameObject::GetTransform()
{
	return transform;
}

void GameObject::Init()
{
	for (auto& component : components)
	{
		component->Init();
	}
}

void GameObject::Tick()
{
	for (auto& script : scripts)
	{
		script->Tick();
	}
}

void GameObject::FinalTick()
{
	for (auto& component : components)
	{
		component->FinalTick();
	}
}

void GameObject::Render()
{
	if (meshRender != nullptr) meshRender->Render();
}