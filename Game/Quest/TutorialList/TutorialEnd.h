#pragma once
#include "pch.h"
#include "Interface/IQuestChecker.h"
#include "../../Scene/PlayScene.h"

class TutorialEnd : public IQuestChecker
{
private:

public:

	// �e�N�X�`���p�X���擾����
	const wchar_t* GetTexturePath() override { return L"Resources/Textures/Quest/QuestUI_Boss.png"; }

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