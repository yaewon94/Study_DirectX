#include "pch.h"
#include "Entity.h"

UINT Entity::nextID = 0;

Entity::Entity() : ID(nextID++)
{
}

Entity::Entity(const wstring& name) : ID(nextID++), name(name)
{
}

Entity::Entity(const Entity& origin) : ID(nextID++), name(origin.name)
{
}

Entity::~Entity()
{
}