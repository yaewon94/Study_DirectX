#pragma once
#include "Entity.h"
#include "Component.h"
#include "MeshRender.h"
#include "Transform.h"

class Script;

// 게임오브젝트
class GameObject final : public Entity
{
public:
	static GameObject* Create() { return new GameObject; }

private:
	array<Component*, (UINT)COMPONENT_TYPE::COUNT_END> components;
	Ptr<MeshRender> meshRender;
	vector<Script*> scripts;

private:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	GameObject* Clone() { return new GameObject(*this); }
	void Destroy() { delete this; }

public:
	template<typename T> requires std::derived_from<T, Component> Ptr<T> AddComponent();
	template<typename T> requires std::derived_from<T, Component> Ptr<T> GetComponent() const;

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();
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
		T* t = Component::Create<T>(*this);
		Ptr<T> ptr(t);
		COMPONENT_TYPE type = Component::GetType<T>();

		if (type == COMPONENT_TYPE::SCRIPT)
		{
			scripts.push_back((Script*)t);
		}
		else
		{
			components[(UINT)type] = t;

			if (type == COMPONENT_TYPE::MESH_RENDER) meshRender = Ptr<MeshRender>((MeshRender*)t);
		}

		return ptr;
	}
}

template<typename T> requires std::derived_from<T, Component>
Ptr<T> GameObject::GetComponent() const
{
	COMPONENT_TYPE type = Component::GetType<T>();
	Component* component = nullptr;

	if (type == COMPONENT_TYPE::SCRIPT)
	{
		for (auto script : scripts)
		{
			component = dynamic_cast<T*>(script);
			if (component != nullptr) return Ptr<T>((T*)component);
		}
	}
	else
	{
		component = components[(UINT)type];
		if (component != nullptr) return Ptr<T>((T*)component);
	}

	return Ptr<T>();
}