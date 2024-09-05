#ifndef _VALUES
#define _VALUES

// 상수 버퍼
cbuffer Transform : register(b0) // 레지스터 번호
{
    //float4 objPos;
    //float4 objScale;
    // * row major : 행 우선 행렬
    row_major matrix g_worldMatrix; // 월드좌표
    row_major matrix g_viewMatrix;  // view 공간
    row_major matrix g_projMatrix;  // 투영 공간
    
    row_major matrix g_wv;  // world * view
    row_major matrix g_wvp; // world * view * proj
};

// 텍스처
Texture2D g_tex : register(t0);

// Sampler State
SamplerState g_sampler0 : register(s0); // 이방성 필터링
SamplerState g_sampler1 : register(s1); // MIN_MAG_POINT 필터링

#endif