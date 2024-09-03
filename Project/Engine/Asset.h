#pragma once
#include "Entity.h"

class Asset;
class Mesh;
class GraphicShader;
class Texture;

// 에셋 타입
enum class ASSET_TYPE : UINT
{
	MESH, GRAPHIC_SHADER, TEXTURE, COUNT_END
};

template<typename T> requires std::derived_from<T, Asset>
static ASSET_TYPE GetType()
{
	if constexpr (std::is_same_v<T, Mesh>) return ASSET_TYPE::MESH;
	if constexpr (std::is_same_v<T, GraphicShader>) return ASSET_TYPE::GRAPHIC_SHADER;
	if constexpr (std::is_same_v<T, Texture>) return ASSET_TYPE::TEXTURE;

	throw std::logic_error(MSG_INVALID_TYPE_CASTING);
}

// 에셋 최상위 클래스
class Asset : public Entity
{
	NO_COPY_ASSIGN(Asset);

private:
	const wstring Key;
	wstring relativePath;

protected:
	Asset(const wstring& Key, const wstring& relativePath);
	~Asset();

protected:
	const wstring& GetRelativePath() { return relativePath; }
	const wstring GetFullPath();

protected:
	virtual int Load() = 0;
};