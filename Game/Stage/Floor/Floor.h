// -----------------------------------
// ���v���~�e�B�u�ɂ��n�ʂ̕`��
// -----------------------------------

#pragma once
#include "pch.h"

class Floor
{
public:
	// -----------------------------
	// �Œ�l�i�萔�j
	// -----------------------------
	// �~�̔��a
	static constexpr float RADIUS = 200.0f;
	// �~�𕪊����鐔
	static constexpr int SEGMENTS = 16;
	// ���K���p�ϐ�
	static constexpr float NORMALIZE = 0.5f;

	// -----------------------------
	// �����o�֐��i���J�j
	// -----------------------------
public:
	// �R���X�g���N�^
	Floor();
	// �f�X�g���N�^
	~Floor();
	// �~�̒��_�𐶐�
	void GenerateCircleVertices(
		DirectX::VertexPositionTexture* vertices, 
		float radius, 
		int segments
	);
	// �`�揈��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj); 
	// �I������
	void Finalize();

private:
	// -----------------------------
	// �����o�ϐ��i����J�j
	// -----------------------------
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// ���ʃX�e�[�g�i�`���ԁj
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �G�t�F�N�g�i�V�F�[�_�j
	std::unique_ptr<DirectX::AlphaTestEffect> m_BatchEffect;
	// �v���~�e�B�u�o�b�`�i�`��p�j
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_Batch;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};
