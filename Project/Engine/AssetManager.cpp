#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "GraphicShader.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto& map : assetMapArr)
	{
		map.clear();
	}
}

int AssetManager::Init()
{
	// TODO : 파일로 변환하기
	if (FAILED(CreateDefaultMesh())) return E_FAIL;
	if (FAILED(CreateDefaultShader())) return E_FAIL;

	return S_OK;
}

int AssetManager::CreateDefaultMesh()
{
	{
		// =============================
		// 사각형
		// =============================
		// 정점 위치 설정 (viewport 좌표)
		// 각 픽셀 사이의 컬러값은 보간되서 나옴
		const int SQUARE_VERTEX_COUNT = 4;
		const int SQUARE_INDEX_COUNT = 6;
		int index = 0;

		Vertex vertexArr[SQUARE_VERTEX_COUNT] = {};
		vertexArr[index].pos = Vec3(-0.5f, 0.5f, 0.f);
		vertexArr[index].uv = Vec2(0.f, 0.f);
		vertexArr[index++].color = Vec4(1.f, 0.f, 0.f, 1.f);

		vertexArr[index].pos = Vec3(0.5f, 0.5f, 0.f);
		vertexArr[index].uv = Vec2(1.f, 0.f);
		vertexArr[index++].color = Vec4(0.f, 0.f, 1.f, 1.f);

		vertexArr[index].pos = Vec3(0.5f, -0.5f, 0.f);
		vertexArr[index].uv = Vec2(1.f, 1.f);
		vertexArr[index++].color = Vec4(0.f, 1.f, 0.f, 1.f);

		vertexArr[index].pos = Vec3(-0.5f, -0.5f, 0.f);
		vertexArr[index].uv = Vec2(0.f, 1.f);
		vertexArr[index++].color = Vec4(1.f, 0.f, 1.f, 1.f);

		// 인덱스 값 설정
		UINT indexArr[SQUARE_INDEX_COUNT] = { 0, 1, 2, 0, 2, 3 };

		// 메쉬 에셋 생성
		Ptr<Mesh> rectMesh = AddAsset<Mesh>(L"RectMesh", L"RectMesh");
		if (FAILED(rectMesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
		{
			MessageBox(nullptr, L"사각형 Mesh 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	{
		// =============================
		// 원
		// =============================
		const int SLICE = 40;
		const float RADIUS = 0.5f;

		vector<Vertex> vertexVec;
		vector<UINT> indexVec;
		Vertex vertex;
		float theta = 0.f;	// 원을 나눈 삼각형의 중심각

		// 중심점
		vertex.pos = Vec3(0.f, 0.f, 0.f);
		vertex.uv = Vec2(0.5f, 0.5f);
		vertexVec.push_back(vertex);

		// 정점들 좌표 초기화
		for (int i = 0; i < SLICE + 1; ++i)
		{
			// cos(theta) : x 좌표 / RADIUS
			// sin(theta) : y 좌표 / RADIUS
			vertex.pos = Vec3(RADIUS * cosf(theta), RADIUS * sinf(theta), 0.f);
			vertex.uv = Vec2(vertex.pos.x + 0.5f, 1.f - (vertex.pos.y + 0.5f));
			vertexVec.push_back(vertex);

			theta += (XM_PI * 2.f) / SLICE;
		}

		// 인덱스(원을 이루는 정점들 번호) 초기화
		for (int i = 0; i < SLICE; ++i)
		{
			indexVec.push_back(0);
			indexVec.push_back(i + 1);
			indexVec.push_back(i + 2);
		}

		// 메쉬 생성
		Ptr<Mesh> circleMesh = AddAsset<Mesh>(L"CircleMesh", L"CircleMesh");
		if (FAILED(circleMesh->CreateOnGpu(vertexVec.data(), vertexVec.size(), indexVec.data(), indexVec.size())))
		{
			MessageBox(nullptr, L"원 Mesh 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}

int AssetManager::CreateDefaultShader()
{
	// ==========================
	// 기본 2D 셰이더
	// ==========================
	Ptr<GraphicShader> shader = AddAsset<GraphicShader>(L"Std2D_Shader", L"Std2D.fx");
	shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
	if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_Std2D")))
	{
		MessageBox(nullptr, L"기본 2D 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}