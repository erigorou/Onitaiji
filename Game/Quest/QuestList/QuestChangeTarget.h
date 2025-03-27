// ---------------------------------------------------------------------------------------
// ���O:	QuestChangeTarget.h
// ���e:	�N�G�X�g�̃`�F�b�J�[
//			�^�[�Q�b�g�̕ύX���s���������m�F����
// �쐬:	�r�c����
// ---------------------------------------------------------------------------------------

// �C���N���[�h
#pragma once
#include "pch.h"
#include "Interface/IQuestChecker.h"
#include "Game/Scene/PlayScene.h"


/// <summary>
/// �`���[�g���A���̃^�[�Q�b�g�ύX�N�G�X�g
/// </summary>
class QuestChangeTarget : public IQuestChecker
{
public:
	// �e�N�X�`���p�X���擾����
	const wchar_t* GetTexturePath() override { return L"Resources/Textures/Quest/QuestUI_Target.png"; }

	// �`���[�g���A���̃e�N�X�`���p�X���擾����
	const wchar_t* GetTutorialTexturePath() override { return L"Resources/Textures/Quest/TutorialChangeTarget.png"; }

	// �`�F�b�J�[�����s����
	bool ExecuteChecker(PlayScene* playScene) override
	{
		UNREFERENCED_PARAMETER(playScene);

		// �L�[�{�[�h�̏�Ԃ��擾����
		DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();
		DirectX::Keyboard::KeyboardStateTracker keyboardTracker;
		// �L�[�{�[�h�X�e�[�g�g���b�J�[���X�V����
		keyboardTracker.Update(keyboardState);

		// space�������ꂽ��
		return (keyboardTracker.IsKeyPressed(DirectX::Keyboard::Space));
	};
};