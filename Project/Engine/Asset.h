#pragma once
#include "Entity.h"

class Asset;
class Mesh;
class GraphicShader;
class Sprite;
class Texture;
class Material;

// 에셋 타입
enum class ASSET_TYPE : UINT
{
	MESH, GRAPHIC_SHADER, TEXTURE, MATERIAL, SPRITE, COUNT_END
};

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
	const string& GetKey() { return Key; }

protected:
	const string& GetRelativePath() { return relativePath; }
	const string GetFullPathA();
	const wstring GetFullPathW();

protected:
	virtual int Load() = 0;
};