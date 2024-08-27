#include "pch.h"
#include "Level.h"
#include "Layer.h"

Level::Level()
{
}

Level::~Level()
{
}

void Level::Init()
{
	for (auto& layer : layers)
	{
		layer->Init();
	}
}

void Level::Tick()
{
	for (auto& layer : layers)
	{
		layer->Tick();
	}
}

void Level::FinalTick()
{
	for (auto& layer : layers)
	{
		layer->FinalTick();
	}
}

void Level::Render()
{
	for (auto& layer : layers)
	{
		layer->Render();
	}
}

void Level::AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj)
{
	layers[(UINT)layer]->AddObject(obj);
}