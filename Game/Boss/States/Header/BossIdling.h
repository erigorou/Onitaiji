// -----------------------------------------------------
// ���O:	BossIdling.h
// ���e:	�{�X�̑ҋ@�X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_IDLING_DEFINED
#define BOSS_IDLING_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Boss;
class Player;

/// <summary>
/// �{�X�̑ҋ@�X�e�[�g
/// </summary>
class BossIdling : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// ������
	static constexpr float TOTAL_TIME = 1.0f;
	// ����
	static constexpr float FAR_DISTANCE = 20.0f;
	// �S�̂̊���
	static constexpr int TOTAL_RATE = 10;
	// �ガ�������s������
	static constexpr int SWEEPING_RATE = 3;
	// �����������s������
	static constexpr int ATTACKING_RATE = 7;
	// �_�b�V���U�����s������
	static constexpr int DASH_ATTACK_RATE = 8;
	// �������Ȃ�����
	static constexpr int IDLING_RATE = 10;
	// �v���C���[�̕����ɒǏ]���銄��
	static constexpr float LERP_RATE = 0.1f;

	// ---------------------------
	// �����o�֐��i���J�j
	// ---------------------------
public:
	// �R���X�g���N�^
	BossIdling(Boss* boss);
	// �f�X�g���N�^
	~BossIdling() override;
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
	// �����o�֐�(����J)
	// ---------------------------
private:
	// �A�j���[�V�����̍X�V
	void UpdateAnimation();
	// ���̃X�e�[�g�Ɉڍs���邩�����m
	void CheckNextState();

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

#endif
