// 파일 우클릭 > HLSL 컴파일러 > 셰이더 형식 /fx 설정

#ifndef _SHADER // 파일명
#define _SHADER

// 상수 버퍼
cbuffer Transform : register(b0) // 레지스터 번호
{
    //float4 objPos;
    //float4 objScale;
    row_major matrix g_worldMatrix;   // 행 우선 행렬
    row_major matrix g_viewMatrix;
    row_major matrix g_projMatrix;
};

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VS_OUT VS_Test(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ======================== 좌표 ============================
    // 상대좌표 => 절대좌표
    //float3 pos = (input.pos * objScale.xyz) + objPos.xyz;
    //output.pos = float4(pos, 1.f);
    float4 worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    // 절대좌표 => view 공간
    float4 viewPos = mul(worldPos, g_viewMatrix);
    // view 공간 => 투영공간
    output.pos = mul(viewPos, g_projMatrix);
    
    // ======================== 색상 ============================
    output.color = input.color;
    
    return output;
}

// Pixel Shader
float4 PS_Test(VS_OUT input) : SV_Target
{
    return input.color;
}

#endif
