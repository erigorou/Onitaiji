// ---------------------------------------------------------------------------------------
// ���O:	QuestPlayerMove.h
// ���e:	�N�G�X�g�̃`�F�b�J�[
//			�v���C���[���ړ����������m�F����
// �쐬:	�r�c����
// ---------------------------------------------------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Interface/IQuestChecker.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Player/Player.h"

/// <summary>
/// �`���[�g���A���̈ړ��N�G�X�g
/// </summary>
class QuestPlayerMove : public IQuestChecker
{
public:

	// �e�N�X�`���p�X���擾����
	const wchar_t* GetTexturePath() override { return L"Resources/Textures/Quest/QuestUI_Move.png"; }

	// �`���[�g���A���̃e�N�X�`���p�X���擾����
	const wchar_t* GetTutorialTexturePath() override { return L"Resources/Textures/Quest/TutorialMove.png"; }

	// �`�F�b�J�[�����s����
	bool ExecuteChecker(PlayScene* playScene) override
	{
		// �v���C���[�̎擾
		auto player = playScene->GetPlayer();

		// �v���C���[���ړ����Ă��邩
		return (player->GetinputVector() != DirectX::SimpleMath::Vector2::Zero);
	};
};