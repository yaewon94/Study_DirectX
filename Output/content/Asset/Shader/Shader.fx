// ���� ��Ŭ�� > HLSL �����Ϸ� > ���̴� ���� /fx ����

#ifndef _SHADER // ���ϸ�
#define _SHADER

// ��� ����
cbuffer Transform : register(b0) // �������� ��ȣ
{
    float4 pos;
};

// Vertex Shader
struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VS_OUT VS_Test(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0.f;
    output.pos = float4(input.pos + pos.xyz, 1.f);
    output.color = input.color;
    return output;
}

// Pixel Shader
float4 PS_Test(VS_OUT input) : SV_Target
{
    return input.color;
}

#endif