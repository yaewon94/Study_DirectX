#include "pch.h"
#include "TileMap.h"
#include "Device.h"
#include "StructuredBuffer.h"
#include "GameObject.h"
#include "Transform.h"
#include "AssetManager.h"
#include "Texture.h"
#include "Material.h"
#include "Mesh.h"

TileMap::TileMap(const Ptr<GameObject>& owner) 
	: MeshRender(owner)
	, m_tileCount(Vec2(1, 1)), m_tileSize(Vec2(100, 100))
	, m_atlas(nullptr)
	, m_tileInfo{}
{
	SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("RectMesh"));
	SetMaterial(AssetManager::GetInstance()->FindAsset<Material>("TileMap_Material"));
}

TileMap::TileMap(const Ptr<Component>& origin, const Ptr<GameObject>& owner) 
	: MeshRender(origin, owner)
{
	auto pOrigin = origin.ptr_dynamic_cast<TileMap>();

	SetAtlasTexture(pOrigin->m_atlas, pOrigin->m_atlasTileCount);
	SetTileIndex(pOrigin->m_atlasTileIndex);
	SetTileCount(pOrigin->m_tileCount);
	SetTileSize(pOrigin->m_tileSize);
}

TileMap::~TileMap()
{
}

void TileMap::SetTileCount(Vec2 count)
{
	if (count.x < 0 || count.y < 0)
	{
		throw std::logic_error("타일 개수는 양의 정수만 가능합니다");
	}

	m_tileCount = count;
	SetObjectScale();

	// 구조화 버퍼 생성
	if (FAILED(m_buffer->CreateOnGpu(sizeof(TileInfo), m_tileCount.x * m_tileCount.y)))
	{
		throw std::logic_error("구조화 버퍼 생성 실패");
	}
}

void TileMap::SetTileSize(Vec2 size)
{
	m_tileSize = size;
	SetObjectScale();
}

void TileMap::SetAtlasTexture(const Ptr<Texture>& atlas, Vec2 tileCount)
{
	m_atlas = atlas;
	m_atlasTileCount = tileCount;

	m_tileInfo.leftTopUV = Vec2(m_atlasTileIndex.x / m_atlasTileCount.x
								, m_atlasTileIndex.y / m_atlasTileCount.y);
	m_tileInfo.sliceUV = Vec2(1.f / m_atlasTileCount.x
							, 1.f / m_atlasTileCount.y);
}

void TileMap::SetTileIndex(Vec2 index)
{
	m_atlasTileIndex = index;

	m_tileInfo.leftTopUV = Vec2(m_atlasTileIndex.x / m_atlasTileCount.x
								, m_atlasTileIndex.y / m_atlasTileCount.y);
}

void TileMap::Render()
{
	// 좌표
	GetOwner()->GetTransform()->BindOnGpu();

	// 재질
	m_material->SetTextureParam(TEX_0, m_atlas);
	m_material->SetScalarParam(VEC2_0, m_tileCount);
	m_material->BindOnGpu();

	// 구조화 버퍼
	m_buffer->SetData(&m_tileInfo, 1);
	m_buffer->BindOnGpu(TEXTURE_PARAM::TILEMAP);

	// 렌더링
	GetMesh()->Render();
}

void TileMap::SetObjectScale()
{
	GetOwner()->GetTransform()->SetLocalScale(Vec3(m_tileCount.x * m_tileSize.x
													, m_tileCount.y * m_tileSize.y
													, 1.f));
}