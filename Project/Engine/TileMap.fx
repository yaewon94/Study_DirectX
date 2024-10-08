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
    
    // 타일 렌더링
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
    
    // ========================================
    // 광원 처리
    // ========================================
    float3 lightColor = float3(0.f, 0.f, 0.f);
    float DistanceRatio = 1.f;
    
    // 직사광선
    if (g_light2dInfo[0].type == DIRECTION_LIGHT)
    {
        lightColor += g_light2dInfo[0].color;
    }
    // 점 광원
    else if (g_light2dInfo[0].type == POINT_LIGHT)
    {
        float Distance = distance(input.worldPos, g_light2dInfo[0].worldPos);
        if (Distance <= g_light2dInfo[0].radius)
        {
            lightColor += g_light2dInfo[0].color;
            DistanceRatio = saturate(1.f - (Distance / g_light2dInfo[0].radius));
        }

    }
    // 과제 : 스포트라이트 구현
    else if (g_light2dInfo[0].type == SPOT_LIGHT)
    {
        // 방향 체크 (LEFT, RIGHT, UP, DOWN)
        float3 vecMinus = input.worldPos - g_light2dInfo[0].worldPos;

        // 오브젝트 픽셀이 광원 방향에 있는지 확인
        // (부호가 같은 두 숫자끼리 곱하면 양수가 되는 것을 이용)
        // 2차원 광원 방향은 x축 또는 y축 뿐이지만
        if (g_light2dInfo[0].dir.x * vecMinus.x > 0 
            || g_light2dInfo[0].dir.y * vecMinus.y > 0)
        // 3차원 광원 방향은 x,y,z,xy,xz,yz축 중에 판별해야 함
        //if ((g_light2dInfo[0].dir.x == 0.f || (g_light2dInfo[0].dir.x != 0.f && g_light2dInfo[0].dir.x * vecMinus.x > 0))
        //    && (g_light2dInfo[0].dir.y == 0.f || (g_light2dInfo[0].dir.y != 0.f && g_light2dInfo[0].dir.y * vecMinus.y > 0))
        //    && (g_light2dInfo[0].dir.z == 0.f || (g_light2dInfo[0].dir.z != 0.f && g_light2dInfo[0].dir.z * vecMinus.z > 0)))
        {
            // 광원(O)에서
            // 빛의 진행방향으로 수직으로 내린 직선과 오브젝트 픽셀이 존재하는 축이 만나는 지점(V)
            // 사이의 거리
            // (g_light2dInfo[0].dir 는 Light2D클래스에서 단위벡터로 입력됨)
            float OVdis = distance(input.worldPos * g_light2dInfo[0].dir
                                    , g_light2dInfo[0].worldPos * g_light2dInfo[0].dir);
            
            // 빛을 비추는 각도, 광원부터 V좌표까지의 거리를 기반으로
            // 오브젝트에 투영되는 Light의 반지름 구하기
            // cos(g_light2dInfo[0].angle) == OVdis / sqrt(OVdis^2 + Radius^2)
            // sin(g_light2dInfo[0].angle) == Radius / sqrt(OVdis^2 + Radius^2)
            // => Radius == OVdis / cos(g_light2dInfo[0].angle) * sqrt(1-cos(g_light2dInfo[0].angle)^2)
            // => sin(angle)^2 + cos(angle)^2 = 1 이므로
            float Radius = OVdis * sin(g_light2dInfo[0].angle) / cos(g_light2dInfo[0].angle);
            
            // 오브젝트 픽셀(P)이 Light 범위 안에 있는지 체크
            float3 unitVec = (1.f, 1.f, 1.f);
            if (g_light2dInfo[0].dir.x != 0.f)
                unitVec.x = 0.f;
            if (g_light2dInfo[0].dir.y != 0.f)
                unitVec.y = 0.f;
            
            float VPdis = distance(input.worldPos * unitVec, g_light2dInfo[0].worldPos * unitVec);
            if (VPdis < Radius)
            {
                lightColor += g_light2dInfo[0].color;
                DistanceRatio = saturate(1.f - (VPdis / Radius));
            }
            else
            {
                discard;
            }
        }
        else
        {
            discard;
        }
    }
    
    color.rgb *= lightColor * DistanceRatio;
    return color;
}
#endif