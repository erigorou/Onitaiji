// ---------------------------------------------
// ���O:	QuestManager.cpp
// ���e:	�N�G�X�g�}�l�[�W���[�N���X
//			�N�G�X�g�̊Ǘ����s��
// ����:	�r�c����
// ---------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "QuestManager.h"
#include "../Scene/PlayScene.h"
#include "../Data/GameData.h"
#include "QuestRenderer/QuestRenderer.h"
#include "Tutorial/Tutorial.h"
#include "Interface/IQuestChecker.h"
#include "QuestList/QuestChangeTarget.h"
#include "QuestList/QuestPlayerMove.h"
#include "QuestList/QuestPlayerAttack.h"
#include "QuestList/QuestPlayerCombo.h"
#include "QuestList/QuestPlayerAvoid.h"
#include "QuestList/TutorialClear.h"
#include "TutorialList/TutorialStart.h"
#include "TutorialList/TutorialEnd.h"
#include "TutorialList/TutorialAttackStart.h"
#include "TutorialList/TutorialDodgStart.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------
QuestManager::QuestManager(PlayScene* playScene)
	: m_playScene(playScene)
	, m_elapsedTime()
	, m_currentQuestNo()
	, m_totalTime()
	, m_clearTime()
	, m_canClear(false)
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
QuestManager::~QuestManager()
{
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�̏�����
/// </summary>
// ---------------------------------------------
void QuestManager::InitializeQuest()
{
	// �N�G�X�g�f�[�^�ɓo�^���ꂽ�ԍ����擾
	int questIndex = GameData::GetInstance()->GetSelectStage();

	// �N�G�X�g���X�g�̍쐬
	CreateQuest(questIndex);

	if (m_questList.size() <= 0) return;

	// �N�G�X�g���e�̕`��I�u�W�F�N�g
	m_renderer = std::make_unique<QuestRenderer>(this);
	// ����������
	m_renderer->Initialize(m_textureList[0]);
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void QuestManager::Update(float elapsedTime)
{
	// �o�ߎ��Ԃ̋L�^
	m_totalTime += elapsedTime;
	m_elapsedTime = elapsedTime;

	// �N�G�X�g�̍X�V
	UpdateQuest();

	// �`���[�g���A���̍X�V
	if (m_tutorial != nullptr)
	{
		m_tutorial->Update(elapsedTime);
	}

	if (m_renderer != nullptr)
	{
		// �N�G�X�g�`��̍X�V
		m_renderer->Update(elapsedTime);
	}

	// �N�G�X�g�̃N���A����
	IsQuestClear();
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�̍X�V����
/// </summary>
// ---------------------------------------------
void QuestManager::UpdateQuest()
{
	if (m_renderer == nullptr) return;	// �N�G�X�g���Ȃ��ꍇ�͏I��
	if (m_totalTime < DELAY_TIME) return;	// �ŏ��̒x�����ԓ��Ȃ�I��

	if ((m_currentQuestNo < m_questList.size()))
	{
		// �N�G�X�g�̃N���A��`��I�u�W�F�N�g�ɒʒm
		m_renderer->IsClear(m_questList[m_currentQuestNo]->ExecuteChecker(m_playScene));
	}
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g����X�V����
/// </summary>
// ---------------------------------------------
void QuestManager::ChangeNextQuest()
{
	// �N�G�X�g���P�i�߂�
	m_currentQuestNo++;

	// �N�G�X�g���Ō�܂ōs���Ă��Ȃ��ꍇ
	if (m_currentQuestNo < m_questList.size())
	{
		// �N�G�X�g�̕`��̍X�V
		m_renderer->ChangeTexture(m_textureList[m_currentQuestNo]);

		// �`���[�g���A���̕`��̍X�V
		if (m_tutorial != nullptr)
		{
			m_tutorial->ChangeTexture(m_tutorialTextureList[m_currentQuestNo]);
		}
	}
	else
	{
		m_canClear = true;
	}
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�̕`��
/// </summary>
// ---------------------------------------------
void QuestManager::DrawQuest()
{
	if (m_renderer != nullptr)
	{
		// �N�G�X�g�̕`��
		m_renderer->Draw();
	}

	// �`���[�g���A���̕`��
	if (m_tutorial != nullptr)
	{
		m_tutorial->Draw();
	}
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�}�l�[�W���[�̏I������
/// </summary>
// ---------------------------------------------
void QuestManager::Finalize()
{
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�̍쐬
/// </summary>
/// <param name="questIndex">�N�G�X�g�̃C���f�b�N�X</param>
// ---------------------------------------------
void QuestManager::CreateQuest(int questIndex)
{
	switch (questIndex)
	{
	case 0:
		CreateQuestList_1st();
		break;

	case 1:
		CreateQuestList_2nd();
		break;

	case 2:
		CreateQuestList_3rd();
		break;

	default:
		MessageBox(nullptr, L"�N�G�X�g�̍쐬�Ɏ��s���܂���", L"�G���[", MB_OK);
		break;
	}
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g���X�g�̍쐬 �X�e�[�W�P
/// </summary>
// ---------------------------------------------
void QuestManager::CreateQuestList_1st()
{
	// �N�G�X�g�f�[�^�̏���
	ClearQuestData();

	// �N�G�X�g�̍쐬
	m_questList.push_back(new TutorialStart());
	m_questList.push_back(new QuestChangeTarget());
	m_questList.push_back(new QuestPlayerMove());
	m_questList.push_back(new TutorialAttackStart());
	m_questList.push_back(new QuestPlayerAttack());
	m_questList.push_back(new QuestPlayerCombo());
	m_questList.push_back(new TutorialDodgStart());
	m_questList.push_back(new QuestPlayerAvoid());
	m_questList.push_back(new TutorialEnd());

	// �N�G�X�g�̒��̃e�N�X�`����ǂݍ���
	AddQuestTexture();

	// �`���[�g���A���̍쐬
	CreateTutorial();
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g���X�g�̍쐬 �X�e�[�W�Q
/// </summary>
// ---------------------------------------------
void QuestManager::CreateQuestList_2nd()
{
	// �N�G�X�g�f�[�^�̏���
	ClearQuestData();

	// �N�G�X�g�̍쐬
	m_questList.push_back(new TutorialClear());

	// �N�G�X�g�̒��̃e�N�X�`����ǂݍ���
	AddQuestTexture();
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g���X�g�̍쐬 �X�e�[�W�R
/// </summary>
// ---------------------------------------------
void QuestManager::CreateQuestList_3rd()
{
	// �N�G�X�g�f�[�^�̏���
	ClearQuestData();
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�̃e�N�X�`����ǂݍ���
/// </summary>
// ---------------------------------------------
void QuestManager::AddQuestTexture()
{
	// �ݒ肵���N�G�X�g����S�Ĕ����o��
	for (auto quest : m_questList)
	{
		if (quest->GetTexturePath() == nullptr)
		{
			// �e�N�X�`�����X�g��nullptr��ǉ�(��������Ȃ����v�f�͑��₷)
			m_textureList.push_back(nullptr);
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DX::ThrowIfFailed(
			DirectX::CreateWICTextureFromFile(
				CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice(),
				quest->GetTexturePath(),
				nullptr,
				texture.ReleaseAndGetAddressOf()
			)
		);

		// �e�N�X�`�����X�g�ɒǉ�
		m_textureList.push_back(texture);
	}
}

// ---------------------------------------------
/// <summary>
/// �`���[�g���A���̃e�N�X�`����ǂݍ���
/// </summary>
// ---------------------------------------------
void QuestManager::AddTutorialTexture()
{
	for (auto tutorial : m_questList)
	{
		if (tutorial->GetTutorialTexturePath() == nullptr)
		{
			// �e�N�X�`�����X�g��nullptr��ǉ�(��������Ȃ����v�f�͑��₷)
			m_tutorialTextureList.push_back(nullptr);
			continue;
		}

		// �`���[�g���A���̃e�N�X�`����ǂݍ���
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DX::ThrowIfFailed(
			DirectX::CreateWICTextureFromFile(
				CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice(),
				tutorial->GetTutorialTexturePath(),
				nullptr,
				texture.ReleaseAndGetAddressOf()
			)
		);

		// �e�N�X�`�����X�g�ɒǉ�
		m_tutorialTextureList.push_back(texture);
	}
}

// ---------------------------------------------
/// <summary>
/// �`���[�g���A���̍쐬
/// </summary>
// ---------------------------------------------
void QuestManager::CreateTutorial()
{
	// �`���[�g���A���̃e�N�X�`����ǂݍ���
	AddTutorialTexture();

	// �`���[�g���A���̍쐬
	m_tutorial = std::make_unique<Tutorial>(this);
	m_tutorial->Initialize(m_tutorialTextureList[0]);
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�f�[�^�̏���
/// </summary>
// ---------------------------------------------
void QuestManager::ClearQuestData()
{
	// �N�G�X�g���X�g��S�č폜����
	for (auto quest : m_questList)
	{
		delete quest;
	}

	// �摜���X�g�����ׂč폜����
	for (auto texture : m_textureList)
	{
		texture.Reset();
	}

	// �N�G�X�g���X�g�ƃe�N�X�`�����X�g���N���A����
	m_questList.clear();
	m_textureList.clear();
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�̃N���A����
/// </summary>
// ---------------------------------------------
void QuestManager::IsQuestClear()
{
	// �Q�[���N���A���\�ȏꍇ
	if (m_canClear)
	{
		// ��莞�Ԍo�ߌ�ɃQ�[���N���A
		m_clearTime += m_elapsedTime;

		if (m_clearTime > CLEAR_DELAY_TIME)
		{
			// �N���A�V�[���ɑJ��
			m_playScene->ChangeResultScene();
		}
	}
}
