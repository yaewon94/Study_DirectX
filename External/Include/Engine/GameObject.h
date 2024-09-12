#pragma once
#include "Entity.h"
#include "ComponentEnums.h"
#include "LayerEnums.h"

class Component;
class Transform;
class Script;
class RenderComponent;

// 게임오브젝트
class GameObject final : public Entity
{
private:
	wstring name;
	LAYER_TYPE layer;

	map<COMPONENT_TYPE, Ptr<Component>> componentMap;
	vector<Ptr<Script>> scripts;
	Ptr<RenderComponent> renderComponent;

	// GetComponent 없이 바로 이용할 수 있게
	Ptr<Transform> transform;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	const wstring& GetName() { return name; }
	LAYER_TYPE GetLayer() { return layer; }
	Ptr<Transform> GetTransform();

	void SetName(const wstring& name) { this->name = name; }
	void SetLayer(LAYER_TYPE layer) { this->layer = layer; }

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
			constexpr COMPONENT_TYPE Type = GetType<T>();
			component = Ptr<T>(Ptr<GameObject>(this));

			// 사용자 정의 컴포넌트
			if constexpr (Type == COMPONENT_TYPE::SCRIPT)
			{
				scripts.push_back(component.ptr_dynamic_cast<Script>());
			}
			// 게임엔진 기본 컴포넌트
			else
			{
				// 렌더링 컴포넌트 여부
				if constexpr (IsRenderComponent<T>())
				{
					if (renderComponent == nullptr)
					{
						renderComponent = component.ptr_dynamic_cast<RenderComponent>();
					}
					else
					{
						MessageBox(nullptr, L"렌더링 컴포넌트가 이미 존재합니다", L"컴포넌트 추가 실패", MB_OK);
						return nullptr;
					}
				}
				else if constexpr (Type == COMPONENT_TYPE::TRANSFORM) transform = component;

				componentMap.insert(make_pair(Type, component.ptr_dynamic_cast<Component>()));
			}

			return component;
		}
	}

	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> GetComponent()
	{
		constexpr COMPONENT_TYPE Type = GetType<T>();

		// 사용자 정의 컴포넌트
		if constexpr (Type == COMPONENT_TYPE::SCRIPT)
		{
			for (auto& script : scripts)
			{
				Ptr<T> component = script.ptr_dynamic_cast<T>();
				if (component != nullptr) return component;
			}

			return nullptr;
		}
		// 렌더링 컴포넌트
		else if constexpr (Type == COMPONENT_TYPE::RENDER)
		{
			return renderComponent;
		}
		// 게임엔진 기본 컴포넌트
		else
		{
			const auto iter = componentMap.find(Type);
			if (iter == componentMap.end()) return nullptr;
			else return iter->second.ptr_dynamic_cast<T>();
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