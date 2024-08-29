#pragma once
#include "Entity.h"
#include "ComponentEnums.h"

class GameObject;

// 게임오브젝트에 부착할 컴포넌트 클래스
class Component : public Entity
{
	NO_COPY_ASSIGN(Component);

private:
	Ptr<GameObject> owner;

protected:
	Component(const Ptr<GameObject>& owner);
	Component(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~Component();

public:
	virtual Ptr<Component> Clone(const Ptr<Component>& origin, const Ptr<GameObject>& owner) = 0;

public:
	Ptr<GameObject> GetOwner() { return owner; }

public:
	virtual void Init() {}
	virtual void FinalTick() = 0;
};