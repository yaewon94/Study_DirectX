#include "pch.h"
#include "Light.h"
#include "GameObject.h"

Light::Light(const Ptr<GameObject>& owner) 
	: Component(owner)
{
	GetOwner()->SetLayer(LAYER_TYPE::LIGHT);
}

Light::Light(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
	GetOwner()->SetLayer(LAYER_TYPE::LIGHT);
}

Light::~Light()
{
}
