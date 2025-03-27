// --------------------------------------------------
// ���O:	Sound.h
// ���e:	�T�E���h�Ǘ��N���X
// �쐬:	�r�c����
// --------------------------------------------------
#pragma once

// FMOD�p�̑O���錾
namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

class Sound
{
	// -----------------------------
	// �񋓌^
	// -----------------------------
public:
	// BGM�̎��
	enum class BGM_TYPE : unsigned int
	{
		TITLE,
		PLAY,
		WIN,
		LOSE
	};

	// SE�̎��
	enum class SE_TYPE : unsigned int
	{
		SYSTEM_OK,
		PLAYER_ATTACK,
		PLAYER_ATTACK2,
		PLAYER_DAMAGED,
		BOSS_MOVE,
		BOSS_ATTACK,
		BOSS_SWEEP
	};

	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �^�C�g��BGM
	static constexpr const char* TITLE_BGM_PATH = "Resources/Sounds/BGM/Title.mp3";
	// �v���CBGM
	static constexpr const char* PLAY_BGM_PATH = "Resources/Sounds/BGM/Play.mp3";
	// ����BGM
	static constexpr const char* WIN_BGM_PATH = "Resources/Sounds/BGM/Win.mp3";
	// �s�kBGM
	static constexpr const char* LOSE_BGM_PATH = "Resources/Sounds/BGM/Lose.mp3";

	// �I��SE
	static constexpr const char* SYSTEM_OK_PATH = "Resources/Sounds/SE/System/OK.mp3";
	// �v���C���[�̍U��SE
	static constexpr const char* PLAYER_ATTACK_SE_PATH = "Resources/Sounds/SE/Player/Attack.mp3";
	// �v���C���[�̍U��SE
	static constexpr const char* PLAYER_ATTACK2_SE_PATH = "Resources/Sounds/SE/Player/Attack2.mp3";
	// �v���C���[�̃_���[�WSE
	static constexpr const char* PLAYER_DAMAGED_SE_PATH = "Resources/Sounds/SE/Player/DamagedSE.mp3";
	// �{�X�̈ړ�SE
	static constexpr const char* ENEMY_MOVE_SE_PATH = "Resources/Sounds/SE/Enemy/Move.mp3";
	// �{�X�̍U��SE
	static constexpr const char* ENEMY_ATTACK_SE_PATH = "Resources/Sounds/SE/Enemy/Attack.mp3";
	// �{�X�̑|��SE
	static constexpr const char* ENEMY_SWEEP_SE_PATH = "Resources/Sounds/SE/Enemy/Sweep.mp3";

	// ������BGM����
	static constexpr float DEFAULT_BGM_VOLUME = 1.0f;
	// ������SE����
	static constexpr float DEFAULT_SE_VOLUME = 1.0f;
	// �t�F�[�h��
	static constexpr float FADE_VALUE = 1.0f;

	// -----------------------------
	// �A�N�Z�T
	// -----------------------------
public:
	// BGM�Đ��N���X�̃C���X�^���X���擾����
	static Sound* const GetInstance();

	// BGM�̉��ʂ𒲐�����֐�
	void SetBGMVolume(float volume);
	// SE�̉��ʂ𒲐�����֐�
	void SetSEVolume(float volume);

	// BGM�̕ύX
	static void ChangeBGM(BGM_TYPE type);
	// SE�̍Đ�
	static void PlaySE(SE_TYPE type);

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �f�X�g���N�^
	~Sound();
	// �X�V����
	static void Update();
	// SOUND�Ŏg�p�����I�u�W�F�N�g�����
	void FinalizeFMOD();

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �R���X�g���N�^
	Sound();
	// FMOD�̃V�X�e���̏�����
	void InitializeFMOD();
	// BGM���X�g�̐���
	void CreateBGMList();
	// SE���X�g�̐���
	void CreateSEList();
	// BGM�̓ǂݍ���
	void LoadBGM(BGM_TYPE type, const char* filePath);
	// SE�̓ǂݍ���
	void LoadSE(SE_TYPE type, const char* filePath);

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �C���X�^���X
	static std::unique_ptr<Sound> s_sound;

	// FMOD�̃V�X�e��
	FMOD::System* m_system;
	// BGM�p�̉����f�[�^
	FMOD::Sound* m_soundBGM;
	// BGM���Đ�����`�����l��
	FMOD::Channel* m_channelBGM;
	// SE���Đ�����`�����l��
	FMOD::Channel* m_channelSE;

	// BGM�p�̉����f�[�^���X�g
	std::vector<FMOD::Sound*> m_bgmList;
	// SE�p�̉����f�[�^���X�g
	std::vector<FMOD::Sound*> m_seList;

	// BGM�̉���
	float m_bgmVolume;
	// SE�̉���
	float m_seVolume;
	// ��ʂ̃t�F�[�h��(�t�F�[�h�ɉ�����BGM���s��)
	float m_fadeValue;
};
