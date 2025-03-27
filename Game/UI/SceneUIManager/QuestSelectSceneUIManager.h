#pragma once
#include "pch.h"
#include "Game/UI/UIAnchor.h"
#include "Interface/IAction.h"

class NormalAction;
class TitleLogoAction;
class UserInterface;

class QuestSelectSceneUIManager
{
	// ------------------------------
	// 	�萔
	// ------------------------------
public:
	// �f�t�H���g�̑傫��
	static constexpr DirectX::SimpleMath::Vector2 DEFAULT_SIZE = DirectX::SimpleMath::Vector2(1.0f, 1.0f);
	// ���S�̏����l
	static constexpr DirectX::SimpleMath::Vector2 LOGO_POSITION = DirectX::SimpleMath::Vector2(640.0f, -300.0f);
	// �{�^���̏����l
	static constexpr DirectX::SimpleMath::Vector2 BUTTON_POSITION = DirectX::SimpleMath::Vector2(640.0f, 700.0f);
	// �`���[�g���A���{�^���̏����l
	static constexpr DirectX::SimpleMath::Vector2 TUTORIAL_BUTTON_POSITION = DirectX::SimpleMath::Vector2(1580.0f, 500.0f);
	// �{�X��{�^���̏����l
	static constexpr DirectX::SimpleMath::Vector2 BOSS_FIGHT_BUTTON_POSITION = DirectX::SimpleMath::Vector2(1880.0f, 625.0f);

	// ------------------------------
	// ���J�֐�
	// ------------------------------
public:
	// �R���X�g���N�^
	QuestSelectSceneUIManager();
	// �f�X�g���N�^
	~QuestSelectSceneUIManager();
	// ������
	void Initialize();
	// �X�V
	void Update(const float time);
	// �`��
	void Render();

	// ------------------------------
	// �����֐�
	// ------------------------------
private:
	// ���[�U�[�C���^�[�t�F�[�X�̒ǉ�
	void AddUserInterface(
		const std::string textureName,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		ANCHOR anchor,
		IAction* action
	);

	// ------------------------------
	// �����o�ϐ�
	// ------------------------------
private:
	// ���[�U�[�C���^�[�t�F�[�X���X�g
	std::vector<std::unique_ptr<UserInterface>> m_userInterfaceList;
};
