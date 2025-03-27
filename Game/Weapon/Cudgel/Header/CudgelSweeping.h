// ----------------------------------------------------------
// ���O:	CudgeSweeping
// 
// ���e:	�{�X�S�̕���̋��_�@�ガ�����̃X�e�[�g
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "Interface/IWeapon.h"

class Cudgel;
class Boss;

/// <summary>
/// �U�����
/// </summary>
class CudgelSweeping : public IWeapon
{
	// --------------------------
	// �Œ�l
	// ---------------------------
public:
	// �U���̒��߃��[�V�����̎���
	static constexpr float CHARGE_TIME = 0.8f;
	// �U������O�̎���
	static constexpr float WINDUP_TIME = 0.9f;
	// �U�����鎞��
	static constexpr float ATTACK_TIME = 2.0f;
	// �U���i�S�́j���I�����鎞��
	static constexpr float END_TIME = 2.3f;

	// ������]�p
	static constexpr float INITIAL_ROTATE_UD = 93.0f;
	// �U���̒��߃��[�V�����̊p�x
	static constexpr float CHARGE_ROTATE_ANGLE = 30.0f;
	// �U����̊p�x
	static constexpr float WINDUP_ROTATE_ANGLE = 240.0f;

	// �r�̒���
	static constexpr DirectX::SimpleMath::Vector3 ARM_LENGTH = { 0.0f, 5.0f, 0.0f };
	// ���_����ړ�����ʒu
	static constexpr DirectX::SimpleMath::Vector3 ZERO_DIREC = { 6.0f, 1.0f, 0.0f };

	// ---------------------------
	// �����o�֐�(���J)
	// ---------------------------
public:
	// �R���X�g���N�^
	CudgelSweeping(Cudgel* cudgel);
	// �f�X�g���N�^
	~CudgelSweeping()override;
	// ����������
	void Initialize()override;
	// ���O����
	void PreUpdate()override;
	// �X�V����
	void Update(float elapsedTime)override;
	// ���㏈��
	void PostUpdate()override;
	// �I������
	void Finalize()override;
	// �Փ˃C�x���g
	void HitAction(InterSectData data)override;

	// ---------------------------
	// �����o�֐�(����J)
	// ---------------------------
private:
	// Cudgel�̉�]���v�Z����֐�
	void UpdateCudgelRotation();
	// �`���[�W�A�j���[�V����
	void ChargeAnimation();
	// �U�����[�V����
	void AttackAnimation();
	// �I�����[�V����
	void EndAnimation();
	// �����l�Ƃ��Ďg�p���郏�[���h�s����v�Z����֐�
	void CalculateModelMatrix();
	// Cudgel�̍U�����[�V�����̉�]���v�Z����֐�
	DirectX::SimpleMath::Matrix CalculateAttackMatrix();
	// ���{�ƒ��_�̍��W���擾���� �� both ends = ���[
	void GetCudgelBothEnds();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ���E�p�x
	float m_angleRL;
	// �㉺�p�x
	float m_angleUD;
	// �e�̍��E�p�x
	float m_parentAngleRL;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �����蔻��p�̍s��
	DirectX::SimpleMath::Matrix m_collMatrix;
	// �X�e�[�g�̌o�ߎ���
	float m_totalSeconds;

	// �X�e�[�g�����L����e
	Cudgel* m_cudgel;
	// �{�X
	Boss* m_boss;

	// ���{�̍��W�z��
	std::vector<DirectX::SimpleMath::Vector3> m_rootPos;
	// ��[�̍��W�z��
	std::vector<DirectX::SimpleMath::Vector3> m_tipPos;
	// ���ʉ����Đ��������̃t���O
	bool m_playSound;
	// �v���C���[���q�b�g�ł��邩�̃t���O
	bool m_playerCanHit;
};