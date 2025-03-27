// --------------------------------------------
//
// ���O:	EnemyHPUI.cpp
// �@�\:	�{�X��HP��\������UI�N���X
// ����:	�r�c����
//
// --------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/UI/EnemyHP/EnemyHPUI.h"
#include "Game/Data/HPSystem.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "Game/GameResources.h"

// ----------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="hpSystem">HP����������N���X�̃|�C���^</param>
// ----------------------------
EnemyHPUI::EnemyHPUI(HPSystem* hpSystem)
	: 
	m_enemyHPclass(hpSystem), 
	m_texture{},
	m_totalTime{},
	m_spriteBatch{}, 
	m_enemyHP{}
{
}

// ----------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ----------------------------
EnemyHPUI::~EnemyHPUI()
{
}

// ----------------------------
/// <summary>
/// ����������
/// </summary>
// ----------------------------
void EnemyHPUI::Initialize()
{
	// �R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`�̐ݒ�
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);

	// �e�N�X�`���̓ǂݍ���
	m_texture = GameResources::GetInstance()->GetTexture("enemyHP");
	m_backTexture = GameResources::GetInstance()->GetTexture("enemyHPBack");
	m_frameTexture = GameResources::GetInstance()->GetTexture("enemyHPFrame");

	// �G�l�~�[��HP���擾
	m_enemyHP = m_enemyHPclass->GetMaxHP();
}


// ----------------------------
/// <summary>
/// �X�V�֐�
/// </summary>
// ----------------------------
void EnemyHPUI::Update()
{
}

// ----------------------------
/// <summary>
/// �`��֐�
/// </summary>
// ----------------------------
void EnemyHPUI::Render()
{
	// �G��HP���擾
	m_enemyHP = m_enemyHPclass->GetHP();
	// �ő�HP���擾
	float MAXHP = m_enemyHPclass->GetMaxHP();

	// �`��ʒu�̃I�t�Z�b�g�l��΃Q�[�W�̕����v�Z����
	LONG offset = static_cast<LONG>(Screen::CENTER_X - (MAX_WIDTH / 2));
	LONG width = static_cast<LONG>(offset + MAX_WIDTH * (m_enemyHP / MAXHP));

	// �Q�[�W�͈̔͂̐ݒ�
	RECT outline{ offset, TOP_POSITION, offset + MAX_WIDTH, BOTTOM_POSITION };
	RECT back	{ offset, TOP_POSITION, offset + MAX_WIDTH, BOTTOM_POSITION };
	RECT gauge	{ offset, TOP_POSITION, width, BOTTOM_POSITION };

	// �X�v���C�g�o�b�`���J�n����
	m_spriteBatch->Begin();

	// �w�ʂ̕`��
	m_spriteBatch->Draw(m_backTexture.Get(), back, DirectX::Colors::White);
	// �Q�[�W����
	m_spriteBatch->Draw(m_texture.Get(), gauge, DirectX::Colors::White);
	// �Q�[�W�̘g
	m_spriteBatch->Draw(m_frameTexture.Get(), outline, DirectX::Colors::White);

	// �X�v���C�g�o�b�`���I������
	m_spriteBatch->End();
}

// ----------------------------
/// <summary>
/// �I���֐�
/// </summary>
// ----------------------------
void EnemyHPUI::Finalize()
{
	m_spriteBatch.reset();
	m_texture.Reset();
	m_enemyHPclass = nullptr;
}