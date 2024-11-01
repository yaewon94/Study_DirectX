#pragma once
#include "Entity.h"

class Asset;
class Mesh;
class GraphicShader;
class Sprite;
class Texture;
class Material;

// 에셋 타입
enum class ASSET_TYPE
{
	MESH = 0, GRAPHIC_SHADER, TEXTURE, MATERIAL, SPRITE, COUNT_END
};

static const char* AssetNameArr[] 
	= { "Mesh"
	, "Graphic Shader"
	, "Texture"
	, "Material"
	, "Sprite"};
static int AssetNameArrSize = sizeof(AssetNameArr) / sizeof(const char*);

// 에셋 최상위 클래스
class Asset : public Entity
{
	NO_COPY_ASSIGN(Asset);

private:
	const string Key;
	string relativePath;

protected:
	Asset(const string& Key, const string& relativePath);
	~Asset();

public:
	const string& GetKey() const { return Key; }
	virtual ASSET_TYPE GetType() = 0;

protected:
	const string& GetRelativePath() { return relativePath; }
	const string GetFullPathA();
	const wstring GetFullPathW();

protected:
	virtual int Load() = 0;
};