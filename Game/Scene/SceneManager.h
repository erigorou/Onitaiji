// --------------------------------------------------
// 
// ���O:	SceneManager.h
// ���e:	�V�[�����Ǘ�����N���X
// �쐬:	�r�c����
// 
// --------------------------------------------------
#pragma once
// �C���N���[�h
#include "IScene.h"

// �O���錾
class CommonResources;
class GameResources;
class Sound;
class Fade;

class SceneManager
{
	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	SceneManager();
	// �f�X�g���N�^
	~SceneManager();

	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
	// �V�[���ύX�\�ɂ���
	void SetCanChangeScene() { m_canChangeScene = true; }

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �V�[����ύX����
	void ChangeScene(IScene::SceneID sceneID);
	// �V�[�����쐬����
	void CreateScene(IScene::SceneID sceneID);
	// �V�[�����폜����
	void DeleteScene();
	// �L�[�{�[�h�̓��͂��X�V����
	void UpdateKeyboard();
	// Escape�������ꂽ�Ƃ��̃C�x���g
	void OnEscapeKeyEvent();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ���݂̃V�[��
	std::unique_ptr<IScene> m_currentScene;
	// �t�F�[�h
	std::unique_ptr<Fade> m_fade;
	// �Q�[�����\�[�X
	GameResources* m_gameResources;
	// �T�E���h�Ǘ�
	Sound* m_sound;

	// ���݂̃V�[��ID
	IScene::SceneID m_currentSceneID;
	// ���̃V�[��ID
	IScene::SceneID m_nextSceneID;

	// �V�[���ύX�\���ǂ���
	bool m_canChangeScene;
	// �t�F�[�h�����ǂ���
	bool m_isFade;
	// esc�L�[�������ꂽ���ǂ���
	bool m_isEscape;


	// �L�[�{�[�h�̏��
	DirectX::Keyboard::State m_keyboardState;
	// �L�[�{�[�h�̏�ԃg���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardStateTracker;
};
