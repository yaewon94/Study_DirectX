#pragma once
#include "Entity.h"

class MeshRender;
class Transform;
class GameObject;

// 컴포넌트 타입
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
};

// 게임오브젝트에 부착할 컴포넌트 클래스
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);

public:
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

public:
	virtual Component* Clone(const GameObject& Owner) = 0;
	void Release() { delete this; }

public:
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
	if constexpr (std::is_same_v<T, Transform>) return COMPONENT_TYPE::TRANSFORM;
	if constexpr (std::is_same_v<T, MeshRender>) return COMPONENT_TYPE::MESH_RENDER;
}