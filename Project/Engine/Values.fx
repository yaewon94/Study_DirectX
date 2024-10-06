#ifndef _VALUES
#define _VALUES

// =============================================
// 상수 버퍼
// =============================================
// 오브젝트 좌표, 크기, 각도
cbuffer Transform : register(b0) // 레지스터 번호
{
    //float4 objPos;
    //float4 objScale;
    // * row major : 행 우선 행렬
    row_major matrix g_worldMatrix; // 월드좌표
    row_major matrix g_viewMatrix; // view 공간
    row_major matrix g_projMatrix; // 투영 공간
    
    row_major matrix g_wv; // world * view
    row_major matrix g_wvp; // world * view * proj
};

// 재질
cbuffer Material : register(b1)
{
    int g_int_0, g_int_1, g_int_2, g_int_3;
    float g_float_0, g_float_1, g_float_2, f_float_3;
    float2 g_vec2_0, g_vec2_1, g_vec2_2, g_vec2_3;
    float4 g_vec4_0, g_vec4_1, g_vec4_2, g_vec4_3;
    row_major Matrix g_matrix_0, g_matrix_1;
    int g_bTex_0, g_bTex_1, g_bTex_2, g_bTex_3, g_bTex_4, g_bTex_5;
    int g_bTexArr_0, g_bTexArr_1, g_bTexArr_2, g_bTexArr_3;
    int g_bTexCube_0, g_TexCube_1;
}

// 스프라이트 이미지
cbuffer Sprite : register(b2)
{
    float2 g_leftTopUV;
    float2 g_sliceUV;
    float2 g_backgroundUV;
    float2 g_offsetUV;
    int g_isSpriteUsed;
    int3 g_spritePadding;
}

// 전역 데이터
cbuffer Global : register(b3)
{
    float2 g_renderResolution;
    float g_dt;
    float g_totalTime;
    float g_dt_engine;
    float g_totalTime_engine;
    int g_light2dCount;
    int g_light3dCount;
}

// =============================================
// 텍스처
// =============================================
Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);
Texture2D g_tex_2 : register(t2);
Texture2D g_tex_3 : register(t3);
Texture2D g_tex_4 : register(t4);
Texture2D g_tex_5 : register(t5);

Texture2DArray g_texArr_0 : register(t6);
Texture2DArray g_texArr_1 : register(t7);
Texture2DArray g_texArr_2 : register(t8);
Texture2DArray g_texArr_3 : register(t9);

TextureCube g_texCube_0 : register(t10);
TextureCube g_texCube_1 : register(t11);

Texture2D g_spriteTex : register(t12);

// =============================================
// 샘플링
// =============================================
SamplerState g_sampler0 : register(s0); // 이방성 필터링
SamplerState g_sampler1 : register(s1); // MIN_MAG_POINT 필터링

// =============================================
// 상수 정의
// =============================================
#define PI 3.1415926535f
#endif