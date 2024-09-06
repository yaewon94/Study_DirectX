#ifndef _DEBUG // ÆÄÀÏ¸í
#define _DEBUG

#include "Values.fx"

// Vertex Shader
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

VS_OUT VS_Debug(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    output.uv = input.uv;
    
    return output;
}

// Pixel Shader
float4 PS_Debug(VS_OUT input) : SV_Target
{
    return g_vec4_0;
    //float4 color = float4(0.f, 1.f, 0.f, 1.f);
    
    ////float thickNess = 0.01f;
    
    ////if (thickNess < input.uv.x && input.uv.x < (1.f - thickNess) 
    ////    && thickNess < input.uv.y && input.uv.y < (1.f - thickNess))
    ////    discard;
    
    //return color;
}

#endif