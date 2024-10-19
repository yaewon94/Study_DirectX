#include "pch.h"
#include "Asset.h"
#include "PathManager.h"

Asset::Asset(const string& Key, const string& relativePath)
	: Key(Key), relativePath(relativePath)
{
}

Asset::~Asset()
{
}

// TODO : 이거 제대로 되는거 맞나 확인
const wstring Asset::GetFullPathW()
{
	string fullPath = GetFullPathA();
	wstring fullPath_w;
	fullPath_w.assign(fullPath.begin(), fullPath.end());
	return fullPath_w;
}

const string Asset::GetFullPathA()
{
	return PathManager::GetInstance()->GetContentPath() + relativePath;
}