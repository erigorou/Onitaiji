// -----------------------------------------------------
// ���O:	BossDashAttacking.h
// ���e:	�{�X�̓ːi�X�e�[�g���`
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_DASH_ATTACKING_DEFINED
#define BOSS_DASH_ATTACKING_DEFINED

// �C���N���[�h
#include "pch.h"
#include "Interface/IState.h"

// �O���錾
class Enemy;
class Cudgel;
class Player;

/// <summary>
/// �{�X�̓ːi�X�e�[�g
/// </summary>
class BossDashAttacking : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// �U���̒��߃��[�V�����̎���
	static constexpr float CHARGE_TIME = 1.0f;
	// �_�b�V�����鎞��
	static constexpr float DASH_TIME = 2.0f;
	// �ҋ@
	static constexpr float WAIT_TIME = 3.5f;
	// �U�����I����Ă��猳�ɖ߂鎞��
	static constexpr float RETURN_TIME = 5.0f;
	// ������
	static constexpr float TOTAL_TIME = 5.0f;
	// �ő呬�x
	static constexpr float MAX_SPEED = 90.0f;
	// sin�g�̑��x
	static constexpr float SIN_SPEED = 10.0f;
	// �X��(����)
	static constexpr float TILT_ANGLE = 20.0f;
	// �X��(�_�b�V��)
	static constexpr float TILT_ANGLE_DASH = 40.0f;

	// -----------------------------------
	// �����o�֐��i���J�j
	// -----------------------------------
public:
	// �R���X�g���N�^
	BossDashAttacking(Boss* boss);
	// �f�X�g���N�^
	~BossDashAttacking() override;
	// ����������
	void Initialize() override;
	// �X�e�[�g�ύX����(in)
	void PreUpdate() override;
	// �X�V��������
	void Update(const float& elapsedTime) override;
	// �X�e�[�g�X�V����(out)
	void PostUpdate() override;
	// �I������
	void Finalize() override;

	// -----------------------------------
	// �����o�֐��i����J�j
	// -----------------------------------
private:
	// �A�N�V�����̍X�V����
	void UpdateAction();
	// �U���̒��߃��[�V����
	void ChargeAction();
	// �_�b�V������
	void DashAction();
	// �ҋ@
	void WaitAction();
	// ���ɖ߂�
	void ReturnAction();

	// -----------------------------------
	// �����o�ϐ�
	// -----------------------------------
private:
	// ��]
	float m_angle;
	// �X��
	float m_bodyTilt;
	// �U����
	bool m_isAttacking;
	// ��]�p�s��
	DirectX::SimpleMath::Matrix m_rotMatrix;
	// �ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �t���[������
	float m_elapsedTime;
	// ������
	float m_totalSeconds;
	// �G
	Boss* m_boss;
	// �v���C���[
	IObject* m_player;
	// ���_
	Cudgel* m_cudgel;
};

#endif		// BOSS_DASH_ATTACKING_DEFINED
