// -----------------------------------------------------
// ���O:	BossApproaching.h
// ���e:	�{�X�̑ҋ@�X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_APPROACHING_DEFINED
#define BOSS_APPROACHIGN_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Boss;

/// <summary>
/// �G�̒ǔ��X�e�[�g
/// </summary>
class BossApproaching : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// ���b��
	static constexpr float TOTAL_TIME = 2.0f;
	// �ŏ��l
	static constexpr float MINIMAL = 0.01f;
	// ���x�̐��K���p
	static constexpr float NORMALIZE_VELOCITY = 75.0f;
	// �T�C���g�̐U��
	static constexpr float AMPLITUDE = 1.0f;
	// �T�C���g�̎��g��
	static constexpr float FREQUENCY = 1.0f;
	// �J�����̗h��̋���
	static constexpr float SHAKE_POWER = 1.0f;
	// �v���C���[�Ƃ̍ŏ�����
	static constexpr float MIN_DISTANCE = 20.0f;

	// �S�̂̊���
	static constexpr int TOTAL_RATE = 4;
	// �ガ�������s������
	static constexpr int SWEEPING_RATE = 1;
	// �����������s������
	static constexpr int ATTACKING_RATE = 2;
	// �������Ȃ�����
	static constexpr int IDLING_RATE = 3;

	// ---------------------------
	// �����o�֐�(���J)
	// ---------------------------
public:
	// �R���X�g���N�^
	BossApproaching(Boss* Boss);
	// �f�X�g���N�^
	~BossApproaching() override;
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

	// --------------------------
	// �����o�֐�(����J)
	// --------------------------
private:
	// �A�j���[�V�����̍X�V
	void UpdateAnimation(float elapsedTime);
	// �����̃X�e�[�g�Ɉڍs���邩�����m
	void CheckNextState();

	// ---------------------------
	// �����o�ϐ�
	// ---------------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// �ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��]
	float m_angle;
	// ������
	float m_totalSeconds;
	// �G
	Boss* m_boss;
	// �v���C���[
	IObject* m_player;
};

#endif		// Boss_IDLING_DEFINED
