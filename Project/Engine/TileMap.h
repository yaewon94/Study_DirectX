#pragma once
#include "MeshRender.h"

class Texture;

// 타일 렌더링 컴포넌트
class TileMap final : public MeshRender
{
	NO_COPY_ASSIGN(TileMap);

private:
	Vec2 m_tileCount;	// 렌더링할 타일 개수
	Vec2 m_tileSize;	// 개당 타일 사이즈

	Ptr<Texture> m_atlas;
	Vec2 m_atlasTileCount;	// 아틀라스 텍스처에 있는 타일의 개수
	Vec2 m_atlasTileIndex;	// 렌더링할 타일의 인덱스

public:
	TileMap(const Ptr<GameObject>& owner);
	TileMap(const Ptr<Component>& origin, const Ptr<GameObject>& owner);
	~TileMap();

public:
	void SetTileCount(Vec2 count);
	void SetTileSize(Vec2 size);
	void SetAtlasTexture(const Ptr<Texture>& atlas, Vec2 tileCount);
	void SetTileIndex(Vec2 index) { m_atlasTileIndex = index; }
	
public:
	virtual void Render() final;

private:
	void SetObjectScale();
};