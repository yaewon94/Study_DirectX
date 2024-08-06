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
	friend class AssetManager;

private:
	const wstring Key;
	wstring relativePath;
	const ASSET_TYPE Type;

protected:
	Asset(ASSET_TYPE Type, const wstring& Key, const wstring& relativePath);
	~Asset();

protected:
	const wstring& GetPath() { return relativePath; }

protected:	// 삭제
	Asset(const Asset&) = delete;
	Asset& operator=(const Asset&) = delete;
};