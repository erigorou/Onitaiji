#pragma once
#include "pch.h"
#include "Interface/IWeapon.h"

class Sword;
class Easying;

/// <summary>
/// �����Y�������̍U��
/// </summary>
class SwordAttacking1 : public IWeapon
{
	// -----------------------
	// �Œ�l
	// -----------------------
public:
	// 90�x�̃��W�A��
	static const float RADIAN_90;
	// �U���̎���
	static constexpr float ATTACK_TIME = 0.5f;
	// �ʒu�����p
	static constexpr DirectX::SimpleMath::Vector3 MATRIX_DIRECTION = DirectX::SimpleMath::Vector3(1.0f, 2.0f, 0.0f);

	// ���̒��ߊp�x
	static constexpr float MAX_SIDE_ANGLE = -250.0f;

	// �����p�x
	static constexpr float INIT_ANGLE = 10.0f;

	// �c�̍ő�
	static constexpr float MAX_VERTICAL_ANGLE = 40.0f;

	// -----------------------
	// �����o�֐�(���J)
	// -----------------------
public:
	// �R���X�g���N�^
	SwordAttacking1(Sword* sword);
	// �f�X�g���N�^
	~SwordAttacking1();

	// ����������
	void Initialize()override;
	// ���O����
	void PreUpdate()override;
	// �X�V����
	void Update(float elapsedTime)override;
	void CreateSwordParticle();
	// ���㏈��
	void PostUpdate()override;
	// �I������
	void Finalize()override;
	// �Փˏ���
	void HitAction(InterSectData data)override;

	// ---------------------
	// �����o�֐�(����J)
	// ---------------------
private:
	// �A�j���[�V�����X�V����
	void UpdateAnimation();
	// ���[���h�s��̍X�V
	void UpdateWorldMatrix();
	// ���{�ƒ��_�̍��W���擾���� �� both ends = ���[
	void GetCudgelBothEnds();

	// -----------------------
	// �����o�ϐ�
	// -----------------------
private:
	// �\�[�h�̌����擾
	Sword* m_sword;

	DirectX::SimpleMath::Vector3	m_position;		// ���W
	DirectX::SimpleMath::Vector3	m_velocity;		// ���x
	float							m_angle;		// ���̉�]
	DirectX::SimpleMath::Vector3	m_rot;			// 3�����̌��̉�]
	DirectX::SimpleMath::Matrix		m_worldMatrix;	// ���[���h�s��
	float m_totalSeconds;

	std::vector<DirectX::SimpleMath::Vector3>	m_rootPos;	// ���{�̍��W
	std::vector<DirectX::SimpleMath::Vector3>	m_tipPos;	// ��[�̍��W
};