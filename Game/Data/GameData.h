// ------------------------------------------------
// ���O:	GameData.h
// ���e:	�Q�[���f�[�^��n�����߂̃N���X
//			��ɃV�[���Ԃł̃f�[�^�̎󂯓n���Ɏg�p����
// �쐬;	�r�c����
// ------------------------------------------------
#pragma once

/// <summary>
/// �Q�[���f�[�^��n�����߂̃N���X
/// </summary>
class GameData
{
	// ------------------------------
	// �\����
	// ------------------------------
public:
	enum class BATTLE_RESULT : unsigned int
	{
		WIN,
		LOSE,
		NONE
	};

	// ------------------------------
	// �A�N�Z�T
	// ------------------------------
public:
	// GameData�N���X�̃C���X�^���X���擾����
	static GameData* const GetInstance();

	// �퓬���ʂ̐ݒ�
	void SetBattleResult(BATTLE_RESULT result) { m_battleResult = result; }
	// �퓬���ʂ̎擾
	BATTLE_RESULT GetBattleResult() const { return m_battleResult; }
	// ��ʂ̃t�F�[�h�ʂ̐ݒ�
	void SetFadeValue(float value) { m_fadeValue = value; }
	// ��ʂ̃t�F�[�h�ʂ̎擾	
	float GetFadeValue() const { return m_fadeValue; }
	// �o�ߎ���
	void SetElapsedTime(float time) { m_elapsedTime = time; }
	// �o�ߎ��Ԃ̎擾
	float GetElapsedTime() const { return m_elapsedTime; }
	// �I�������X�e�[�W�̃C���f�b�N�X�̐ݒ�
	void SetSelectStage(int stageIndex) { m_questIndex = stageIndex; }
	// �I�������X�e�[�W�̃C���f�b�N�X�̎擾
	int GetSelectStage() const { return m_questIndex; }

	// �X�N���[���V���b�g�̐ݒ�
	void SetScreenShot(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> captureSRV) { m_captureSRV = captureSRV; }
	// �X�N���[���V���b�g�̎擾
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetScreenShot() const { return m_captureSRV; }

	// ------------------------------
	// �����o�֐�(���J)
	// ------------------------------
public:
	// �R���X�g���N�^
	GameData();
	// �f�X�g���N�^
	~GameData() = default;

	// ------------------------------
	// �����o�ϐ�
	// ------------------------------
private:
	// �C���X�^���X
	static std::unique_ptr<GameData> s_data;
	// �퓬����
	BATTLE_RESULT m_battleResult = BATTLE_RESULT::WIN;
	// ��ʂ̃t�F�[�h��
	float m_fadeValue;
	// �o�ߎ���
	float m_elapsedTime;
	// �N�G�X�g�̃C���f�b�N�X
	int m_questIndex;

	// �X�N�V��(�e�N�X�`��)
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_captureSRV;
};