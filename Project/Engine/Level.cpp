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
#include "Light2D.h"

Level::Level() 
	: m_state(LEVEL_STATE::NONE)
{
}

Level::~Level()
{
	m_layerMap.clear();
}

void Level::Init()
{
	{	 
		// [�ӽ�]
		// ���� ������Ʈ �߰�
		/*Ptr<GameObject> obj = Ptr<GameObject>();
		obj->SetName(L"Light1");
		obj->GetTransform()->SetLocalPos(Vec3(-100.f, 150.f, 0.f));
		Ptr<Light2D> light = obj->AddComponent<Light2D>();
		light->SetLightType(LIGHT_TYPE::SPOT);
		light->SetColor(COLOR_RED);
		light->SetDirection(DIRECTION_2D::DOWN);
		light->SetAngle(45);

		obj = obj.DeepCopy();
		obj->SetName(L"Light2");
		obj->GetTransform()->SetLocalPos(Vec3(100.f, 150.f, 0.f));
		light = obj->GetComponent<Light2D>();
		light->SetColor(COLOR_GREEN);*/
		Ptr<GameObject> obj = Ptr<GameObject>();
		obj->SetName("Light");
		obj->AddComponent<Light2D>();

		// Ÿ�ϸ� ������Ʈ �߰�
		obj = Ptr<GameObject>();
		obj->SetName("Ground");
		obj->GetTransform()->SetLocalPosY(-100.f);
		Ptr<TileMap> tileMap = obj->AddComponent<TileMap>();
		tileMap->SetAtlasTexture(AssetManager::GetInstance()->AddAsset<Texture>("TileMapTex", "TileTest.png"), Vec2(8, 8));
		tileMap->SetTileIndex(Vec2(3, 0));
		tileMap->SetTileCount(Vec2(10, 1));
		obj->SetLayer(LAYER_TYPE::GROUND); // TODO : Ground script���� �߰��ϵ��� ����

		//// �÷��̾� ������Ʈ �߰�
		//Ptr<GameObject> g_player = Ptr<GameObject>();
		//g_player->SetName(L"Player");
		//g_player->GetTransform()->SetLocalPosX(-300.f);
		//g_player->AddComponent<Player>();

		//// �÷��̾��� �ڽ� ������Ʈ �߰�
		//Ptr<GameObject> child = Ptr<GameObject>();
		//child->SetName(L"PlayerChild");
		//meshRender = child->AddComponent<MeshRender>();
		//meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		//meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Std2D_AlphaBlend_Material"));
		//meshRender->GetMaterial()->SetAlpha(0.2f);
		//g_player->AddChild(child);

		// ���� ������Ʈ �߰�
		Ptr<GameObject> monster = Ptr<GameObject>();
		monster->SetName("Monster");
		Ptr<MeshRender> meshRender = monster->AddComponent<MeshRender>();
		meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>("CircleMesh"));
		// ���� ���� ���
		Ptr<Material> material = AssetManager::GetInstance()->FindAsset<Material>("Std2D_AlphaBlend_Material").DeepCopy();
		meshRender->SetMaterial(material);
		meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>("MonsterTexture", "NoiseTest.png"));
		monster->AddComponent<Collider2D>();
		monster->SetLayer(LAYER_TYPE::MONSTER); // TODO : Monster script���� �߰��ϵ��� ����

		//// Post Process Vortex Test
		//Ptr<GameObject> post = Ptr<GameObject>();
		//post->GetTransform()->SetLocalScale(Vec3(1000.f, 800.f, 0.f));
		//meshRender = post->AddComponent<MeshRender>();
		//meshRender->SetMesh(AssetManager::GetInstance()->FindAsset<Mesh>(L"RectMesh"));
		//meshRender->SetMaterial(AssetManager::GetInstance()->FindAsset<Material>(L"Vortex_Material"));
		//meshRender->GetMaterial()->SetTextureParam(TEX_0, AssetManager::GetInstance()->FindAsset<Texture>(L"PostProcessTex"));
		//post->SetLayer(LAYER_TYPE::DEFAULT);
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

void Level::GetLayers(vector<LAYER_TYPE>& layers)
{
	for (auto& pair : m_layerMap)
	{
		layers.push_back(pair.first);
	}
}

Ptr<GameObject> Level::AddObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer == LAYER_TYPE::NONE)
	{
		throw std::logic_error("�߸��� �����Դϴ�");
	}

	// ���ӿ�����Ʈ�� ���̾�� ��ġ�ϴ� ���̾ ���
	if (m_layerMap.find(layer) == m_layerMap.end()) m_layerMap.insert(make_pair(layer, Ptr<Layer>(layer)));
	return m_layerMap.find(layer)->second->AddObject(obj);
}

void Level::DeleteObject(const Ptr<GameObject>& obj)
{
	LAYER_TYPE layer = obj->GetLayer();
	if (layer == LAYER_TYPE::NONE)
	{
		throw std::logic_error("�߸��� �����Դϴ�");
	}

	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		throw std::logic_error("������Ʈ ���� ���� : ���� ������ ��ϵ� ���̾ �ƴմϴ�");
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
		throw std::logic_error("������Ʈ ã�� ���� : ���� ������ ��ϵ� ���̾ �ƴմϴ�");
	}
	else
	{
		return iter->second->GetGameObject();
	}
}

void Level::GetGameObjects(LAYER_TYPE layer, vector<Ptr<GameObject>>& objs)
{
	const auto iter = m_layerMap.find(layer);

	if (iter == m_layerMap.end())
	{
		throw std::logic_error("������Ʈ ã�� ���� : ���� ������ ��ϵ� ���̾ �ƴմϴ�");
	}
	else
	{
		return iter->second->GetGameObjects(objs);
	}
}