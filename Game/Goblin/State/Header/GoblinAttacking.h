// --------------------------------------------------
//���O:	GoblinAttacking.h
//���e:	�S�u�����̍U�����
//�쐬:	�r�c����
// --------------------------------------------------
#pragma once
#ifndef GOBLIN_ATTACKING
#define GOBLIN_ATTACKING
// �C���N���[�h
#include "pch.h"
#include "Interface/IState.h"

// �O���錾
class Goblin;

/// <summary>
/// �S�u�����̍U�����
/// </summary>
class GoblinAttacking : public IState
{
	//--------------------
	// �Œ�l
	// --------------------
private:
	// ��Ԃ̎���
	static constexpr float STATE_TIME = 3.0f;
	// �ҋ@����
	static constexpr float CHARGE_TIME = 1.0f;
	// �U������
	static constexpr float ATTACK_TIME = 2.0f;
	// �߂鎞��
	static constexpr float RETURN_TIME = 3.0f;
	// �ł��������Ƃ��̃T�C�Y
	static constexpr float MAX_MINUS_SIZE = 0.35f;
	// �ő��ׂ鍂��
	static constexpr float MAX_Y_POS = 20.0f;

	// --------------------
	// �����o�֐�(���J)
	// --------------------
public:
	// �R���X�g���N�^
	GoblinAttacking(Goblin* goblin);
	// �f�X�g���N�^
	~GoblinAttacking() override;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �㏈�����s��
	void Finalize() override;

	// --------------------
	// �����o�֐�(����J)
	// --------------------
private:
	// �v���C���[�̒T�����s���B
	void SearchPlayer();
	// �A�j���[�V�����̍X�V
	void UpdateAnimation();

	void ChargeAnimation();
	void AttackAnimation();
	void ReturnAnimation();

private:
	// �e
	Goblin* m_goblin;
	// �o�ߎ���
	float m_totalTime;
	// �p�x
	float m_angle;
	// �ړ��p�̉�]�s��
	DirectX::SimpleMath::Matrix m_rotMatrix;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �ړ���
	DirectX::SimpleMath::Vector3 m_moveValue;
	// �ړ��ʒu
	DirectX::SimpleMath::Vector3 m_movePosition;
};
#endif