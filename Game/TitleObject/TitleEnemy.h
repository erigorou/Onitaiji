#pragma once  // ���d�ǂݍ��ݖh�~
#include "pch.h"
#include "Interface/IState.h"

// ===== �G�̏�� =================================================================
class EnemyTitleMoving;
class EnemyTitleIdling;

class TitleEnemy
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �G�̑��x
	static constexpr float TITLE_ENEMY_SPEED = 0.1f;
	// �G�̃X�P�[��
	static constexpr float TITLE_ENEMY_SCALE = 1.0f;
	// �N�[���^�C��
	static constexpr float COOL_TIME = 0.4f;
	// �X�e�[�g�̍ő吔
	static constexpr int STATE_MAX = 2;


	// -----------------------------
	// �񋓌^
	// -----------------------------
	enum class BossState
	{
		IDLING,  // �ҋ@���
		MOVING,  // �ړ����
	};

public:
	// -----------------------------
	// �A�N�Z�T
	// -----------------------------
	// �S�̍��W���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	// �S�̍��W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3 pos) { m_position = pos; }
	// �S�̉�]�p���擾����
	float GetAngle() const { return m_angle; }
	// �S�̉�]�p��ݒ肷��
	void SetAngle(const float angle) { m_angle = angle; }
	// �G�̃��[���h���W���擾����
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_worldMatrix; }
	// �G�̃��[���h���W��ݒ肷��
	void SetWorldMatrix(DirectX::SimpleMath::Matrix mat) { m_worldMatrix = mat; }
	
	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	TitleEnemy();
	// �f�X�g���N�^
	~TitleEnemy();
	// ����������
	void Initialize();
	// �V������ԂɑJ�ځi�X�e�[�g�p�^�[���j
	void ChangeState(BossState state);
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// �I������
	void Finalize();

private:
	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �X�e�[�g�̍쐬����
	void CreateState();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��]�p
	float m_angle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���f��
	DirectX::Model* m_model;
	// ���݂̃X�e�[�g
	IState* m_currentState;
	// �ҋ@���
	std::unique_ptr<EnemyTitleIdling> m_titleIdling;
	// �ړ����
	std::unique_ptr<EnemyTitleMoving> m_titleMoving;
	// �X�e�[�g�̔z��
	IState* m_states[STATE_MAX];
};
