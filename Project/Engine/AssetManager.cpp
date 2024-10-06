#include "pch.h"
#include "AssetManager.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "Material.h"
#include "Texture.h"

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
	if (FAILED(CreateDefaultMaterial())) return E_FAIL;

	return S_OK;
}

Ptr<Texture> AssetManager::CreateTexture(const wstring& Key, ComPtr<ID3D11Texture2D> texture)
{
	Ptr<Texture> newTex = FindAsset<Texture>(Key);

	if (newTex != nullptr)
	{
		throw std::logic_error("해당 key를 가진 텍스처가 이미 존재합니다");
	}

	// 텍스처 생성
	newTex = Ptr<Texture>(Key, L"");
	if (FAILED(newTex->CreateOnGpu(texture)))
	{
		return nullptr;
	}

	// 생성 성공시
	AddAsset<Texture>(Key, newTex);
	return newTex;
}

Ptr<Texture> AssetManager::CreateTexture(const wstring& Key, Vec2 size, DXGI_FORMAT format, UINT bindFlags, D3D11_USAGE usage)
{
	Ptr<Texture> newTex = FindAsset<Texture>(Key);

	if (newTex != nullptr)
	{
		throw std::logic_error("해당 key를 가진 텍스처가 이미 존재합니다");
	}

	// 텍스처 생성
	newTex = Ptr<Texture>(Key, L"");
	if (FAILED(newTex->CreateOnGpu(size, format, bindFlags, usage)))
	{
		return nullptr;
	}

	// 생성 성공시
	AddAsset<Texture>(Key, newTex);
	return newTex;
}

