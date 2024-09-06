// 파일 우클릭 > HLSL 컴파일러 > 셰이더 형식 /fx 설정

#ifndef _STD2D // 파일명
#define _STD2D

#include "Values.fx"
#include "Functions.fx"

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Std2D(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ======================== 좌표 ============================
    // 상대좌표 => 절대좌표
    //float3 pos = (input.pos * objScale.xyz) + objPos.xyz;
    //output.pos = float4(pos, 1.f);
    //float4 worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    // 절대좌표 => view 공간
    //float4 viewPos = mul(worldPos, g_viewMatrix);
    // view 공간 => 투영공간
    //output.pos = mul(viewPos, g_projMatrix);
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    
    // ======================== 색상 ============================
    output.color = input.color;
    
    // ======================== UV 좌표 =========================
    output.uv = input.uv;
    
    return output;
}

// Pixel Shader
float4 PS_Std2D(VS_OUT input) : SV_Target
{
    // texture가 바인딩 되어있지 않으면 디버그 색상 출력
    // 방법 1. Shader 상에서 해결
    // 문제점 : 모든 픽셀을 검사하기 때문에 성능 매우 떨어짐
    int width = 0;
    int height = 0;
    g_tex_0.GetDimensions(width, height);
    
    if (!width || !height)
        return GetDebugColor(input.uv, 10);
    else
        return g_tex_0.Sample(g_sampler0, input.uv);
    
    ////// 중도폐기
    ////clip(-1);
    ////discard;
    //float4 color = g_tex_0.Sample(g_sampler0, input.uv);
    
    ////// 투명 표현 용도
    ////if (color.r == 1.f && color.g == 0.f && color.b == 1.f)
    ////    discard;
    
    //if (g_int_0 == 10) return float4(0.f, 0.f, 1.f, 1.f);
    //else return color;
}

#endif
