// ----------------------------------------------------------
// ���O:	CudgelAttacking
// 
// ���e:	�{�X�S�̕���̋��_�@���������U���̃X�e�[�g
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------

#pragma once
// �C���N���[�h
#include "pch.h"
#include "Interface/IWeapon.h"

// �O���錾
class Cudgel;
class Enemy;
class Particle;
class Easying;

/// <summary>
/// �U�����
/// </summary>
class CudgelAttacking : public IWeapon
{
	// --------------------------
	// �Œ�l
	// ---------------------------
public:
	// �U���̒��߃��[�V�����̎���
	static constexpr float CHARGE_TIME = 0.8f;
	// �U������O�̎���
	static constexpr float WINDUP_TIME = 1.0f;
	// �U�����鎞��
	static constexpr float ATTACK_TIME = 1.6f;
	// �U�����I����Ă���ҋ@���鎞��
	static constexpr float STOP_TIME = 2.3f;
	// �U�����I����Ă��猳�ɖ߂鎞��
	static constexpr float RETURN_TIME = 2.8f;
	// �U���i�S�́j���I�����鎞��
	static constexpr float END_TIME = 3.3f;
	// �r�̒���
	static constexpr DirectX::SimpleMath::Vector3 ARM_LENGTH = { 0.0f, 4.0f, 0.0f };
	// ���_����ړ�����n�_
	static constexpr DirectX::SimpleMath::Vector3 ZERO_DIREC = { 8.0f, 1.0f, 0.0f };
	// ���ߎ��̊p�x
	static constexpr float CHARGE_ANGLE = 40.0f;
	// �I�����̊p�x
	static constexpr float END_ANGLE = 135.0f;
	// �����̊p�x
	static constexpr float INIT_ANGLE = 20.0f;
	// �U���̊p�x
	static constexpr float ATTACK_ANGLE = 95.0f;

	// SE���Đ����鎞��
	static constexpr float SOUND_TIME = 0.9f;

	// ---------------------------
	// �����o�֐�(���J)
	// ---------------------------
public:
	// �R���X�g���N�^
	CudgelAttacking(Cudgel* cudgel);
	// �f�X�g���N�^
	~CudgelAttacking()override;
	// ����������
	void Initialize()override;
	// ���O����
	void PreUpdate()override;
	// �X�V����
	void Update(float elapsedTime)override;
	void UpdateAnimation();
	// ���㏈��
	void PostUpdate()override;
	// �I������
	void Finalize()override;
	// �Փ˃C�x���g
	void HitAction(InterSectData data)override;

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// Cudgel�̉�]���v�Z����֐�
	void UpdateCudgelRotation();
	// �����l�Ƃ��Ďg�p���郏�[���h�s����v�Z����֐�
	void CalculateModelMatrix();
	// Cudgel�̍U�����[�V�����̉�]���v�Z����֐�
	DirectX::SimpleMath::Matrix CalculateAttackMatrix();
	// ���{�ƒ��_�̍��W���擾���� �� both ends = ���[
	void GetCudgelBothEnds(float _totalTime);
	// ���߃��[�V����
	void HandleChargePhase(float t);
	// �U���O�̃��[�V����
	void HandleWindoupPhase();
	// �U�����[�V����
	void HandleAttackPhase(float t);
	// �U����̃��[�V����
	void KeepStampPhase();
	// ���ɖ߂郂�[�V����
	void ReturnToOriginalPhase(float t);
	// �p�[�e�B�N���𐶐�����
	void HandleSlamParticles();
	// �U����Ԃ��X�V����
	void UpdateAttackState();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �U���t���O
	bool m_canHit;
	// �G�̊p�x
	float m_enemyAngle;
	// ���E�p�x
	float m_angleRL;
	// �㉺�p�x
	float m_angleUD;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �X�e�[�g�̌o�ߎ���
	float m_totalSeconds;
	// ���W���L�^����C���^�[�o���̌v���p�ϐ�
	float m_recordPointTimer;
	// �X�e�[�g�����L����e
	Cudgel* m_cudgel;

	// �p�[�e�B�N��
	Particle* m_particles;
	// ���{�̍��W�z��
	std::vector<DirectX::SimpleMath::Vector3> m_rootPos;
	// ��[�̍��W�z��
	std::vector<DirectX::SimpleMath::Vector3> m_tipPos;
	// �p�[�e�B�N���𐶐��������̃t���O
	bool m_canGenerateSlamParticles;
	// ���ʉ����Đ��������̃t���O
	bool m_playSound;
};