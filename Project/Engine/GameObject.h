#pragma once
#include "Entity.h"
#include "ComponentEnums.h"
#include "LayerValues.h"

class Component;
class Transform;
class Script;
class RenderComponent;
class Collider;
class Light;

// 게임오브젝트
class GameObject : public Entity
{
protected:
	string m_name;

	map<COMPONENT_TYPE, Ptr<Component>> m_components;	// 엔진 기본 컴포넌트만 등록
	vector<Ptr<Script>> m_scripts;						// 사용자 정의 컴포넌트 등록

	Ptr<Transform> m_transform;

	// 상위타입 한 가지만 가질 수 있는 컴포넌트
	Ptr<RenderComponent> m_renderComponent;
	Ptr<Collider> m_collider;
	Ptr<Light> m_light;

	Ptr<GameObject> m_parent;
	vector<Ptr<GameObject>> m_children;

	LAYER_TYPE m_layer;
	bool m_isDead;

public:
	GameObject();
	GameObject(const GameObject& origin);
	~GameObject();
	GameObject& operator=(const GameObject& other);

public:
	const string& GetName() { return m_name; }
	void SetName(const string& name) { m_name = name; }

	virtual void SetLayer(LAYER_TYPE layer);
	LAYER_TYPE GetLayer() { return m_layer; }

	Ptr<Transform> GetTransform();
	Ptr<RenderComponent> GetRenderComponent();
	Ptr<Collider> GetCollider();

	Ptr<GameObject> GetParent() { return m_parent; }
	void GetChildren(vector<Ptr<GameObject>>& children);
	void AddChild(const Ptr<GameObject>& child, bool isSameLayer = true);

	bool IsDead() { return m_isDead; }
	// only TaskManager can call
	void SetDead() { m_isDead = true; }


	template<typename T> requires std::derived_from<T, Component>
	Ptr<T> AddComponent()
	{
		Ptr<T> component = GetComponent<T>();

		if (component != nullptr)
		{
			throw std::logic_error("이미 해당 컴포넌트가 존재합니다");
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
				// 콜라이더 컴포넌트 여부
				else if constexpr (IsColliderComponent<T>())
				{
					if (m_collider == nullptr)
					{
						m_collider = component.ptr_dynamic_cast<Collider>();
					}
					else
					{
						throw std::logic_error("콜라이더 컴포넌트가 이미 존재합니다");
					}
				}
				// 광원 컴포넌트 여부
				else if constexpr (IsLightComponent<T>())
				{
					if (m_light == nullptr)
					{
						m_light = component.ptr_dynamic_cast<Light>();
					}
					else
					{
						throw std::logic_error("광원 컴포넌트가 이미 존재합니다");
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
		// 렌더링 최상위 추상 컴포넌트
		else if constexpr (Type == COMPONENT_TYPE::RENDER)
		{
			return m_renderComponent;
		}
		// 콜라이더 최상위 추상컴포넌트
		else if constexpr (Type == COMPONENT_TYPE::COLLIDER)
		{
			return m_collider;
		}
		// 광원 최상위 추상컴포넌트
		else if constexpr (Type == COMPONENT_TYPE::LIGHT)
		{
			return m_light;
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
	virtual void FinalTick();
	void Render();

public:
	void OnCollisionEnter(LAYER_TYPE other);
	void OnCollisionStay(LAYER_TYPE other);
	void OnCollisionExit(LAYER_TYPE other);
};