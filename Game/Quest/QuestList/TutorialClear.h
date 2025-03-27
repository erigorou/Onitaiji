// ---------------------------------------------------------------------------------------
// ���O:	QuestPlayerAvoid.h
// ���e:	�N�G�X�g�̃`�F�b�J�[
//			�v���C���[����𒆂����m�F����
// �쐬:	�r�c����
// ---------------------------------------------------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Interface/IQuestChecker.h"
#include "Game/Scene/PlayScene.h"
#include "Game/EnemyManager/EnemyManager.h"

/// <summary>
/// �N�G�X�g�̑S�G���S�`�F�b�J�[
/// </summary>
class TutorialClear : public IQuestChecker
{
public:

	// �e�N�X�`���p�X���擾����
	const wchar_t* GetTexturePath() override { return nullptr; }

	// �`���[�g���A���̃e�N�X�`���p�X���擾����
	const wchar_t* GetTutorialTexturePath() override { return L"Resources/Textures/Quest/TutorialEnd.png"; }

	// �`�F�b�J�[�����s����
	bool ExecuteChecker(PlayScene* playScene) override
	{
		// �G�}�l�[�W���[�̎擾
		auto enemyManager = playScene->GetEnemyManager();

		// �G���S�ł��Ă���Ȃ�true��Ԃ�
		return !enemyManager->IsEnemysAlive();
	};
};