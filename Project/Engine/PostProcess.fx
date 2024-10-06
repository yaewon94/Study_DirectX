#ifndef _POSTPROCESS
#define _POSTPROCESS

#include "Values.fx"

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

// 기본 PostProcess Shader
VS_OUT VS_PostProcess(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = float4(input.pos.xy * 2.f, 0.f, 1.f);
    output.uv = input.uv;

    return output;
}

float4 PS_PostProcess(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    color = g_tex_0.Sample(g_sampler0, input.uv);
    
    color.r = 1.f;  // for test
    color.g = 0.f;
    color.b = 0.f;
    float average = (color.r + color.g + color.b) / 3.f;
    color.rgb = average;
    
    return color;
}

// 왜곡효과 Shader
VS_OUT VS_Distortion(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    output.uv = input.uv;
    
    return output;
}

float4 PS_Distortion(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    // SV Position => Pixel Postion
    float2 screenUV = input.pos.xy / g_renderResolution;
    
    if (g_bTex_1)
    {
        float4 noise = g_tex_1.Sample(g_sampler0, screenUV + 0.05f * g_totalTime);
        noise -= 0.5f;
        noise *= 0.05f;
        screenUV += noise.xy;
    }
    
    color = g_tex_0.Sample(g_sampler0, screenUV);
    return color;
}

// 소용돌이 효과 출력타입, Shader
struct VS_VortexOut
{
    float4 pos : SV_Position;
    float2 objUV : TEXCOORD;
};

VS_VortexOut VS_Vortex(VS_IN input)
{
    VS_VortexOut output = (VS_VortexOut) 0.f;
    
    output.pos = float4(input.pos * 2.f, 1.f);
    
    float4 projPos = mul(float4(0.f, 0.f, 0.f, 1.f), g_wvp);
    projPos.xyz = projPos.xyz / projPos.w;
    
    output.objUV.x = (projPos.x + 1.f) / 2.f;
    output.objUV.y = 1.f - ((projPos.y + 1.f) / 2.f);
    
    return output;
}

float4 PS_Vortex(VS_VortexOut input) : SV_Target
{
    float4 color = (float) 0.f;
    
    float effectRadius = 0.5f;
    float effectAngle = 1.f * PI;
    
    float2 center = input.objUV;
    float2 uv = (input.pos.xy / g_renderResolution.xy) - center;
    
    float len = length(uv * float2(g_renderResolution.x / g_renderResolution.y, 1.));
    float angle = atan2(uv.y, uv.x) + effectAngle * smoothstep(effectRadius, 0, len);
    float radius = length(uv);
    
    color = g_tex_0.Sample(g_sampler0, float2(radius * cos(angle), radius * sin(angle)) + center);
    return color;
}
#endif