#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::AddObject(Ptr<GameObject>& _obj)
{
	// 중복 검사
	for (auto& obj : objs)
	{
		if (_obj.GetAddressOf() == obj.GetAddressOf()) return;
	}

	objs.push_back(_obj);
}

void Layer::Init()
{
	for (auto& obj : objs)
	{
		obj->Init();
	}
}

void Layer::Tick()
{
	for (auto& obj : objs)
	{
		obj->Tick();
	}
}

void Layer::FinalTick()
{
	for (auto& obj : objs)
	{
		obj->FinalTick();
	}
}

void Layer::Render()
{
	for (auto& obj : objs)
	{
		obj->Render();
	}
}