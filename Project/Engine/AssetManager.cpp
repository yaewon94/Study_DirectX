#include "pch.h"
#include "AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto& map : assetMapArr)
	{
		for (auto& pair : map)
		{
			if (pair.second != nullptr)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

		map.clear();
	}
}