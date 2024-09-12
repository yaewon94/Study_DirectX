#include "pch.h"
#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "RenderComponent.h"
#include "Script.h"

GameObject::GameObject() : layer(LAYER_TYPE::NONE), renderComponent(Ptr<RenderComponent>(nullptr))
{
	AddComponent<Transform>();
}

GameObject::GameObject(const GameObject& origin) 
{
	*this = origin;
}

GameObject::~GameObject()
{
}

GameObject& GameObject::operator=(const GameObject& other)
{
	layer = other.layer;
	name = other.name;

	auto pObj = Ptr<GameObject>(this);

	for (auto& component : other.componentMap)
	{
		auto& origin = component.second;
		componentMap.insert(make_pair(component.first, origin->Clone(origin, pObj)));
	}

	renderComponent = GetComponent<RenderComponent>();
	transform = GetComponent<Transform>();

	scripts.resize(other.scripts.size());
	for (int i=0; i<scripts.size(); ++i)
	{
		auto& origin = other.scripts[i];
		scripts[i] = origin->Clone(origin, pObj);
	}

	return *this;
}

Ptr<Transform> GameObject::GetTransform()
{
	return transform;
}

void GameObject::Init()
{
	for (auto& component : componentMap)
	{
		component.second->Init();
	}

	for (auto& script : scripts)
	{
		script->Init();
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
	for (auto& component : componentMap)
	{
		component.second->FinalTick();
	}
}

void GameObject::Render()
{
	if (renderComponent != nullptr) renderComponent->Render();
}