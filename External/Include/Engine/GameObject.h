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

// ���ӿ�����Ʈ
class GameObject : public Entity
{
protected:
	string m_name;

	map<COMPONENT_TYPE, Ptr<Component>> m_components;	// ���� �⺻ ������Ʈ�� ���
	vector<Ptr<Script>> m_scripts;						// ����� ���� ������Ʈ ���

	Ptr<Transform> m_transform;

	// ����Ÿ�� �� ������ ���� �� �ִ� ������Ʈ
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
			throw std::logic_error("�̹� �ش� ������Ʈ�� �����մϴ�");
		}
		else
		{
			constexpr COMPONENT_TYPE Type = GetType<T>();
			component = Ptr<T>(Ptr<GameObject>(this));

			// ����� ���� ������Ʈ
			if constexpr (Type == COMPONENT_TYPE::SCRIPT)
			{
				m_scripts.push_back(component.ptr_dynamic_cast<Script>());
			}
			// ���ӿ��� �⺻ ������Ʈ
			else
			{
				// ������ ������Ʈ ����
				if constexpr (IsRenderComponent<T>())
				{
					if (m_renderComponent == nullptr)
					{
						m_renderComponent = component.ptr_dynamic_cast<RenderComponent>();
					}
					else
					{
						MessageBox(nullptr, L"������ ������Ʈ�� �̹� �����մϴ�", L"������Ʈ �߰� ����", MB_OK);
						return nullptr;
					}
				}
				// �ݶ��̴� ������Ʈ ����
				else if constexpr (IsColliderComponent<T>())
				{
					if (m_collider == nullptr)
					{
						m_collider = component.ptr_dynamic_cast<Collider>();
					}
					else
					{
						throw std::logic_error("�ݶ��̴� ������Ʈ�� �̹� �����մϴ�");
					}
				}
				// ���� ������Ʈ ����
				else if constexpr (IsLightComponent<T>())
				{
					if (m_light == nullptr)
					{
						m_light = component.ptr_dynamic_cast<Light>();
					}
					else
					{
						throw std::logic_error("���� ������Ʈ�� �̹� �����մϴ�");
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

		// ����� ���� ������Ʈ
		if constexpr (Type == COMPONENT_TYPE::SCRIPT)
		{
			for (auto& script : m_scripts)
			{
				Ptr<T> component = script.ptr_dynamic_cast<T>();
				if (component != nullptr) return component;
			}

			return nullptr;
		}
		// ������ �ֻ��� �߻� ������Ʈ
		else if constexpr (Type == COMPONENT_TYPE::RENDER)
		{
			return m_renderComponent;
		}
		// �ݶ��̴� �ֻ��� �߻�������Ʈ
		else if constexpr (Type == COMPONENT_TYPE::COLLIDER)
		{
			return m_collider;
		}
		// ���� �ֻ��� �߻�������Ʈ
		else if constexpr (Type == COMPONENT_TYPE::LIGHT)
		{
			return m_light;
		}
		// ���ӿ��� �⺻ ������Ʈ
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