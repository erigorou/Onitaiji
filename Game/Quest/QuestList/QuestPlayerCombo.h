// ---------------------------------------------------------------------------------------
// ���O:	QuestPlayerCombo.h
// ���e:	�N�G�X�g�̃`�F�b�J�[
//			�v���C���[���R���{�������m�F����
// �쐬:	�r�c����
// ---------------------------------------------------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Interface/IQuestChecker.h"
#include "Game/Scene/PlayScene.h"
#include "Game/Player/Player.h"

/// <summary>
/// �`���[�g���A���̃R���{�N�G�X�g
/// </summary>
class QuestPlayerCombo : public IQuestChecker
{
public:

	// �e�N�X�`���p�X���擾����
	const wchar_t* GetTexturePath() override { return L"Resources/Textures/Quest/QuestUI_Combo.png"; }

	// �`���[�g���A���̃e�N�X�`���p�X���擾����
	const wchar_t* GetTutorialTexturePath() override { return L"Resources/Textures/Quest/TutorialCombo.png"; }

	// �`�F�b�J�[�����s����
	bool ExecuteChecker(PlayScene* playScene) override
	{
		// �v���C���[�̎擾
		auto player = playScene->GetPlayer();

		// ���݂̃X�e�[�g�ƃR���{�̃X�e�[�g���擾
		auto currentState = player->GetCurrentState();
		auto attackState = player->GetPlayerAttackingState2();

		// �v���C���[�̃X�e�[�g���U�������ǂ���
		return (currentState == attackState);
	};
};