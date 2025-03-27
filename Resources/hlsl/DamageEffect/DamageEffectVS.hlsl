#include "Common.hlsli"


VS_Output main(VS_Input input)
{
    VS_Output output = (VS_Output) 0;
   
    // ���[�J�����烏�[���h�ɕϊ�
    output.PositionWS = mul(input.Position, World);
    
    // �@���Ƀ��[���h��K�p
    output.NormalWS = normalize(mul(input.Normal, (float3x3) World));
    
    // �ˉe��ԏ�ɍ��W��ϊ�
    output.PositionPS = mul(input.Position, WorldViewProj);
   
    return output;
}