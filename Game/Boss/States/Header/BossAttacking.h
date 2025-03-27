// -----------------------------------------------------
// ���O:	BossApproaching.h
// ���e:	�{�X�̒ǔ��X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_ATTACKING_DEFINED
#define BOSS_ATTACKING_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Boss;
class Player;

/// <summary>
/// �{�X�̒@�����U���X�e�[�g
/// </summary>
class BossAttacking : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// ������
	static constexpr float TOTAL_TIME = 5.0f;
	// �G��ǂ������鎞��
	static constexpr float CHASE_TIME = 1.4f;

	// ---------------------------
	// �����o�֐��i���J�j
	// ---------------------------
public:
	// �R���X�g���N�^
	BossAttacking(Boss* boss);
	// �f�X�g���N�^
	~BossAttacking() override;
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
	// �����o�ϐ�
	// ---------------------------
private:
	// ��]
	float m_angle;
	// ������
	float m_totalSeconds;
	// �G
	Boss* m_boss;
	// �v���C���[
	IObject* m_player;
};

#endif		// BOSS_ATTACKING_DEFINED
