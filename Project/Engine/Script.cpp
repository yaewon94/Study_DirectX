#include "pch.h"
#include "Script.h"
#include "GameObject.h"

Script::Script(const Ptr<GameObject>& owner) : Component(owner)
{
}

Script::Script(const Script& origin, const Ptr<GameObject>& owner) 
	: Component(origin, owner)
{
}

Script::~Script()
{
}
