#include "pch.h"
#include "Asset.h"

Asset::Asset(const wstring& key, const wstring& relativePath) 
	: key(key), relativePath(relativePath)
{
}

Asset::~Asset()
{
}