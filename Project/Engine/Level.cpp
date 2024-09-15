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
		// 플레이어 오브젝트 추가
		Ptr<GameObject> g_player = Ptr<GameObject>();
		g_player->SetName(L"Player");
		g_player->AddComponent<Player>();
		Ptr<MeshRender> meshRender = g_player->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_Material"));
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"PlayerTexture", L"Poby.jpeg"));
		AddObject(LAYER_TYPE::PLAYER, g_player);

		// 몬스터 오브젝트 추가
		Ptr<GameObject> monster = Ptr<GameObject>();
		monster->SetName(L"Monster");
		monster->GetComponent<Transform>()->SetPos(Vec3(200.f, 0.f, 100.f));
		Ptr<MeshRender> meshRender2 = monster->AddComponent<MeshRender>();
		meshRender2->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		meshRender2->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material"));
		AddObject(LAYER_TYPE::MONSTER, monster);
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

void Level::Render(LAYER_TYPES layers)
{
	// 현재 레벨에 등록된 레이어 중
	for (auto& pair : m_layerMap)
	{
		// 레이어 조합에 등록된 경우 렌더링
		if (layers & pair.first)
		{
			pair.second->Render();
		}
	}
}

void Level::AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj)
{
	if (m_layerMap.find(layer) == m_layerMap.end()) AddLayer(layer);
	m_layerMap.find(layer)->second->AddObject(obj);
}

Ptr<GameObject> Level::GetGameObject(LAYER_TYPE layer)
{
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		MessageBoxA(nullptr, "해당 레이어의 오브젝트가 없습니다", "오브젝트 찾기 실패", MB_OK);
		return nullptr;
	}
	else
	{
		return iter->second->GetGameObject();
	}
}

void Level::AddLayer(LAYER_TYPE layer)
{
	if (m_layerMap.find(layer) == m_layerMap.end())
	{
		m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	}
}