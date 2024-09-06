#ifndef _FUNCTIONS
#define _FUNCTIONS

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
#endif