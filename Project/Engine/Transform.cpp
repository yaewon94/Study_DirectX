#include "pch.h"
#include "Transform.h"

Transform::Transform(const GameObject& Owner) 
	: Component(Owner), scale(Vec3(100, 100, 1))
{
}

Transform::Transform(const Transform& origin, const GameObject& Owner) 
	: Component(origin, Owner)
	, pos(origin.pos), scale(origin.scale), rotation(origin.rotation)
{
}

Transform::~Transform()
{
}