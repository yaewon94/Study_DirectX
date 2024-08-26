#include "pch.h"
#include "Component.h"
#include "GameObject.h"

Component::Component(const Ptr<GameObject>& owner) : owner(owner)
{
}

Component::Component(const Component& origin, const Ptr<GameObject>& owner)
	: owner(owner)
{
}

Component::~Component()
{
}
