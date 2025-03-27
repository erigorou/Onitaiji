#include "../Particle.hlsli"

//	4�̒��_���쐬����
static const int vnum = 4;

//	�e���_�̃x�[�X�Ƃ�����
static const float4 offset_array[vnum] =
{
	float4(-0.5f,  0.5f, 0.0f, 0.0f),	// ����
	float4( 0.5f,  0.5f, 0.0f, 0.0f),	// �E��
	float4(-0.5f, -0.5f, 0.0f, 0.0f),	// ����
	float4( 0.5f, -0.5f, 0.0f, 0.0f),	// �E��

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{
	//	4�̒��_�𐶐����Ă���
	for (int i = 0; i < vnum; i++)
	{
		//	�V�������_���p�̕ϐ�
		PS_INPUT element;

		//	�x�[�X�̍��W���擾
		float4 res = offset_array[i];

		//	Tex�ɓ����Ă�����ŕ\���T�C�Y�����肷��B
		//	���̌v�Z���ʂ��A�\���������ʒu�܂ňړ��B
		element.Pos =input[0].Pos + mul(offset_array[i] * input[0].Tex.x, matWorld);

		//	view��proj���v�Z���āA�X�N���[�����W�֕ϊ�
		element.Pos = mul(element.Pos, matView);
		element.Pos = mul(element.Pos, matProj);

		//	�F���͂��̂܂܎g��
		element.Color = input[0].Color;
		//	C++���������Ă���Tex����UV���W�ł͂Ȃ����߁A
		//	���ۂɎg�p�\�ȉ摜��UV���������ŎZ�o����
		element.Tex.x =  offset_array[i].x + 0.5f;
		element.Tex.y = -offset_array[i].y + 0.5f;

		//	���̃V�F�[�_�֏���n�����߁A���_����ǉ�����
		output.Append(element);
	}
	//	�����������_�f�[�^����A�|���S������K�؂ɔ��f���Ă��炤
	output.RestartStrip();
}