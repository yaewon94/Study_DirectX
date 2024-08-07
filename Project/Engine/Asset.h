#pragma once
#include "Entity.h"

// 에셋 타입
enum class ASSET_TYPE : UINT
{
	MESH, GRAPHIC_SHADER, COUNT_END
};

// 에셋 최상위 클래스
class Asset : public Entity
{
	NO_COPY_ASSIGN(Asset);
	friend class AssetManager;

private:
	const wstring Key;
	wstring relativePath;

protected:
	Asset(const wstring& Key, const wstring& relativePath);
	~Asset();

protected:
	const wstring& GetPath() { return relativePath; }
};