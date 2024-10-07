#ifndef _TILEMAP
#define _TILEMAP

#include "Values.fx"
#include "Functions.fx"

#define AtlasTex g_tex_0
#define TileCount g_vec2_0

struct TileInfo
{
    float2 tileLeftTopUV;
    float2 tileSliceUV;
};

StructuredBuffer<TileInfo> g_buffer : register(t16);

struct VS_IN
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float3 worldPos : POSITION;
    float2 uv : TEXCOORD;
};

VS_OUT VS_TileMap(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    output.worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    output.uv = input.uv * TileCount;
    
    return output;
}

float4 PS_TileMap(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    // Å¸ÀÏ ·»´õ¸µ
    if (g_bTex_0)
    {
        int2 colRow = floor(input.uv);
        int index = colRow.y * TileCount.x + colRow.y;
        
        float2 atlasUV = g_buffer[index].tileLeftTopUV + (frac(input.uv) * g_buffer[index].tileSliceUV);
        color = AtlasTex.Sample(g_sampler1, atlasUV);
    }
    else
    {
        color = GetDebugColor(input.uv, 10);
    }
    
    // ±¤¿ø Ã³¸®
    float3 lightColor = float3(0.f, 0.f, 0.f);
    float DistanceRatio = 1.f;
    
    if (g_light2dInfo[0].type == DIRECTION_LIGHT)
    {
        lightColor += g_light2dInfo[0].color;
    }
    else if (g_light2dInfo[0].type == POINT_LIGHT)
    {
        float Distance = distance(input.worldPos, g_light2dInfo[0].worldPos);
        if (Distance <= g_light2dInfo[0].radius)
        {
            lightColor += g_light2dInfo[0].color;
            DistanceRatio = saturate(1.f - (Distance / g_light2dInfo[0].radius));
        }

    }
    else if (g_light2dInfo[0].type == SPOT_LIGHT)
    {
    }
    
    color.rgb *= lightColor * DistanceRatio;
    return color;
}

#endif