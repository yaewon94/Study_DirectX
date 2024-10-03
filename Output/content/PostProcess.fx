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
#endif