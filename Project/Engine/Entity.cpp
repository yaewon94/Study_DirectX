#include "pch.h"
#include "Entity.h"

UINT Entity::nextID = 0;

Entity::Entity() : ID(nextID++)
{
}


Entity::Entity(const Entity& origin) : ID(nextID++)
{
}

Entity::~Entity()
{
}