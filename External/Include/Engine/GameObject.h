#pragma once
#include "Entity.h"
#include "ComponentEnums.h"

class Component;
class Transform;
class MeshRender;
class Script;

// 게임오브젝트
class GameObject final : public Entity
{
private:
	array<Ptr<Component>, (UINT)COMPONENT_TYPE::COUNT_END> components;
	Ptr<Transform> transform;
	Ptr<MeshRender> meshRender;
	vector<Ptr<Script>> scripts;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	Ptr<Transform> GetTransform();

public:
	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> AddComponent()
	{
		Ptr<T> component = GetComponent<T>();

		if (component != nullptr)
		{
			MessageBoxA(nullptr, "이미 해당 컴포넌트가 존재합니다", "컴포넌트 추가 실패", MB_OK);
			return component;
		}
		else
		{
			COMPONENT_TYPE type = GetType<T>();
			component = Ptr<T>(Ptr<GameObject>(this));

			if (type == COMPONENT_TYPE::SCRIPT)
			{
				scripts.push_back(component.ptr_dynamic_cast<Script>());
			}
			else
			{
				if (type == COMPONENT_TYPE::MESH_RENDER) meshRender = component;
				//else if (type == COMPONENT_TYPE::TRANSFORM) transform = component; // [ERROR : C2027]

				components[(UINT)type] = component.ptr_dynamic_cast<Component>();
			}

			return component;
		}
	}

	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> GetComponent()
	{
		COMPONENT_TYPE type = GetType<T>();

		if (type == COMPONENT_TYPE::SCRIPT)
		{
			for (auto& script : scripts)
			{
				Ptr<T> component = script.ptr_dynamic_cast<T>();
				if (component != nullptr) return component;
			}

			return nullptr;
		}
		else
		{
			return components[(UINT)type].ptr_dynamic_cast<T>();
		}
	}

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

private:
	GameObject(GameObject&&) = delete;
	GameObject& operator=(GameObject&&) = delete;
};