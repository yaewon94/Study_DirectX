// ���� ��Ŭ�� > HLSL �����Ϸ� > ���̴� ���� /fx ����

#ifndef _STD2D // ���ϸ�
#define _STD2D

#include "Values.fx"
#include "Functions.fx"

#define ALPHA g_float_0

// Vertex Shader
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

VS_OUT VS_Std2D(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    // ======================== ��ǥ ============================
    // �����ǥ => ������ǥ
    //float3 pos = (input.pos * objScale.xyz) + objPos.xyz;
    //output.pos = float4(pos, 1.f);
    //float4 worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    // ������ǥ => view ����
    //float4 viewPos = mul(worldPos, g_viewMatrix);
    // view ���� => ��������
    //output.pos = mul(viewPos, g_projMatrix);
    output.pos = mul(float4(input.pos, 1.f), g_wvp);
    output.worldPos = mul(float4(input.pos, 1.f), g_worldMatrix);
    
    // ======================== UV ��ǥ =========================
    output.uv = input.uv;
    
    return output;
}

// Pixel Shader
float4 PS_Std2D(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    if (g_bTex_0)
        color = g_tex_0.Sample(g_sampler0, input.uv);
    else
        color = GetDebugColor(input.uv, 10);
  
    // ����ó��
    float3 lightColor = (float3) 0.f;
    for (int i = 0; i < g_light2dCount; ++i)
    {
        CalcLight2D(i, input.worldPos.xy, lightColor);
    }
    color.rgb *= lightColor;
   
    return color;
}

float4 PS_Std2D_AlphaBlend(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    if (ALPHA == 0.f)
    {
        discard;
    }
    else
    {
        if (g_isSpriteUsed)
        { 
            float2 bgrLeftTop = g_leftTopUV + (g_sliceUV / 2.f) - (g_backgroundUV / 2.f);
            float2 spriteUV = bgrLeftTop + (input.uv * g_backgroundUV) - g_offsetUV;
            
            if (spriteUV.x < g_leftTopUV.x || spriteUV.x > g_leftTopUV.x + g_sliceUV.x 
                || spriteUV.y < g_leftTopUV.y || spriteUV.y > g_leftTopUV.y + g_sliceUV.y)
            {
                discard;
            }
            else
            {
                color = g_spriteTex.Sample(g_sampler0, spriteUV);
                
                // ����ó��
                float3 lightColor = (float3) 0.f;
                for (int i = 0; i < g_light2dCount; ++i)
                {
                    CalcLight2D(i, input.worldPos.xy, lightColor);
                }
                color.rgb *= lightColor;
            }
        }
        else
        {
            color = PS_Std2D(input);
        }
        
        color.a = ALPHA;
    }
    
    return color;
}

float4 PS_PaperBurn(VS_OUT input) : SV_Target
{
    float4 color = (float4) 0.f;
    
    // ù��° �ؽ�ó
    if (g_bTex_0)
        color = g_tex_0.Sample(g_sampler0, input.uv);
    else
        color = GetDebugColor(input.uv, 10);
    
    // �ι�° �ؽ�ó
    if (g_bTex_1)
    {
        float4 noise = g_tex_1.Sample(g_sampler0, input.uv);
        if (noise.a + ALPHA > 1.f)
            discard;
    }
    
    if (ALPHA == 0.f)
        discard;

    return color;
}

#endif
