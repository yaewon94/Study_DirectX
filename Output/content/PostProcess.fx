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
#endif