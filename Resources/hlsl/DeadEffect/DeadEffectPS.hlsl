#include "Common.hlsli"

// �萔�o�b�t�@
cbuffer ConstBuffer : register(b1)
{
    float time;
    float3 padding;
};


SamplerState samLinear : register(s0);
Texture2D tex : register(t0);



float4 main(PS_Input input) : SV_Target0
{
    // �ˉe��Ԃł�UV�Ƃ��ĎZ�o
    float2 screenUV = input.PositionPS.xy / input.PositionPS.w /5;
    
    // �w�肳�ꂽ�摜�̕\��
    float4 pattern = tex.Sample(samLinear, screenUV);

    // ���̒��_�̐F
    float4 color = float4(1.0f, 0.0f, 0.0f, 1.0f);
    
    
    // �����鋫�E���C�� (���ԂɊ�Â�)
    float boundary_min = 1 - time; // �t�F�[�h�A�E�g�J�n���_
    float boundary_max = 1 - time + 0.3f; // �t�F�[�h�A�E�g�I�����_

    // rgb�̕��ϒl���擾
    float average = (pattern.r + pattern.g + pattern.b) / 3.0f;

    // �O���f�[�V�����p�̕�Ԓl���v�Z
    float t = smoothstep(boundary_min, boundary_max, average);

    // �����猳�̒��_�̐F + �Ԃݗv�f �ւ̃O���f�[�V����
    float4 targetColor = color + float4(0.5f, 0.0f, 0.0f, 0.0f); // ���_�̐F�ɐԂ�ǉ�
    float4 gradColor = lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), targetColor, t);
    
    // �ŏI�I�ȓ����x��ݒ�
    gradColor.a = t; // �����x���O���f�[�V�����ɍ��킹��
    
    gradColor.rgb *= gradColor.a;
    
    return gradColor;
    
    //// �@���𐳋K������
    //float3 normal = normalize(input.NormalWS);
    
    //// ���˃x�N�g���̋t�x�N�g���𐳋K�����遨���C�g����������Ɍ������x�N�g��
    //float3 toLight = normalize(-LightDirection[0]);
    
    //// �@���x�N�g���ƃ��C�g�x�N�g�����甽�ˌ��̋������v�Z����(0-1)
    //float NdotL = dot(normal, toLight);
    //float intensity1 = max(NdotL, 0.0f);
    ////float intensity1 = max(dot(normal, toLight), 0.0f);

    //// �g�U���˂̋������v�Z����
    //float3 diffuse = DiffuseColor.rgb * LightDiffuseColor[0] * intensity1 + EmissiveColor;

    
    //diffuse.rgb -= time / 1.5f;
    //diffuse.r += time;
    
    //// �ŏI�I�ȐF���v�Z����F����͂��܂�Ӗ����Ȃ����
    //float3 finalColor = diffuse;
    
    //return float4(finalColor, 0);
}