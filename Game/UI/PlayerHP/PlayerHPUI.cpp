// --------------------------------------------
// 
// ���O:�@�@PlayerHPUI.cpp
// �@�\:	�v���C���[��HP��\������UI�N���X
// ����:	�r�c����
// 
// --------------------------------------------

// �C���N���[�h
#include "pch.h"
#include "PlayerHPUI.h"
#include "Game/Data/HPSystem.h"
#include "Game/GameResources.h"
#include "Game/CommonResources.h"

// ----------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="hpSystem">�v���C���[HP�V�X�e���̃|�C���^</param>
// ----------------------------
PlayerHPUI::PlayerHPUI(HPSystem* hpSystem)
    : m_playerHPclass(hpSystem),
    m_spriteBatch{},
    m_playerHP{}
{
}

// ----------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ----------------------------
PlayerHPUI::~PlayerHPUI()
{
}

// ----------------------------
/// <summary>
/// �������֐�
/// </summary>
// ----------------------------
void PlayerHPUI::Initialize()
{
    // �X�v���C�g�o�b�`�̐ݒ�
    auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
    m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);

    // �v���C���[��HP���擾
    m_playerHP = m_playerHPclass->GetMaxHP();

    // �e�N�X�`���̓ǂݍ���
    m_texture = GameResources::GetInstance()->GetTexture("playerHP");
	m_backTexture = GameResources::GetInstance()->GetTexture("playerHPBack");
	m_frameTexture = GameResources::GetInstance()->GetTexture("playerHPFrame");
}

// ----------------------------
/// <summary>
/// �X�V����
/// </summary>
// ----------------------------
void PlayerHPUI::Update()
{
    // �v���C���[��HP���擾
    m_playerHP = m_playerHPclass->GetHP();
}

// ----------------------------
/// <summary>
/// �`�揈��
/// </summary>
// ----------------------------
void PlayerHPUI::Render()
{
    float MAXHP = static_cast<float>(m_playerHPclass->GetMaxHP());  // �ő�HP���擾

    // �`��ʒu�̃I�t�Z�b�g�l��΃Q�[�W�̕����v�Z����
    LONG offset = static_cast<LONG>(LEFT_POSITION);
    LONG width = static_cast<LONG>(offset + MAX_WIDTH * (m_playerHP / MAXHP));

    // �Q�[�W�͈̔͂̐ݒ�
    RECT outline{ offset, TOP_POSITION, offset + MAX_WIDTH, BOTTOM_POSITION };
    RECT back   { offset, TOP_POSITION, offset + MAX_WIDTH, BOTTOM_POSITION };
    RECT gauge  { offset, TOP_POSITION, width, BOTTOM_POSITION };

	// �X�v���C�g�o�b�`���J�n����
    m_spriteBatch->Begin();

    // �w�ʂ̕`��
    m_spriteBatch->Draw(m_backTexture.Get(), back,DirectX::Colors::White);
    // �Q�[�W����
    m_spriteBatch->Draw(m_texture.Get(), gauge, DirectX::Colors::White);
    // �Q�[�W�̘g
    m_spriteBatch->Draw(m_frameTexture.Get(), outline, DirectX::Colors::White);

    // �X�v���C�g�o�b�`���I������
    m_spriteBatch->End();

}

// ----------------------------
/// <summary>
/// �I������
/// </summary>
// ----------------------------
void PlayerHPUI::Finalize()
{
    // ���\�[�X�̉��
    m_spriteBatch.reset();
    m_texture.Reset();
    m_playerHPclass = nullptr;
}
