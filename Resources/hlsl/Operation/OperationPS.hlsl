#include "../Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float4 main(PS_INPUT input) : SV_TARGET
{
    // �e�N�X�`�����T���v�����O
    float4 output = tex.Sample(samLinear, input.Tex);
    float v = 0.5f;
    float4 push = float4(v, v, v, v);
    
    // �L�[���͂��������Ƃ��ɏ����Â�����
    output -= push * time.x;
    
    return output;
}