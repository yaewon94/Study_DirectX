#include "pch.h"
#include "Entity.h"

UINT Entity::nextID = 0;

Entity::Entity() : ID(nextID++), refCount(0)
{
}

Entity::Entity(const wstring& name) : ID(nextID++), name(name), refCount(0)
{
}

Entity::Entity(const Entity& origin) : ID(nextID++), name(origin.name), refCount(0)
{
}

Entity::~Entity()
{
}