int AssetManager::CreateDefaultMesh()
{
	Ptr<Mesh> mesh;

	// =============================
	// 사각형
	// =============================
	{
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
		mesh = AddAsset<Mesh>(L"RectMesh", L"RectMesh");
		if (FAILED(mesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
		{
			MessageBox(nullptr, L"사각형 Mesh 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}

		// =============================
		// 디버깅 모드 사각형
		// =============================
		{
			const int DBG_RECT_IDX_COUNT = 5;
			UINT DbgRectIdx[DBG_RECT_IDX_COUNT] = { 0, 1, 2, 3, 0 };
			mesh = AddAsset<Mesh>(L"RectMesh_D", L"RectMesh_D");
			if (FAILED(mesh->CreateOnGpu(vertexArr, SQUARE_VERTEX_COUNT, DbgRectIdx, DBG_RECT_IDX_COUNT)))
			{
				MessageBox(nullptr, L"디버깅용 사각형 Mesh 생성 실패", L"에셋 생성 실패", MB_OK);
				return E_FAIL;
			}
		}
	}

	// =============================
	// 원
	// =============================
	{
		const int SLICE = 40;
		const float RADIUS = 0.5f;

		vector<Vertex> vertexVec(SLICE + 2);
		vector<UINT> indexVec(SLICE * 3);
		Vertex vertex;
		float theta = 0.f;	// 원을 나눈 삼각형의 중심각

		// 중심점
		vertex.pos = Vec3(0.f, 0.f, 0.f);
		vertex.uv = Vec2(0.5f, 0.5f);
		vertexVec[0] = vertex;

		// 정점들 좌표 초기화
		for (int i = 1; i < SLICE + 2; ++i)
		{
			// cos(theta) : x 좌표 / RADIUS
			// sin(theta) : y 좌표 / RADIUS
			vertex.pos = Vec3(RADIUS * cosf(theta), RADIUS * sinf(theta), 0.f);
			vertex.uv = Vec2(vertex.pos.x + 0.5f, 1.f - (vertex.pos.y + 0.5f));
			vertexVec[i] = vertex;

			theta += (XM_PI * 2.f) / SLICE;
		}

		// 인덱스(원을 이루는 정점들 번호) 초기화
		int index = -1;
		for (int i = 0; i < SLICE; ++i)
		{
			indexVec[++index] = 0;
			indexVec[++index] = i + 1;
			indexVec[++index] = i + 2;
		}

		// 메쉬 생성
		mesh = AddAsset<Mesh>(L"CircleMesh", L"CircleMesh");
		if (FAILED(mesh->CreateOnGpu(vertexVec.data(), vertexVec.size(), indexVec.data(), indexVec.size())))
		{
			MessageBox(nullptr, L"원 Mesh 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}

		// =============================
		// 디버깅 모드 원
		// =============================
		{
			indexVec.resize(vertexVec.size() - 1);
			for (int i = 0; i < indexVec.size(); ++i)
			{
				indexVec[i] = i + 1;
			}

			mesh = AddAsset<Mesh>(L"CircleMesh_D", L"CircleMesh_D");
			if (FAILED(mesh->CreateOnGpu(vertexVec.data(), vertexVec.size(), indexVec.data(), indexVec.size())))
			{
				MessageBox(nullptr, L"디버깅용 원 Mesh 생성 실패", L"에셋 생성 실패", MB_OK);
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

int AssetManager::CreateDefaultShader()
{
	Ptr<GraphicShader> shader;

	// ==========================
	// 기본 2D 셰이더
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"Std2D_Shader", L"Std2D.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);
		if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_Std2D")))
		{
			MessageBox(nullptr, L"기본 2D 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	// ==========================
	// 기본 알파블렌드 2D 셰이더
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"Std2D_AlphaBlend_Shader", L"Std2D.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::ALPHABLEND);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_TRANSPARENT);
		if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_Std2D_AlphaBlend")))
		{
			MessageBox(nullptr, L"기본 알파블렌드 2D 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	// ==========================
	// PaperBurn 셰이더
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"PaperBurn_Shader", L"Std2D.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);
		if (FAILED(shader->CreateOnGpu("VS_Std2D", "PS_PaperBurn")))
		{
			MessageBox(nullptr, L"PaperBurn 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	// ==========================
	// 타일맵 컴포넌트 전용 셰이더
	// ==========================
	{
		shader = AddAsset<GraphicShader>(L"TileMap_Shader", L"TileMap.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::LESS);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_MASK);
		if (FAILED(shader->CreateOnGpu("VS_TileMap", "PS_TileMap")))
		{
			MessageBox(nullptr, L"TileMap 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	// ============================
	// Post Process 셰이더
	// ============================
	{
		shader = AddAsset<GraphicShader>(L"PostProcess_Shader", L"PostProcess.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST_WRITE);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
		if (FAILED(shader->CreateOnGpu("VS_PostProcess", "PS_PostProcess")))
		{
			MessageBox(nullptr, L"PostProcess 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	// ============================
	// Distortion 셰이더
	// ============================
	{
		shader = AddAsset<GraphicShader>(L"Distortion_Shader", L"PostProcess.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST_WRITE);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
		if (FAILED(shader->CreateOnGpu("VS_Distortion", "PS_Distortion")))
		{
			MessageBox(nullptr, L"Distortion 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}

	// ============================
	// Vortex 셰이더
	// ============================
	{
		shader = AddAsset<GraphicShader>(L"Vortex_Shader", L"PostProcess.fx");
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST_WRITE);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
		if (FAILED(shader->CreateOnGpu("VS_Vortex", "PS_Vortex")))
		{
			MessageBox(nullptr, L"Vortex 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}



#ifdef _DEBUG
	// ============================
	// 디버깅 모드 셰이더
	// ============================
	{
		shader = AddAsset<GraphicShader>(L"Debug_Shader", L"Debug.fx");
		shader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		shader->SetRasterizerType(RASTERIZE_TYPE::CULL_NONE);
		shader->SetBlendType(BLEND_TYPE::DEFAULT);
		shader->SetDepthStencilType(DEPTH_STENCIL_TYPE::NO_TEST_WRITE);
		shader->SetDomain(SHADER_DOMAIN::DOMAIN_POSTPROCESS);
		if (FAILED(shader->CreateOnGpu("VS_Debug", "PS_Debug")))
		{
			MessageBox(nullptr, L"디버깅 모드 셰이더 생성 실패", L"에셋 생성 실패", MB_OK);
			return E_FAIL;
		}
	}
#endif // DEBUG

	return S_OK;
}

int AssetManager::CreateDefaultMaterial()
{
	Ptr<Material> material;

	// ==========================
	// 기본 2D 재질
	// ==========================
	material = AddAsset<Material>(L"Std2D_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"Std2D_Shader"));

	// ==========================
	// 기본 알파블렌드 2D 재질
	// ==========================
	material = AddAsset<Material>(L"Std2D_AlphaBlend_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"Std2D_AlphaBlend_Shader"));

	// ==========================
	// PaperBurn 재질
	// ==========================
	material = AddAsset<Material>(L"PaperBurn_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"PaperBurn_Shader"));

	// ==========================
	// TileMap 재질
	// ==========================
	material = AddAsset<Material>(L"TileMap_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"TileMap_Shader"));

	// ==========================
	// PostProcess 재질
	// ==========================
	material = AddAsset<Material>(L"PostProcess_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"PostProcess_Shader"));

	// ==========================
	// Distortion 재질
	// ==========================
	material = AddAsset<Material>(L"Distortion_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"Distortion_Shader"));

	// ==========================
	// Vortex 재질
	// ==========================
	material = AddAsset<Material>(L"Vortex_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"Vortex_Shader"));

#ifdef _DEBUG
	// ==========================
	// 디버깅 모드 재질
	// ==========================
	material = AddAsset<Material>(L"Debug_Material", L"");
	material->SetShader(FindAsset<GraphicShader>(L"Debug_Shader"));
#endif // _DEBUG

	return S_OK;
}
