#include "../Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);


float CalcAlpha(float2 uv, float2 center, float size)
{
    float aspect = 1280.0f / 720.0f;
	uv.x *= aspect;
	
    return step(size, distance(uv, float2(center.x * aspect, center.y)));
}



float CalcAlpha2(float2 uv, float2 center, float size)
{
    float alpha = 0;
    float aspect = 1280.0f / 720.0f;
    uv.x *= aspect; // �A�X�y�N�g��̒���
	
    // center�̈ʒu���A�X�y�N�g��ɍ��킹�Ē���
    float2 adjustedCenter = center;
    adjustedCenter.x *= aspect;

    float Value = distance(uv, adjustedCenter);
	
    // 0.0f����1.0f�͈̔͂Ɏ��߂A����������
    float x = Value / size;
	
    alpha = smoothstep(0.0f, 1.0f, x);
	
    return alpha;
}


float EraseDifference(float4 dst)
{
    return(1.0 - dst.a);
}



float4 main(PS_INPUT input) : SV_TARGET
{
	//	�摜�\��
	float4 output = tex.Sample(samLinear, input.Tex);

	float4 output2 = tex2.Sample(samLinear, input.Tex);


	//	�^�����ȃs�N�Z��
	float4 outputw = float4(1, 1, 1, 1);
	//	�^�����ȃs�N�Z��
	float4 outputb = float4(0, 0, 0, 1);
	
    // �o�ߎ��ԓI�Ȏg����������
    float t = easing.x;
	
    output.a = CalcAlpha2(input.Tex, float2(0.5f, 0.5f), t * 50);
    
    output.a = EraseDifference(output2);
    
    return output;
}