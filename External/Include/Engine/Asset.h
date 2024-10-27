#pragma once
#include "Entity.h"

class Asset;
class Mesh;
class GraphicShader;
class Sprite;
class Texture;
class Material;

// ���� Ÿ��
enum class ASSET_TYPE : UINT
{
	MESH, GRAPHIC_SHADER, TEXTURE, MATERIAL, SPRITE, COUNT_END
};

static const char* AssetNameArr[] 
	= { "Mesh"
	, "Graphic Shader"
	, "Texture"
	, "Material"
	, "Sprite"};
static int AssetNameArrSize = sizeof(AssetNameArr) / sizeof(const char*);


template<typename T> requires std::derived_from<T, Asset>
static ASSET_TYPE GetType()
{
	if constexpr (std::is_same_v<T, Mesh>) return ASSET_TYPE::MESH;
	if constexpr (std::is_same_v<T, GraphicShader>) return ASSET_TYPE::GRAPHIC_SHADER;
	if constexpr (std::is_same_v<T, Texture>) return ASSET_TYPE::TEXTURE;
	if constexpr (std::is_same_v<T, Material>) return ASSET_TYPE::MATERIAL;
	if constexpr (std::is_same_v<T, Sprite>) return ASSET_TYPE::SPRITE;

	throw std::logic_error(MSG_INVALID_TYPE_CASTING);
}

// ���� �ֻ��� Ŭ����
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
	const string& GetKey() { return Key; }

protected:
	const string& GetRelativePath() { return relativePath; }
	const string GetFullPathA();
	const wstring GetFullPathW();

protected:
	virtual int Load() = 0;
};