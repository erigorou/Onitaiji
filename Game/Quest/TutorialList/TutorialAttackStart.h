#pragma once
#include "pch.h"
#include "Interface/IQuestChecker.h"
#include "../../Scene/PlayScene.h"

class TutorialAttackStart : public IQuestChecker
{
public:

	// �e�N�X�`���p�X���擾����
	const wchar_t* GetTexturePath() override { return nullptr; }

	// �`���[�g���A���̃e�N�X�`���p�X���擾����
	const wchar_t* GetTutorialTexturePath() override { return L"Resources/Textures/Quest/TutorialAttackStart.png"; }

	// �`�F�b�J�[�����s����
	bool ExecuteChecker(PlayScene* playScene) override
	{
		auto tutorial = playScene->GetQuestManager()->GetTutorial();

		// �`���[�g���A���̃^�C�}�[���X�^�[�g
		tutorial->StartTimer();

		// �^�C�}�[���I�����Ă��邩�ǂ���
		return tutorial->GetTimerIsEnd();
	};
};