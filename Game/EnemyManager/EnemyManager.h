// ---------------------------------------------
// ���O:	EnemyManager.h
// ���e:	�S�Ă̓G�̊Ǘ����s���N���X
//			���ׂĂ̓G�̐����A�X�V�A�`��A�폜���s��
// �쐬:	�r�c
// ---------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "Interface/IEnemy.h"

// �O���錾
class Boss;
class Goblin;
class IObject;
class PlayScene;

/// <summary>
/// �G�̊Ǘ��N���X
/// </summary>
class EnemyManager
{
	// ---------------------------
	// �\����
	// ---------------------------
public:
	// �G�̎��
	enum class EnemyType
	{
		Goblin, 
		Boss
	};

	// �G�̃f�[�^
	struct EnemyData
	{
		EnemyType type;
		std::unique_ptr<IEnemy> data;
	};

	// Json�œǂݍ��ޓG�̃f�[�^
	struct JsonEnemyData
	{
		std::string type;
		DirectX::SimpleMath::Vector3 position;
	};

	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// Json�f�[�^��ǂݍ���
	static constexpr wchar_t ENEMY_JSON_PATH[] = L"Resources/Jsons/EnemySpawnPoint.json";;

	// �{�X�����S�������Ƃ�`����ۂ̒x��
	static constexpr float BOSS_DEAD_DELAY = 3.0f;

	// ---------------------------
	// �A�N�Z�T
	// ---------------------------
public:
	// �{�X�̃|�C���^���擾
	Boss* GetBossEnemy();
	// �{�X�̍��W���擾
	DirectX::SimpleMath::Vector3 GetBossPosition();
	// �^�[�Q�b�g�Ƃ��Ă���G�̍��W���擾
	void* GetPicupEnemyPosition();

	// ---------------------------
	// �����o�֐�(in)
	// ---------------------------
public:
	// �R���X�g���N�^
	EnemyManager();
	// �f�X�g���N�^
	~EnemyManager();
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// �I������
	void Finalize();

	// �G�̐�������
	void GenerateEnemy(const DirectX::SimpleMath::Vector3& position, EnemyType type);
	// �S�ẴS�u������HP��0�ɂ���
	void AllGoblinHPZero();
	// �G�P�̂̍폜
	void DeleteEnemy(void* pointer);
	// �J�����̃^�[�Q�b�g�̐ݒ�
	void ChangeCameraTarget();
	// �G�������Ă��邩�̃t���O
	bool IsEnemysAlive();

	// �S�Ă̓G�ɔ�_���\��ʒB
	void AllEnemyCanHit(void* flag);

	// ---------------------------
	// �����o�֐�(out)
	// ---------------------------
private:

	// Json����G�̐���
	void GenerateEnemyFromJson();
	// �S�u�����̐�������
	void GenerateGoblin(const DirectX::SimpleMath::Vector3& position);
	// �{�X�̐�������
	void GenerateBoss(const DirectX::SimpleMath::Vector3& position);

	// ---------------------------
	// �����o�ϐ�
	// ---------------------------
private:
	// �G�̔z��
	std::vector<EnemyData> m_enemies;

	// �v���C�V�[��
	PlayScene* m_playScene;

	// ���݃^�[�Q�b�g�ɂ��Ă���G�̔z��ԍ�
	int m_targetEnemyIndex;
	// �^�[�Q�b�g�̍��W
	DirectX::SimpleMath::Vector3 m_targetPosition;

	DirectX::Model* m_goblinModel;
	DirectX::Model* m_bossModel;

	// �b��
	float m_elapsedTime;

	// �o�ߎ���
	float m_currentTime;

	// �C���f�b�N�X��
	int m_selectQuestIndex;
};