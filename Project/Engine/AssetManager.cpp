#include "pch.h"
#include "AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto& map : assetMapArr)
	{
		map.clear();
	}
}