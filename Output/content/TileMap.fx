#ifndef _TILEMAP
#define _TILEMAP

#include "Values.fx"
#include "Functions.fx"

#define AtlasTex g_tex_0
#define LeftTopUV g_vec2_0
#define SliceUV g_vec2_1
//#define TileCol g_int_0
//#define TileRow g_int_1
#define TileCount g_vec2_2

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

VS_OUT VS_TileMap(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    //output.uv = input.uv * float2(TileCol, TileRow);
    output.uv = input.uv * TileCount;
    
    return output;
}

float4 PS_TileMap(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    if (g_bTex_0)
    {
        float2 atlasUV = LeftTopUV + (frac(input.uv) * SliceUV);
        color = AtlasTex.Sample(g_sampler0, atlasUV);
    }
    else
    {
        color = GetDebugColor(input.uv, 10);
    }
    
    return color;
}

#endif