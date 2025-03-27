// -------------------------------------------------------------------
// 
// ���O:	QuestSelectSceneUIManager.cpp
// �@�\:	�^�C�g���V�[���ł�UI�Ǘ��N���X	
//			�`���[�g���A�����{�X��I������{�^����\������
// ����:	�r�c����
// 
// -------------------------------------------------------------------
#include "pch.h"
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "QuestSelectSceneUIManager.h"
#include "Game/UI/UserInterface.h"
#include "Game/UI/UIAnchor.h"
#include "Game/UI/Action/NormalAction.h"
#include "Game/UI/Action/TitleLogoAction.h"
#include "Game/UI/Action/TutorialButtonAction.h"
#include "Game/UI/Action/BossFightButtonAction.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------

QuestSelectSceneUIManager::QuestSelectSceneUIManager()
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
QuestSelectSceneUIManager::~QuestSelectSceneUIManager()
{
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------
void QuestSelectSceneUIManager::Initialize()
{
	// ���S�̒ǉ�
	AddUserInterface(
		"logo",
		DirectX::SimpleMath::Vector2(LOGO_POSITION),
		DirectX::SimpleMath::Vector2(DEFAULT_SIZE),
		ANCHOR::TOP_CENTER,
		new TitleLogoAction()
	);

	// �{�^���̒ǉ�
	AddUserInterface(
		"startButton",
		DirectX::SimpleMath::Vector2(BUTTON_POSITION),
		DirectX::SimpleMath::Vector2(DEFAULT_SIZE),
		ANCHOR::BOTTOM_CENTER,
		new NormalAction()
	);

	// �`���[�g���A���{�^���̒ǉ�
	AddUserInterface(
		"tutorial",
		DirectX::SimpleMath::Vector2(TUTORIAL_BUTTON_POSITION),
		DirectX::SimpleMath::Vector2(DEFAULT_SIZE),
		ANCHOR::BOTTOM_RIGHT,
		new TutorialButtonAction()
	);

	// �{�X��{�^���̒ǉ�
	AddUserInterface(
		"bossfight",
		DirectX::SimpleMath::Vector2(BOSS_FIGHT_BUTTON_POSITION),
		DirectX::SimpleMath::Vector2(DEFAULT_SIZE),
		ANCHOR::BOTTOM_RIGHT,
		new BossFightButtonAction()
	);
}

// ---------------------------------------------------------
/// <summary>
/// ���[�U�[�C���^�[�t�F�[�X�̒ǉ�
/// </summary>
/// <param name="textureName">�e�N�X�`����</param>
/// <param name="position">�ʒu</param>
/// <param name="scale">�X�P�[��</param>
/// <param name="anchor">�A���J�[</param>
/// <param name="action">�A�N�V����</param>
// ---------------------------------------------------------
void QuestSelectSceneUIManager::AddUserInterface(
	const std::string textureName,
	DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale,
	ANCHOR anchor,
	IAction* action
)
{
	// �e�N�X�`���̎擾
	auto texture = GameResources::GetInstance()->GetTexture(textureName);
	// ���[�U�[�C���^�[�t�F�[�X�̐���
	auto ui = std::make_unique<UserInterface>();
	// ���[�U�[�C���^�[�t�F�[�X�̍쐬
	ui->Create(texture, position, scale, anchor, action);
	// ���[�U�[�C���^�[�t�F�[�X�̓o�^
	m_userInterfaceList.push_back(std::move(ui));
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="time">�o�ߎ���</param>
// ---------------------------------------------------------
void QuestSelectSceneUIManager::Update(const float time)
{
	for (auto& ui : m_userInterfaceList)
	{
		ui->Update(time);
	}
}

// ---------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// ---------------------------------------------------------

void QuestSelectSceneUIManager::Render()
{
	for (auto& ui : m_userInterfaceList)
	{
		ui->Render();
	}
}