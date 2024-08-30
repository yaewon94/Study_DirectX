#include "pch.h"
#include "Entity.h"

UINT Entity::nextID = 0;

Entity::Entity() : ID(nextID++), refCount(1)
{
}


Entity::Entity(const Entity& origin) : ID(nextID++), refCount(1)
{
}

Entity::~Entity()
{
	if (refCount > 0) throw std::logic_error("해당 객체를 아직 참조중 입니다");
}