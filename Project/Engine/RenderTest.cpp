#include "pch.h"
#include "RenderTest.h"
#include "Device.h"
#include "TimeManager.h"
#include "Mesh.h"
#include "GraphicShader.h"
#include "AssetManager.h"

#define SQUARE_VERTEX_COUNT 4
#define SQUARE_INDEX_COUNT 6
#define LAYOUT_FIELD_COUNT 3

// 오브젝트 위치
Vec3 g_objPos = Vec3(0.f, 0.f, 0.f);

Ptr<Mesh> g_mesh;
Ptr<GraphicShader> g_shader;

int InitTest()
{
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
	//g_mesh = Ptr(new Mesh(L"MeshTest", L""));
	g_mesh = AssetManager::GetInstance()->FindAsset<Mesh>(L"MeshTest", L"MeshTest");
	if (FAILED(g_mesh->GpuInit(vertexArr, SQUARE_VERTEX_COUNT, indexArr, SQUARE_INDEX_COUNT)))
	{
		return E_FAIL;
	}

	// 셰이더 에셋 생성
	//g_shader = Ptr(new GraphicShader(L"ShaderTest", L"Shader.fx"));
	g_shader = AssetManager::GetInstance()->FindAsset<GraphicShader>(L"ShaderTest", L"Shader.fx");
	if (FAILED(g_shader->GpuInit("VS_Test", "PS_Test")))
	{
		return E_FAIL;
	}

	return S_OK;
}

void RenderTest()
{
	// 이전 프레임 RenderTarget, DepthStencil 클리어
	Device::GetInstance()->Clear();

	// 값 세팅, 렌더링
	Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM)->Bind();
	g_shader->Bind();
	g_mesh->Render();

	// 윈도우에 RenderTarget에 그려진 것 출력
	Device::GetInstance()->Present();
}

void ReleaseTest()
{
}

void MoveTest(KEY_CODE key)
{
	float DT = TimeManager::GetInstance()->GetDeltaTime();
	float dir = 0.f;

	// 방향에 맞게 오브젝트 이동
	if (key == KEY_CODE::LEFT) dir = -1.f;
	else if (key == KEY_CODE::RIGHT) dir = 1.f;

	g_objPos.x += dir * DT;

	// 상수 버퍼 값 변경
	CB_Transform tr;
	tr.pos = g_objPos;

	Ptr<ConstBuffer> cb = Device::GetInstance()->GetConstBuffer(CB_TYPE::TRANSFORM);
	cb->SetData(&tr);
}