// --------------------------------------------
//
// ���O:	EnemyHPUI.cpp
// �@�\:	�{�X��HP��\������UI�N���X
// ����:	�r�c����
//
// --------------------------------------------
#ifndef ENEMY_HP_UI
#define ENEMY_HP_UI
#pragma once
// �C���N���[�h
#include "pch.h"
#include "DeviceResources.h"

// �O���錾
class HPSystem;

/// <summary>
/// �{�XHPUI�N���X
/// </summary>
class EnemyHPUI
{
	// ------------------------------
	// �Œ�l
	// ------------------------------	
private:
	// �e�N�X�`���̃T�C�Y
	static constexpr int MAX_WIDTH = 500;
	// �e�N�X�`���̈ʒu
	static constexpr int TOP_POSITION = 650;
	// �e�N�X�`���̈ʒu
	static constexpr int BOTTOM_POSITION = 680;

	// ------------------------------
	// �����o�֐�
	// ------------------------------
public:
	// �R���X�g���N�^
	EnemyHPUI(HPSystem* hpSystem);
	// �f�X�g���N�^
	~EnemyHPUI();
	// �������֐�
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	// ------------------------------
	// �����o�ϐ�
	// ------------------------------
private:
	// �G�l�~�[��HP�N���X
	HPSystem* m_enemyHPclass;
	// �G�l�~�[��HP
	float m_enemyHP;
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// HP�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �w�i�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backTexture;
	// �t���[���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_frameTexture;
	// �o�ߎ���
	float m_totalTime;
};

#endif