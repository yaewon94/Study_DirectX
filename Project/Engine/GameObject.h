#pragma once
#include "Entity.h"
#include "Component.h"
#include "MeshRender.h"

// 게임오브젝트
class GameObject final : public Entity
{
private:
	array<Component*, (UINT)COMPONENT_TYPE::COUNT_END> components;
	Ptr<MeshRender> meshRender;

public:
	GameObject();
	~GameObject();
	GameObject* const Clone() { return new GameObject(*this); }

public:
	template<typename T> requires std::derived_from<T, Component> Ptr<T> AddComponent();
	template<typename T> requires std::derived_from<T, Component> Ptr<T> GetComponent();

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

private:
	GameObject(const GameObject& origin);
	GameObject& operator=(const GameObject& other);
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
		Ptr<T> ptr(t);
		components[(UINT)T::Type] = t;

		if (T::Type == COMPONENT_TYPE::MESH_RENDER) meshRender = Ptr<MeshRender>((MeshRender*)t);

		return ptr;
	}
}

template<typename T> requires std::derived_from<T, Component>
Ptr<T> GameObject::GetComponent()
{
	Component* component = components[(UINT)T::Type];

	if (component != nullptr) return Ptr<T>((T*)component);
	else return Ptr<T>();
}