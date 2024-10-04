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
	wstring m_name;
	LAYER_TYPE m_layer;

	map<COMPONENT_TYPE, Ptr<Component>> m_components;	// 엔진 기본 컴포넌트만 등록
	vector<Ptr<Script>> m_scripts;						// 사용자 정의 컴포넌트 등록

	Ptr<Transform> m_transform;
	Ptr<RenderComponent> m_renderComponent;

	Ptr<GameObject> m_parent;
	vector<Ptr<GameObject>> m_children;

public:
	GameObject();
	~GameObject();
	Ptr<GameObject> Clone() { return Ptr<GameObject>(*this); }

public:
	const wstring& GetName() { return m_name; }
	LAYER_TYPE GetLayer() { return m_layer; }
	Ptr<GameObject> GetParent() { return m_parent; }

	// 컴포넌트 빨리 접근하기 위한 용도
	Ptr<Transform> GetTransform();
	Ptr<RenderComponent> GetRenderComponent();

	void SetName(const wstring& name) { m_name = name; }
	// 0 이상의 값만 현재 Level에 등록됨
	void SetLayer(LAYER_TYPE layer);
	void AddChild(const Ptr<GameObject>& child, bool isSameLayer = true);

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
				m_scripts.push_back(component.ptr_dynamic_cast<Script>());
			}
			// 게임엔진 기본 컴포넌트
			else
			{
				// 렌더링 컴포넌트 여부
				if constexpr (IsRenderComponent<T>())
				{
					if (m_renderComponent == nullptr)
					{
						m_renderComponent = component.ptr_dynamic_cast<RenderComponent>();
					}
					else
					{
						MessageBox(nullptr, L"렌더링 컴포넌트가 이미 존재합니다", L"컴포넌트 추가 실패", MB_OK);
						return nullptr;
					}
				}

				m_components.insert(make_pair(Type, component.ptr_dynamic_cast<Component>()));
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
			for (auto& script : m_scripts)
			{
				Ptr<T> component = script.ptr_dynamic_cast<T>();
				if (component != nullptr) return component;
			}

			return nullptr;
		}
		// 렌더링 컴포넌트
		else if constexpr (Type == COMPONENT_TYPE::RENDER)
		{
			return m_renderComponent;
		}
		// 게임엔진 기본 컴포넌트
		else
		{
			const auto iter = m_components.find(Type);
			if (iter == m_components.end()) return nullptr;
			else return iter->second.ptr_dynamic_cast<T>();
		}
	}

public:
	void Init();
	void Tick();
	void FinalTick();
	void Render();

public:
	void OnCollisionEnter(LAYER_TYPE other);
	void OnCollisionStay(LAYER_TYPE other);
	void OnCollisionExit(LAYER_TYPE other);

private:
	GameObject(const GameObject& origin);
	GameObject& operator=(const GameObject& other);
};