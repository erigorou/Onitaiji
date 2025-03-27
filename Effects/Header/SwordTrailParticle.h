// -------------------------------------- //
//
// ����̋O�ՃG�t�F�N�g�̋������v�Z����N���X
//
// -------------------------------------- //
#pragma once
#include "pch.h"
#include "Interface/IParticle.h"

class SwordTrailParticle : public IParticle
{
	// ----------------------------
	// �A�N�Z�T
	// ----------------------------
public:
	// �\������
	const float GetLife() { return m_life; }
	// �J�n����
	const float GetStartLife() { return m_startLife; }
	// ���݂̐F
	const DirectX::SimpleMath::Color GetNowColor() { return m_nowColor; }
	// �J�n���F
	const DirectX::SimpleMath::Color GetStartColor() { return m_startColor; }
	// �I�����F
	const DirectX::SimpleMath::Color GetEndColor() { return m_endColor; }

	// 4���_�̍��W���擾
	void GetVertices(DirectX::VertexPositionColorTexture* vertices)
	{
		// �e���_�̈ʒu�A�F�A�e�N�X�`�����W��ݒ肷��
		vertices[0] = DirectX::VertexPositionColorTexture(m_vertices[0].position, DirectX::SimpleMath::Vector4(1, 1, 1, 1), m_vertices[0].textureCoordinate);
		vertices[1] = DirectX::VertexPositionColorTexture(m_vertices[1].position, DirectX::SimpleMath::Vector4(1, 1, 1, 1), m_vertices[1].textureCoordinate);
		vertices[2] = DirectX::VertexPositionColorTexture(m_vertices[2].position, DirectX::SimpleMath::Vector4(1, 1, 1, 1), m_vertices[2].textureCoordinate);
		vertices[3] = DirectX::VertexPositionColorTexture(m_vertices[3].position, DirectX::SimpleMath::Vector4(1, 1, 1, 1), m_vertices[3].textureCoordinate);
	}

	// ----------------------------
	// �����o�֐��i���J�j
	// ----------------------------
public:
	// �R���X�g���N�^
	SwordTrailParticle(
		DirectX::VertexPositionTexture vertex[],
		float life,
		DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor
	);
	// �f�X�g���N�^
	~SwordTrailParticle();
	// �X�V����
	bool Update(float elapsedTime);

	// ----------------------------
	// �����o�ϐ�
	// ----------------------------
private:
	// �`��ɕK�v�ȂS���_�̍��W
	DirectX::VertexPositionTexture m_vertices[4];
	//	��������
	float m_life;
	float m_startLife;
	//	�J���[
	DirectX::SimpleMath::Color m_nowColor;
	DirectX::SimpleMath::Color m_startColor;
	DirectX::SimpleMath::Color m_endColor;
};