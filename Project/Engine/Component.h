#pragma once
#include "Entity.h"

// 컴포넌트 타입
enum class COMPONENT_TYPE : UINT
{
	TRANSFORM, MESH_RENDER, COUNT_END
};

// 게임오브젝트에 부착할 컴포넌트 클래스
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);
	friend class GameObject;

private:
	const GameObject& Owner;

protected:
	Component(const GameObject& Owner);
	Component(const Component& origin, const GameObject& Owner);
	~Component();
	virtual Component* Clone(const GameObject& Owner) = 0;

protected:
	virtual void Init() {}
	virtual void Tick() {}
	virtual void FinalTick() {}
};