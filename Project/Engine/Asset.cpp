#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(const wstring& Key, const wstring& relativePath)
	: Key(Key)
	, relativePath(PathManager::GetInstance()->GetContentPath() + L"Asset\\" + relativePath)
{
}

Asset::~Asset()
{
}