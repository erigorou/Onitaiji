// ---------------------------------------------------------
//
// ���O:	EnemyTitleMoving.h
// ���e:	�G�̍U�����
//			�X�e�[�g�p�^�[���Ŏ���
// �쐬;	�r�c����
//
// ---------------------------------------------------------
#pragma once
#ifndef ENEMY_TITLEMOVING_DEFINED
#define ENEMY_TITLEMOVING_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Particle;

/// <summary>
/// �G�̍U����Ԃ��`
/// </summary>
class EnemyTitleMoving : public IState
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// sin�g�̕�
	static constexpr float AMPLITUDE = 2.0f;
	// sin�g�̎��g��
	static constexpr float FREQUENCY = 1.0f;
	// �ŏ��l
	static constexpr float MINIMAL = 0.01f;
	// �J�����̗h�ꕝ
	static constexpr float SHAKE_POWER = 1.0f;

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	EnemyTitleMoving(TitleEnemy* enemy);
	// �f�X�g���N�^
	~EnemyTitleMoving() override;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V��������
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �I������
	void Finalize() override;

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// �ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��]
	float m_angle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMat;

	// ������
	float m_totalSeconds;
	// �G
	TitleEnemy* m_enemy;

	// �W�����v����
	bool m_isJump;
	// �V�F�C�N�ł��邩
	bool m_canShake;
	// �V�F�C�N�p���[
	float m_shakePower;
};

#endif		// ENEMY_IDLING_DEFINED
