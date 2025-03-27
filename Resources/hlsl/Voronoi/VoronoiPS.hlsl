#include "../Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);



// ���������p�̊֐�
float2 random2(float2 uv)
{
    return frac(sin(dot(uv, float2(12.9898, 78.233))) * 43758.5453);
}

// Voronoi�m�C�Y�����p�̊֐�
float voronoiNoise(float2 uv)
{
    float2 p = floor(uv);
    float2 f = frac(uv);
    
    float minDist = 1.0;
    
    for (int j = -1; j <= 1; ++j)
    {
        for (int i = -1; i <= 1; ++i)
        {
            float2 g = float2(i, j);
            float2 randomPoint = random2(p + g);
            float2 diff = g + randomPoint - f;
            float dist = length(diff);
            
            minDist = min(minDist, dist);
        }
    }
    
    return minDist;
}

// �_�炩���c�ݗp�̊֐�
float2 subtleDistortUV(float2 uv, float time)
{
    float distortionStrengthX = 0.08; // �������̘c�݂̋���
    float distortionStrengthY = 0.06; // �c�����̘c�݂̋���

    uv.x += sin(uv.y * 8.0 + time * 1.5) * distortionStrengthX;
    uv.y += cos(uv.x * 8.0 + time * 1.2) * distortionStrengthY;
    return uv;
}

float4 main(PS_INPUT input) : SV_TARGET
{
    // �u���b�N�̐�
    float scale = 20.0;
    float2 uv = input.Tex * scale;

    // ��{��UV�c��
    uv = subtleDistortUV(uv, time.x);

    // �ǉ��̓���
    uv += float2(time.x * 0.5, time.x * 0.3);

    // ������Voronoi�m�C�Y���C���[
    float noiseValue1 = voronoiNoise(uv);
    float noiseValue2 = voronoiNoise(uv * 0.6 + float2(time.x * 0.02, time.x * 0.015));
    float noiseValue3 = voronoiNoise(uv * 1.2 + float2(time.x * 0.01, time.x * 0.005));

    // �m�C�Y�̍���
    float noiseValue = (noiseValue1 + noiseValue2 + noiseValue3) / 3.0;

    // �F�̃O���f�[�V�����i�[���F�Ɛ󂢐F�𒲐��j
    float3 deepColor = float3(0.4, 0.6, 0.9);
    float3 lightColor = float3(0.4, 0.7, 0.9);
    float3 oceanColor = lerp(deepColor, lightColor, smoothstep(0.3, 0.7, noiseValue));

    // �n�C���C�g�̒ǉ��i���̔��ˁj - �͈͂Ƌ��x������ɍL����
    float highlight = smoothstep(0.5, 0.95, noiseValue) * 1.2; // �n�C���C�g�͈͂Ƌ��x�̒���
    oceanColor += highlight * float3(0.9, 1.1, 1.3); // ��蔒���ۂ�

    return float4(oceanColor, 1.0);
}