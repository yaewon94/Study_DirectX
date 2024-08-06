#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(ASSET_TYPE Type, const wstring& Key, const wstring& relativePath)
	: Type(Type)
	, Key(Key)
	, relativePath(PathManager::GetInstance()->GetContentPath() + L"Asset\\" + relativePath)
{
}

Asset::~Asset()
{
}