#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(const Ptr<GameObject>& owner) : owner(owner)
{
}

Component::Component(const Ptr<Component>& origin, const Ptr<GameObject>& owner)
	: owner(owner)
{
}

Component::~Component()
{
}
