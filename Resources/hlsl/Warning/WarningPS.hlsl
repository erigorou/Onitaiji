#include "../Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
    // �e�N�X�`�����T���v�����O
    float4 output = tex.Sample(samLinear, input.Tex);

    // ���̃A���t�@�l�ɑ΂��ĕϓ���������
    float alphaVariation = sin(time.x * 2) * 0.5f;    // 0�`1�ɃX�P�[�����O
    output.a *= alphaVariation / 2;                   // ���̃A���t�@�l�ɉe����^����
    output.r = 0.7f;
    
    return output;
}