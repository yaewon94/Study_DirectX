#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(const wstring& Key, const wstring& relativePath)
	: Key(Key), relativePath(relativePath)
{
}

Asset::~Asset()
{
}

const wstring Asset::GetFullPath()
{
	return PathManager::GetInstance()->GetContentPath() + relativePath;
}