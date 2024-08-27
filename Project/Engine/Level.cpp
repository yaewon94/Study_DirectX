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
}

Level::~Level()
{
}

void Level::Init()
{
	{
		// [임시]
		// 게임오브젝트 생성
		Ptr<GameObject> g_player = Ptr<GameObject>();
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

		// 오브젝트 등록
		AddObject(LAYER_TYPE::PLAYER, g_player);
	}

	for (auto& layer : layers)
	{
		layer->Init();
	}
}

void Level::Tick()
{
	for (auto& layer : layers)
	{
		layer->Tick();
	}
}

void Level::FinalTick()
{
	for (auto& layer : layers)
	{
		layer->FinalTick();
	}
}

void Level::Render()
{
	for (auto& layer : layers)
	{
		layer->Render();
	}
}

void Level::AddObject(LAYER_TYPE layer, Ptr<GameObject>& obj)
{
	layers[(UINT)layer]->AddObject(obj);
}