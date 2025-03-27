// -----------------------------------------------------
// ���O:	BossSweeping.h
// ���e:	�{�X�̓ガ�����U���X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_SWEEPING_DEFINED
#define BOSS_SWEEPING_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Boss;
class Player;
class Easing;

/// <summary>
/// �{�X�̓ガ�����U���X�e�[�g
/// </summary>
class BossSweeping : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// �U���̒��߃��[�V�����̎���
	static constexpr float CHARGE_TIME = 0.8f;
	// �U������O�̎���
	static constexpr float WINDUP_TIME = 0.9f;
	// �U�����鎞��
	static constexpr float ATTACK_TIME = 1.5f;
	// �U���i�S�́j���I�����鎞��
	static constexpr float END_TIME = 2.3f;
	// �U���̒��߃��[�V�����̊p�x
	static constexpr float ROTATE_ANGLE = 20.0f;

	// ---------------------------
	// �����o�֐��i���J�j
	// ---------------------------
public:
	// �R���X�g���N�^
	BossSweeping(Boss* boss);
	// �f�X�g���N�^
	~BossSweeping() override;
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

	// ---------------------------
	// �����o�֐��i����J�j
	// ---------------------------
private:
	// �A�j���[�V�����̍X�V
	void UpdateAnimation();
	// ���߃��[�V�����̍X�V
	void UpdateChargeMotion();
	// �ガ�������[�V�����̍X�V
	void UpdateSweepMotion();

	// ---------------------------
	// �����o�ϐ�
	// ---------------------------
private:
	// �p�x
	float m_angle;
	// �ڕW�̊p�x
	float m_targetAngle;
	// ������
	float m_totalSeconds;
	// �G
	Boss* m_boss;
};

#endif		// BossSweeping_DEFINED
