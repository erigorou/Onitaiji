// -----------------------------------------------------
// ���O:	BossDead.h
// ���e:	�{�X�̎��S�X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_DEAD_DEFINED
#define BOSS_DEAD_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Boss;
class Player;
class Cudgel;

/// <summary>
/// �{�X�̎��S�X�e�[�g
/// </summary>
class BossDead : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
private:

	// ������
	static constexpr float TOTAL_TIME = 3.0f;
	// �X�����
	static constexpr float MAX_TILT_ANGLE = -90.0f;
	// �J������h�炷����
	static constexpr float CAMERA_SHAKE_POWER = 1.0f;
	// �J������h�炷�^�C�~���O
	static constexpr float CAMERA_SHAKE_TIMING = -89.0f;

	// ---------------------------
	// ���J�֐�
	// ---------------------------
public:
	// �R���X�g���N�^
	BossDead(Boss* boss);
	// �f�X�g���N�^
	~BossDead() override;
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
	// �����֐�
	// ---------------------------
private:
	// �A�j���[�V�����̍X�V
	void UpdateAnimation();

	// ---------------------------
	// �����o�ϐ�
	// ---------------------------
private:
	// �G
	Boss* m_boss;
	// ���_
	Cudgel* m_cudgel;
	// ��]
	float m_angle;
	// ������
	float m_totalSeconds;
	// �A�j���[�V�����p�̉�]���W
	float m_tiltAngle;
	// ��ԊJ�n���̑̂̌X�����擾
	float m_startTilt;
};

#endif		// Boss_IDLING_DEFINED
