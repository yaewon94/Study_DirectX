#include "pch.h"
#include "Level.h"
#include "Layer.h"

#include "GameObject.h"
#include "MeshRender.h"
#include "Player.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"
#include "Collider2D.h"
#include "TileMap.h"

Level::Level()
{
}

Level::~Level()
{
	m_layerMap.clear();
}

void Level::Init()
{
	{	 
		// [임시]
		// 타일맵 오브젝트 추가
		Ptr<GameObject> obj = Ptr<GameObject>();
		obj->GetTransform()->SetLocalPosY(-100.f);
		Ptr<TileMap> tileMap = obj->AddComponent<TileMap>();
		tileMap->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>(L"TileMapTex", L"TileTest.png"), Vec2(8, 8));
		tileMap->SetTileIndex(Vec2(3, 0));
		tileMap->SetTileCount(Vec2(10, 1));
		obj->SetLayer(LAYER_TYPE::GROUND);

		// 플레이어 오브젝트 추가
		Ptr<GameObject> g_player = Ptr<GameObject>();
		g_player->AddComponent<Player>();

		//// 플레이어의 자식 오브젝트 추가
		//Ptr<GameObject> child = Ptr<GameObject>();
		//child->SetName(L"PlayerChild");
		//meshRender = child->AddComponent<MeshRender>();
		//meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		//meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material"));
		//meshRender->GetMaterial()->SetAlpha(0.2f);
		//g_player->AddChild(child);

		// 몬스터 오브젝트 추가
		Ptr<GameObject> monster = Ptr<GameObject>();
		monster->GetTransform()->SetLocalPosX(400.f);
		Ptr<MeshRender> meshRender = monster->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		// 동적 재질 사용
		Ptr<Material> material = AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material").DeepCopy();
		meshRender->SetMaterial(material);
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"MonsterTexture", L"NoiseTest.png"));
		monster->AddComponent<Collider2D>();
		monster->SetLayer(LAYER_TYPE::MONSTER);

		// Post Process Vortex Test
		Ptr<GameObject> post = Ptr<GameObject>();
		post->GetTransform()->SetLocalScale(Vec3(1000.f, 800.f, 0.f));
		meshRender = post->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Vortex_Material"));
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"PostProcessTex"));
		//meshRender->GetMaterial()->SetTextureParam(TEX_1, AssetManager::GetInstance()->FindAsset<Texture>(L"NoiseTex", L"NoiseTest.png"));
		post->SetLayer(LAYER_TYPE::DEFAULT);
	}

	for (auto& layer : m_layerMap)
	{
		layer.second->Init();
	}
}

void Level::Tick()
{
	for (auto& layer : m_layerMap)
	{
		layer.second->Tick();
	}
}

void Level::FinalTick()
{
	for (auto& layer : m_layerMap)
	{
		layer.second->FinalTick();
	}
}

Ptr<GameObject> Level::AddObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer < LAYER_TYPE::CAMERA)
	{
		throw std::logic_error("양의 정수인 LAYER_TYPE의 오브젝트만 등록 가능합니다");
	}

	// 게임오브젝트의 레이어와 일치하는 레이어에 등록
	if (m_layerMap.find(layer) == m_layerMap.end()) m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	return m_layerMap.find(layer)->second->AddObject(obj);
}

void Level::DeleteObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer < LAYER_TYPE::CAMERA) return;
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		throw std::logic_error("오브젝트 삭제 실패 : 현재 레벨에 등록된 레이어가 아닙니다");
	}
	else
	{
		iter->second->DeleteObject(obj);

		if (iter->second->IsEmpty())
		{
			iter->second = nullptr;
			m_layerMap.erase(iter);
		}
	}
}

Ptr<GameObject> Level::GetGameObject(LAYER_TYPE layer)
{
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		throw std::logic_error("오브젝트 찾기 실패 : 현재 레벨에 등록된 레이어가 아닙니다");
	}
	else
	{
		return iter->second->GetGameObject();
	}
}