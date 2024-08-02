#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(const wstring& key, const wstring& relativePath) 
	: key(key), relativePath(PathManager::GetInstance()->GetContentPath() + L"Asset\\" + relativePath)
{
}

Asset::~Asset()
{
}