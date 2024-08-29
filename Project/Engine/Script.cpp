#include "pch.h"
#include "Script.h"
#include "GameObject.h"

Script::Script(const Ptr<GameObject>& owner) : Component(owner)
{
}

Script::Script(const Ptr<Script>& origin, const Ptr<GameObject>& owner)
	: Component(origin.ptr_dynamic_cast<Component>(), owner)
{
}

Script::~Script()
{
}
