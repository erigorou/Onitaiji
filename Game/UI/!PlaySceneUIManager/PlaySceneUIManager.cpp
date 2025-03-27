// ----------------------------------------------
//
//  ���O:  PlaySceneUIManager.h
//  ���e:  �v���C�V�[����UI���Ǘ�����N���X
//  �쐬:  �r�c����
//
// ----------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "PlaySceneUIManager.h"
#include "Game/Screen.h"
#include "Game/Data/GameData.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Player/Player.h"
#include "Game/Boss/Boss.h"
#include "../PlayerHP/PlayerHPUI.h"
#include "../EnemyHP/EnemyHPUI.h"
#include "../PlayerWarning/PlayerWarning.h"
#include "../Operation/Operation.h"

// -----------------------------------------------------
// �Œ�l
// -----------------------------------------------------

// �v���C���[��HP�̈ʒu
const DirectX::SimpleMath::Vector2 PlaySceneUIManager::PLAYER_HP_POSITION = DirectX::SimpleMath::Vector2(Screen::LEFT + 50.0f, 50.0f);

// -----------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene">�v���C�V�[��</param>
// -----------------------------------------------------
PlaySceneUIManager::PlaySceneUIManager(PlayScene* playScene)
	: 
	m_playScene(playScene)
{
}

// -----------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// -----------------------------------------------------
PlaySceneUIManager::~PlaySceneUIManager()
{
	Finalize();
}

// -----------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::Initialize()
{
	// UI�̐���
	CreateUI();
}

// -----------------------------------------------------
/// <summary>
/// UI�̐�������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::CreateUI()
{
	// �v���C���[HP�̐����Ə�����
	CreatePlayerHPUI();
	CreateEnemyHPUI();
	CreateWarning();
	CreateOperation();
}

// -----------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -----------------------------------------------------
void PlaySceneUIManager::Update(float elapsedTime)
{
	// �v���C���[HP�̍X�V
	m_playerHP->Update();

	// �G�l�~�[�����݂���ꍇ
	if (m_enemyHP)
	{
		// �G�l�~�[HP�̍X�V
		m_enemyHP->Update();
	}

	// �x��UI�̍X�V
	m_warning->Update(elapsedTime);
	// ����UI�̍X�V
	m_operation->Update(elapsedTime);
}

// -----------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::Render()
{
	// �x��UI�̍X�V
	m_warning->Render();
	// �v���C���[HP�̕`��
	m_playerHP->Render();

	if (m_enemyHP)
	{
		// �GHP�̕`��
		m_enemyHP->Render();
	}

	// �`���[�g���A���ł͕`�悵�Ȃ�
	if (GameData::GetInstance()->GetSelectStage() <= 0) return;

	// ����UI�̍X�V
	m_operation->Render();
}

// -----------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::Finalize()
{
	// �v���C���[HP�̏I������
	m_playerHP->Finalize();

	if (m_enemyHP)
	{
		// �G�l�~�[HP�̏I������
		m_enemyHP->Finalize();
	}

	// �x��UI�̏I������
	m_warning->Finalize();
	// ����UI�̏I������
	m_operation->Finalize();
}

// -----------------------------------------------------
/// <summary>
/// �v���C���[HP�̐�������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::CreatePlayerHPUI()
{
	auto playerHP = m_playScene->GetPlayer()->GetPlayerHP();

	if (playerHP == nullptr) MessageBox(0, L"PlaySceneUIManager : �v���C���[��HP���擾�ł��܂���ł����B", NULL, MB_OK);

	// �v���C���[HP�̐����Ə�����
	m_playerHP = std::make_unique<PlayerHPUI>(playerHP);
	m_playerHP->Initialize();
}

// -----------------------------------------------------
/// <summary>
/// �GHP�̐�������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::CreateEnemyHPUI()
{
	// �G�l�~�[��HP���擾
	auto enemyHP = m_playScene->GetBoss() ? m_playScene->GetBoss()->GetBossHP() : nullptr;

	// null�`�F�b�N
	if (enemyHP != nullptr)
	{
		// �G�l�~�[HP�̐����Ə�����
		m_enemyHP = std::make_unique<EnemyHPUI>(enemyHP);
		m_enemyHP->Initialize();
	}
}

// -----------------------------------------------------
/// <summary>
/// �x��UI�̐�������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::CreateWarning()
{
	// �v���C���[HP�̎擾
	auto playerHP = m_playScene->GetPlayer()->GetPlayerHP();

	// null�`�F�b�N
	if (playerHP == nullptr) MessageBox(0, L"PlaySceneUIManager : �v���C���[��HP���擾�ł��܂���ł����B", NULL, MB_OK);

	// �x��UI�̐����Ə�����
	m_warning = std::make_unique<PlayerWarning>(playerHP);
	m_warning->Initialize();
}

// -----------------------------------------------------
/// <summary>
/// �������UI�̐�������
/// </summary>
// -----------------------------------------------------
void PlaySceneUIManager::CreateOperation()
{
	// �������UI�̐����Ə�����
	m_operation = std::make_unique<Operation>();
	m_operation->Initialize();
}