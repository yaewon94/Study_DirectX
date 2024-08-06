#include "pch.h"
#include "Component.h"

Component::Component(const GameObject& Owner) : Owner(Owner)
{
}

Component::Component(const Component& origin, const GameObject& Owner) 
	: Owner(Owner)
{
}

Component::~Component()
{
}
