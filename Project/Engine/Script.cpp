#include "pch.h"
#include "Script.h"

Script::Script(const GameObject& Owner) : Component(Owner)
{
}

Script::Script(const Script& origin, const GameObject& Owner) : Component(origin, Owner)
{
}

Script::~Script()
{
}
