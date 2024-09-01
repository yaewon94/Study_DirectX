#include "pch.h"
#include "Level.h"
#include "Layer.h"

#include "GameObject.h"
#include "MeshRender.h"
#include "Player.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "AssetManager.h"

#define SQUARE_VERTEX_COUNT 4
#define SQUARE_INDEX_COUNT 6

Level::Level()
{
	//m_layerMap.insert(make_pair(LAYER_TYPE::PLAYER, Ptr<Layer>(LAYER_TYPE::PLAYER)));
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
		g_player->AddComponent<MeshRender>();
		g_player->AddComponent<Player>();

		// 정점 위치 설정 (viewport 좌표)
		// 각 픽셀 사이의 컬러값은 보간되서 나옴
		int index = 0;

		Vertex vertexArr[SQUARE_VERTEX_COUNT] = {};
		vertexArr[index].pos = Vec3(-0.5f, 0.5f, 0.f);
		vertexArr[index++].color = Vec4(1.f, 0.f, 0.f, 1.f);

		vertexArr[index].pos = Vec3(0.5f, 0.5f, 0.f);
		vertexArr[index++].color = Vec4(0.f, 0.f, 1.f, 1.f);

		vertexArr[index].pos = Vec3(0.5f, -0.5f, 0.f);
		vertexArr[index++].color = Vec4(0.f, 1.f, 0.f, 1.f);

		vertexArr[index].pos = Vec3(-0.5f, -0.5f, 0.f);
		vertexArr[index++].color = Vec4(1.f, 0.f, 1.f, 1.f);

		// 인덱스 값 설정
		UINT indexArr[SQUARE_INDEX_COUNT] = { 0, 1, 2, 0, 2, 3 };

		// 메쉬 에셋 생성
		Ptr<Mesh> mesh = AssetManager::GetInstance()->FindAsset<Mesh>(L"MeshTest", L"MeshTest");
		if (FAILED(mesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
		{
			assert(nullptr);
		}
		g_player->GetComponent<MeshRender>()->SetMesh(mesh);

		// 셰이더 에셋 생성
		Ptr<GraphicShader> shader = AssetManager::GetInstance()->FindAsset<GraphicShader>(L"ShaderTest", L"Shader.fx");
		if (FAILED(shader->CreateOnGpu("VS_Test", "PS_Test")))
		{
			assert(nullptr);
		}
		g_player->GetComponent<MeshRender>()->SetShader(shader);

		AddObject(LAYER_TYPE::PLAYER, g_player);
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