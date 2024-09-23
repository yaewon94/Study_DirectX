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
		g_player->SetLayer(LAYER_TYPE::PLAYER);
		g_player->AddComponent<Player>();
		Ptr<MeshRender> meshRender = g_player->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material"));
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"PlayerTexture", L"Poby.jpeg"));
		g_player->AddComponent<Collider2D>();

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
		monster->SetLayer(LAYER_TYPE::MONSTER);
		monster->GetTransform()->SetLocalPosX(200.f);
		meshRender = monster->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"CircleMesh"));
		meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_Material"));
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"MonsterTexture", L"NoiseTest.png"));
		monster->AddComponent<Collider2D>();
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

Ptr<GameObject> Level::AddObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();

	// 게임오브젝트의 레이어와 일치하는 레이어에 등록
	if (m_layerMap.find(layer) == m_layerMap.end()) m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	return m_layerMap.find(layer)->second->AddObject(obj);
}

void Level::DeleteObject(const Ptr<GameObject>& obj)
{
	const auto iter = m_layerMap.find(obj->GetLayer());

	if (iter == m_layerMap.end())
	{
		if (obj->GetLayer() != LAYER_TYPE::DEFAULT)
		{
			throw std::logic_error("오브젝트 삭제 실패 : 현재 레벨에 등록된 레이어가 아닙니다");
		}
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