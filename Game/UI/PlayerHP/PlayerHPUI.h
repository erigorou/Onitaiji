// --------------------------------------------
// 
// ���O:�@�@PlayerHPUI.cpp
// �@�\:	�v���C���[��HP��\������UI�N���X
// ����:	�r�c����
// 
// --------------------------------------------
#ifndef PLAYER_HP_UI
#define PLAYER_HP_UI

#pragma once
// �C���N���[�h
#include "pch.h"
#include "DeviceResources.h"

// �O���錾
class HPSystem;
class CustomShader;

/// <summary>
/// �v���C���[HPUI�N���X
/// </summary>
class PlayerHPUI
{
    // ------------------------------
	// �Œ�l
	// ------------------------------
private:
    // �ő剡��
    static constexpr int MAX_WIDTH = 300;
	// Y���W�i��j
    static constexpr int TOP_POSITION = 50;
	// Y���W�i���j
    static constexpr int BOTTOM_POSITION = 80;
	// X���W(��)
    static constexpr int LEFT_POSITION = 50;

    // ------------------------------
    // �����o�֐�
    // ------------------------------
public:
    // �R���X�g���N�^
    PlayerHPUI(HPSystem* HPSystem);
    // �f�X�g���N�^
    ~PlayerHPUI();
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
    // �X�v���C�g�o�b�`
    std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
    // HP�̃e�N�X�`��
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
    // �w�i�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_backTexture;
    // �t���[���e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_frameTexture;
    // �v���C���[��HP�N���X
    HPSystem* m_playerHPclass;
    // �v���C���[��HP
    float m_playerHP;
};

#endif
