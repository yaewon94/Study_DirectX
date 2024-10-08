#ifndef _FUNCTIONS
#define _FUNCTIONS
#include "Values.fx"

float4 GetDebugColor(float2 _uv, int _level)
{
    float2 texPos = _uv * _level;
    int col = floor(texPos.x);
    int row = floor(texPos.y);
    
    if ((col + row) % 2) 
        return float4(1.f, 0.f, 1.f, 1.f);
    else
        return float4(0.f, 0.f, 0.f, 1.f);

}

// 광원처리
void CalcLight2D(int lightIdx, float2 objPos, inout float3 lightColor)
{
    float DistanceRatio = 1.f;
    
    // 직사광선
    if (g_light2dInfo[lightIdx].type == DIRECTION_LIGHT)
    {
        lightColor += g_light2dInfo[lightIdx].color;
    }
    // 점 광원
    else if (g_light2dInfo[lightIdx].type == POINT_LIGHT)
    {
        float Distance = distance(objPos, g_light2dInfo[lightIdx].worldPos);
        
        if (Distance <= g_light2dInfo[lightIdx].radius)
        {
            DistanceRatio = saturate(1.f - (Distance / g_light2dInfo[lightIdx].radius));
            lightColor += (g_light2dInfo[lightIdx].color * DistanceRatio);
        }
    }
    // 스포트라이트
    else if (g_light2dInfo[lightIdx].type == SPOT_LIGHT)
    {
        // 방향 체크 (LEFT, RIGHT, UP, DOWN)
        //float3 vecMinus = worldPos - g_light2dInfo[lightIdx].worldPos;
        float2 vecMinus = objPos - g_light2dInfo[lightIdx].worldPos;

        // 오브젝트 픽셀이 광원 방향에 있는지 확인
        // (부호가 같은 두 숫자끼리 곱하면 양수가 되는 것을 이용)
        // 2차원 광원 방향은 x축 또는 y축 뿐이지만
        if (g_light2dInfo[lightIdx].dir.x * vecMinus.x > 0
            || g_light2dInfo[lightIdx].dir.y * vecMinus.y > 0)
        // 3차원 광원 방향은 x,y,z,xy,xz,yz축 중에 판별해야 함
        //if ((g_light2dInfo[0].dir.x == 0.f || (g_light2dInfo[0].dir.x != 0.f && g_light2dInfo[0].dir.x * vecMinus.x > 0))
        //    && (g_light2dInfo[0].dir.y == 0.f || (g_light2dInfo[0].dir.y != 0.f && g_light2dInfo[0].dir.y * vecMinus.y > 0))
        //    && (g_light2dInfo[0].dir.z == 0.f || (g_light2dInfo[0].dir.z != 0.f && g_light2dInfo[0].dir.z * vecMinus.z > 0)))
        {
            // 광원(O)에서
            // 빛의 진행방향으로 수직으로 내린 직선과 오브젝트 픽셀이 존재하는 축이 만나는 지점(V)
            // 사이의 거리
            // (g_light2dInfo[0].dir 는 Light2D클래스에서 단위벡터로 입력됨)
            //float OVdis = distance(worldPos * g_light2dInfo[lightIdx].dir
            //                        , g_light2dInfo[lightIdx].worldPos * g_light2dInfo[lightIdx].dir);
            float OVdis = distance(objPos * g_light2dInfo[lightIdx].dir
                                    , g_light2dInfo[lightIdx].worldPos * g_light2dInfo[lightIdx].dir);
            
            
            // 빛을 비추는 각도, 광원부터 V좌표까지의 거리를 기반으로
            // 오브젝트에 투영되는 Light의 반지름 구하기
            // cos(g_light2dInfo[0].angle) == OVdis / sqrt(OVdis^2 + Radius^2)
            // sin(g_light2dInfo[0].angle) == Radius / sqrt(OVdis^2 + Radius^2)
            // => Radius == OVdis / cos(g_light2dInfo[0].angle) * sqrt(1-cos(g_light2dInfo[0].angle)^2)
            // => sin(angle)^2 + cos(angle)^2 = 1 이므로
            float Radius = OVdis * sin(g_light2dInfo[lightIdx].angle) / cos(g_light2dInfo[lightIdx].angle);
            
            // 오브젝트 픽셀(P)이 Light 범위 안에 있는지 체크
            //float3 unitVec = (1.f, 1.f, 1.f);
            float2 unitVec = (1.f, 1.f);
            if (g_light2dInfo[lightIdx].dir.x != 0.f)
                unitVec.x = 0.f;
            if (g_light2dInfo[lightIdx].dir.y != 0.f)
                unitVec.y = 0.f;
            
            //float VPdis = distance(worldPos * unitVec, g_light2dInfo[lightIdx].worldPos * unitVec);
            float VPdis = distance(objPos * unitVec, g_light2dInfo[lightIdx].worldPos * unitVec);

            if (VPdis < Radius)
            {
                DistanceRatio = saturate(1.f - (VPdis / Radius));
                lightColor += (g_light2dInfo[lightIdx].color * DistanceRatio);
            }
        }
    }
}
#endif