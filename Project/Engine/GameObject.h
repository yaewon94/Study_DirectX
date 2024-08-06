#pragma once
#include "Entity.h"
#include "Component.h"

class GameObject final : public Entity
{
private:
	array<Component*, (UINT)COMPONENT_TYPE::COUNT_END> components;

public:
	template<typename T> requires std::derived_from<T, Component> Ptr<T> AddComponent();
	template<typename T> requires std::derived_from<T, Component> Ptr<T> GetComponent();

public:
	GameObject();
	~GameObject();

public:
	GameObject* Clone() { return new GameObject(*this); }

private:
	GameObject(const GameObject& origin);

private:	// delete
	GameObject& operator=(const GameObject&) = delete;
};

template<typename T> requires std::derived_from<T, Component>
Ptr<T> GameObject::AddComponent()
{
	Ptr<T> component = GetComponent<T>();

	if (component.Get() != nullptr)
	{
		MessageBoxA(nullptr, "이미 해당 컴포넌트가 존재합니다", "컴포넌트 추가 실패", MB_OK);
		return component;
	}
	else
	{
		T* t = new T(*this);
		components[(UINT)T::Type] = t;
		return Ptr<T>(t);
	}
}

template<typename T> requires std::derived_from<T, Component>
Ptr<T> GameObject::GetComponent()
{
	Component* component = components[(UINT)T::Type];

	if (component != nullptr) return Ptr<T>((T*)component);
	else return Ptr<T>();
}