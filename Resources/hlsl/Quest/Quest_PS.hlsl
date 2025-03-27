#include "Quest.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);

SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    // �w�肳�ꂽ�摜�̕\��
    float4 quest = tex.Sample(samLinear, input.Tex);
    float4 pattern = tex2.Sample(samLinear, input.Tex);
    
    // �A���t�@�l������ꍇ�ɂ̂ݗL���Ɣ��f����
    float validTexture = step(0.0001f, quest.a);
    
    // �f�B�]���u�� 0 �̏ꍇ�͂��̂܂� quest ���o��
    float dissolveActive = step(0.01f, dissolve);
    
    // �����鋫�E���C�� (���ԂɊ�Â�)
    float boundary_min = dissolve; // �t�F�[�h�A�E�g�J�n���_
    float boundary_max = dissolve + 0.3f; // �t�F�[�h�A�E�g�I�����_

    // rgb�̕��ϒl���擾
    float average = (pattern.r + pattern.g + pattern.b) / 3.0f;

    // �O���f�[�V�����p�̕�Ԓl���v�Z
    float t = smoothstep(boundary_min, boundary_max, average);


    float4 gradientColor = lerp(
        lerp(float4(0.0f, 0.0f, 0.0f, 1.0f), float4(1.0f, 0.5f, 0.0f, 1.0f), t),
        quest, t * 2 );
    
    // �f�B�]���u�K�p�idissolve.x �� 0 �̏ꍇ�͓K�p���Ȃ��j
    float dissolveFactor = lerp(1.0f, t, dissolveActive);
    
    // �F���Ȃ����A�N�G�X�g��\�����邩
    float4 gradColor = lerp(gradientColor, quest, dissolveFactor);
    
    // �ŏI�I�ȓ����x��ݒ�
    gradColor.a = dissolveFactor * validTexture;
    
    // �����x��������
    gradColor *= alpha;
    
    return gradColor;
}
