// ---------------------------------------------------
// �X�e�[�W�N���A�̃N�G�X�g���Ǘ�����N���X
// ---------------------------------------------------

#pragma once
#include "pch.h"

class PlayScene;		// �v���C�V�[��
class QuestRenderer;	// �N�G�X�g���e�̕`��
class Tutorial;			// �`���[�g���A��
class IQuestChecker;	// �N�G�X�g�̃`�F�b�J�[

class QuestManager
{
	// ---------------
	// �Œ�l
	// ---------------
public:
	// �X�e�[�W�̍ő吔
	static constexpr int MAX_STAGE = 3;

	// �X�e�[�W���Ƃ̃N�G�X�g�̍ő吔
	static constexpr int MAX_QUEST_1 = 5;
	static constexpr int MAX_QUEST_2 = 1;
	static constexpr int MAX_QUEST_3 = 1;

	// �N�[���^�C��
	static constexpr float COOL_TIME = 1.0f;
	// �ŏ��̒x��
	static constexpr float DELAY_TIME = 1.0f;
	// �N���A�̒x��
	static constexpr float CLEAR_DELAY_TIME = 0.0f;

	// ---------------
	// �A�N�Z�T
	// ---------------
public:
	// ���݂̃N�G�X�g�ԍ����擾
	int GetCurrentQuestNo() const { return m_currentQuestNo; }
	// �`���[�g���A�����擾
	Tutorial* GetTutorial() { return m_tutorial.get(); }

	// ---------------
	// ���J�֐�
	// ---------------
public:
	// �R���X�g���N�^
	QuestManager(PlayScene* playScene);
	// �f�X�g���N�^
	~QuestManager();
	// �N�G�X�g�̏�����
	void InitializeQuest();
	// �X�V����
	void Update(float elapsedTime);
	// �N�G�X�g�̕`��
	void DrawQuest();
	// �N�G�X�g�̏I��
	void Finalize();
	// �N�G�X�g����X�V����
	void ChangeNextQuest();

	// ---------------
	// �����֐�
	// ---------------
private:
	// �N�G�X�g�̍X�V
	void UpdateQuest();
	// �N�G�X�g�̍쐬
	void CreateQuest(int questIndex);
	// �N�G�X�g���X�g�̍쐬 1st
	void CreateQuestList_1st();
	// �N�G�X�g���X�g�̍쐬 2nd
	void CreateQuestList_2nd();
	// �N�G�X�g���X�g�̍쐬 3rd
	void CreateQuestList_3rd();
	// �N�G�X�g�̃e�N�X�`����ǂݍ���
	void AddQuestTexture();
	// �`���[�g���A���̃e�N�X�`����ǂݍ���
	void AddTutorialTexture();
	// �`���[�g���A���̍쐬
	void CreateTutorial();
	// �N�G�X�g�f�[�^�̏���
	void ClearQuestData();
	// �N�G�X�g�̃N���A���m�F
	void IsQuestClear();

	// ---------------
	// �����o�ϐ�
	// ---------------
private:

	// ���݂̃N�G�X�g�ԍ�
	int m_currentQuestNo;

	// �v���C�V�[��
	PlayScene* m_playScene;
	// �N�G�X�g�̃��X�g
	std::vector<IQuestChecker*> m_questList;
	// �e�N�X�`���̃��X�g
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;
	// �`���[�g���A���̃��X�g
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_tutorialTextureList;

	// �N�G�X�g�̕`��
	std::unique_ptr<QuestRenderer> m_renderer;

	// �`���[�g���A���̕`��
	std::unique_ptr<Tutorial> m_tutorial;

	// �o�ߎ���
	float m_totalTime;
	// �N���A���Ă���̎���
	float m_clearTime;
	// �o�ߎ���
	float m_elapsedTime;

	// �N�G�X�g�̃N���A���\��
	bool m_canClear;
};
