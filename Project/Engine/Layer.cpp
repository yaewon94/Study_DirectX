#include "pch.h"
#include "Layer.h"
#include "GameObject.h"

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::AddObject(const Ptr<GameObject>& obj)
{
	objs.push_back(obj);
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