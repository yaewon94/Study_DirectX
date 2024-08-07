#pragma once
#include "Entity.h"

class GameObject;
class MeshRender;
class Transform;
class Script;

// 컴포넌트 타입
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
	, SCRIPT
};

// 게임오브젝트에 부착할 컴포넌트 클래스
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);
	friend class GameObject;

private:
	template<typename T> requires std::derived_from<T,Component> 
	static T* Create(const GameObject& Owner);

	template<typename T> requires std::derived_from<T,Component> 
	static COMPONENT_TYPE GetType();

private:
	const GameObject& Owner;

protected:
	Component(const GameObject& Owner);
	Component(const Component& origin, const GameObject& Owner);
	~Component();

protected:
	const GameObject& GetOwner() { return Owner; }

private:
	virtual Component* Clone(const GameObject& Owner) = 0;
	void Destroy() { delete this; }

private:
	virtual void Init() {}
	virtual void Tick() {}
	virtual void FinalTick() {}
};

template<typename T> requires std::derived_from<T, Component>
inline T* Component::Create(const GameObject& Owner)
{
	return new T(Owner);
}

template<typename T> requires std::derived_from<T, Component>
inline COMPONENT_TYPE Component::GetType()
{
	// TODO : 런타임에 컴포넌트 추가할때 오류 안나는지 확인
	if constexpr (std::is_base_of_v<Script, T>) return COMPONENT_TYPE::SCRIPT;
	else if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;
	else if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;

	throw std::logic_error("적당한 타입이 없습니다");
}