#include "pch.h"
#include "LevelManager.h"
#include "Level.h"
#include "GameObject.h"

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::Init()
{
	curLevel = Ptr<Level>();
	curLevel->Init();
}

void LevelManager::Tick()
{
	curLevel->Tick();
	curLevel->FinalTick();
}

void LevelManager::Render()
{
	curLevel->Render();
}

void LevelManager::Render(LAYER_TYPES layers)
{
	curLevel->Render(layers);
}

Ptr<GameObject> LevelManager::GetGameObject(LAYER_TYPE layer)
{
	return curLevel->GetGameObject(layer);
}