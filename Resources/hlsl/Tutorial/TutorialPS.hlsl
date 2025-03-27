#include "Tutorial.hlsli"

Texture2D tex : register(t0);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
    // �摜�\��
    float4 output = tex.Sample(samLinear, input.Tex);

    // ���l�̐ݒ�
    output.a *= alpha * 1.0f;
    
    return output;
}