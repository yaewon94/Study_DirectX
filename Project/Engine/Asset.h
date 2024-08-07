#pragma once
#include "Entity.h"

class GraphicShader;
class Mesh;

// 에셋 타입
enum class ASSET_TYPE : UINT
{
	MESH, GRAPHIC_SHADER, COUNT_END
};

// 에셋 최상위 클래스
class Asset : public Entity
{
	NO_COPY_ASSIGN(Asset);

public:
	template<typename T> requires std::derived_from<T, Asset> 
	static Asset* Create(const wstring& Key, const wstring& relativePath);

	template<typename T> requires std::derived_from<T, Asset> 
	static ASSET_TYPE GetType();

private:
	const wstring Key;
	wstring relativePath;

protected:
	Asset(const wstring& Key, const wstring& relativePath);
	~Asset();

public:
	void Destroy() { delete this; }

protected:
	const wstring& GetPath() { return relativePath; }
};

template<typename T> requires std::derived_from<T, Asset>
inline Asset* Asset::Create(const wstring& Key, const wstring& relativePath)
{
	return new T(Key, relativePath);
}

template<typename T> requires std::derived_from<T, Asset>
inline ASSET_TYPE Asset::GetType()
{
	if constexpr (std::is_same_v<T, Mesh>) return ASSET_TYPE::MESH;
	if constexpr (std::is_same_v<T, GraphicShader>) return ASSET_TYPE::GRAPHIC_SHADER;
}