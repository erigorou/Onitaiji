// -----------------------------------------------------
// ���O:	Goblin.cpp
// ���e:	���S����������N���X
//			�X�e�[�g��Փ˔�����Ǘ�
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef GOBLIN_OBJECT
#define GOBLIN_OBJECT
// �C���N���[�h
#include "pch.h"
#include "Interface/IObject.h"
#include "Interface/IState.h"
#include "Interface/IEnemy.h"

// �O���錾
class HPSystem;
class EnemyEffect;
class GoblinIdling;
class GoblinAttacking;
class GoblinDead;
class GoblinTutorial;

/// <summary>
/// �S�u�����̃X�e�[�g
/// </summary>
enum class GoblinState
{
	IDLING,
	ATTACKING,
	DEAD,
	TUTORIAL
};

/// <summary>
/// ���S����������N���X
/// </summary>
class Goblin : public IEnemy
{
	// ---------------
	// �Œ�l
	// ---------------
public:
	// ���x
	static const float GOBLIN_SPEED;
	// �傫��
	static const float GOBLIN_SCALE;
	// �ő�HP
	static constexpr float GOBLIN_HP = 6.0f;
	// �����蔻��̔��a
	static constexpr float COLLISION_RADIUS = 16.0f;
	// �����蔻��̍���
	static constexpr float COLLISION_POS_Y = 2.0f;
	// �N�[���^�C��
	static constexpr float COOL_TIME = 0.1f;

	// -----------------------
	// �A�N�Z�T
	// -----------------------
public:
	// ���W���擾
	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }
	// ���W��ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
	// ���x���擾
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// ���x��ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// ��]�p���擾
	float GetAngle() const { return m_angle; }
	// ��]�p��ݒ�
	void SetAngle(const float angle) { m_angle = angle; }
	// ���[���h���W���擾
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_worldMatrix; }
	// �X�P�[����ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }
	// �̂̓����蔻����擾
	DirectX::BoundingSphere GetCollision() const { return *m_bodyCollision.get(); }
	// �U�������ǂ������擾
	bool IsAttacking() const { return m_nowAttacking; }
	// HP���擾
	HPSystem* GetHPSystem() override { return m_hp.get(); }
	// �U�������ǂ�����ݒ�
	void SetIsAttacking(bool isAttacking) { m_nowAttacking = isAttacking; }

	// -----------------------
	// �����o�֐�(���J)
	// -----------------------
public:
	// �R���X�g���N�^
	Goblin();
	// �f�X�g���N�^
	~Goblin();
	// �������֐�
	void Initialize();
	// �����蔻��̐���
	void CreateCollision();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);
	// �I������
	void Finalize();
	// �Փˉ\
	void CanHit(bool flag) override { m_canHit = flag; }
	// �Փˏ���
	void HitAction(InterSectData data) override;
	// �X�e�[�g�̕ύX
	void ChangeState(GoblinState state);
	// �S�u����������
	void DeleteGoblin();

	// -----------------------
	// �����o�֐�(����J)
	// -----------------------
private:
	// �X�e�[�g�̍쐬
	void CreateState();
	// ���[���h�s��̌v�Z
	void CalcWorldMatrix();
	// �����蔻��̈ړ�
	void MoveCollision();
	// �����m�F
	void CheckAlive();
	// �v���C���[�ɓ��������Ƃ��̏���
	void HitPlayer(InterSectData data);
	// ���S�ɓ��������Ƃ��̏���
	void HitGoblin(InterSectData data);
	// �G�ɓ��������Ƃ��̏���
	void HitBoss(InterSectData data);
	// �X�e�[�W�ɓ��������Ƃ��̏���
	void HitStage(InterSectData data);
	// ���ɓ��������Ƃ��̏���
	void HitSword(InterSectData data);
	// �_���[�W���󂯂��Ƃ��̏���
	void Damaged(float damage);
	// �N�[���^�C���̃J�E���g
	void CountCoolTime(float elapsedTime);

	// -----------------------
	// �����o�ϐ�
	// -----------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��]�p
	float m_angle;
	// �X�P�[��
	DirectX::SimpleMath::Vector3 m_scale;
	// ���[���h���W
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���f��
	DirectX::Model* m_model;
	// �����߂���
	DirectX::SimpleMath::Vector3 m_pushBackValue;

	// ���݂̃X�e�[�g
	IState* m_currentState;
	// �ҋ@
	std::unique_ptr<GoblinIdling> m_idling;
	// �U��
	std::unique_ptr<GoblinAttacking> m_attacking;
	// ���S
	std::unique_ptr<GoblinDead> m_dead;
	// �`���[�g���A��
	std::unique_ptr<GoblinTutorial> m_tutorial;
	// �X�e�[�g�̃��X�g
	std::vector<IState*> m_states;

	// HP
	std::unique_ptr<HPSystem> m_hp;
	// �G�G�t�F�N�g
	std::unique_ptr<EnemyEffect> m_enemyEffect;
	// �̂̓����蔻��
	std::unique_ptr<DirectX::BoundingSphere> m_bodyCollision;

	// �U�����t���O
	bool m_nowAttacking;
	// �U�����󂯂��t���O
	bool m_isHit;
	// �Փˉ\�t���O
	bool m_canHit;
	// �N�[���^�C��
	float m_coolTime;
};

#endif