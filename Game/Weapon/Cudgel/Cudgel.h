// ----------------------------------------------------------
// ���O:	Cudgel
// 
// ���e:	�{�X�S�̕���̋��_�N���X
//			�X�V������`����s��
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------
#pragma once
// �C���N���[�h
#include "Interface/IWeapon.h"
#include "Interface/IObject.h"

// �O���錾
class Boss;
class CudgelIdling;
class CudgelAttacking;
class CudgelSweeping;

/// <summary>
/// �{�X�S�̋��_�N���X
/// </summary>
class Cudgel : public IObject
{
	// --------------------------
	// �Œ�l
	// ---------------------------
public:
	// �傫��
	static constexpr float CUDGEL_SCALE = Boss::BOSS_SCALE * 1.4f;
	// �G�Ƃ̗���Ă��鋗��
	static constexpr DirectX::SimpleMath::Vector3 DIRECTION_ENEMY = { 8.0f, 5.0f, 0.0f };
	// ���_�̒���
	static constexpr DirectX::SimpleMath::Vector3 CUDGEL_LENGTH = { 0.0f, 50.0f, 0.0f };
	// ���_�̎����̈ʒu
	static constexpr DirectX::SimpleMath::Vector3 CUDGEL_HADLE_POS = { 0.0f, 10.0f, 0.0f };

	// ---------------------------
	// �A�N�Z�T
	// ---------------------------
public:
	// ���̃I�u�W�F�N�g�̃|�C���^��n��
	void* GetCudgelObject() { return this; }
	// �{�X�̃|�C���^��n��
	Boss* GetBoss() { return m_boss; }
	// �{�X�����S�������Ƃ�`����
	void BossDead() { m_isDead = true; }
	// �ʒu�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }
	// ���f���̎擾
	DirectX::Model* GetModel() const { return m_model; }
	// �ҋ@
	CudgelIdling* GetIdling() const { return m_idling.get(); }
	// �U��
	CudgelAttacking* GetAttacking() const { return m_attacking.get(); }
	// �ガ����
	CudgelSweeping* GetSweeping() const { return m_sweeping.get(); }
	// �����蔻��̈ʒu�̐ݒ�
	void SetCollisionPosition(DirectX::SimpleMath::Matrix mat) { m_originalBox.Transform(*m_collision.get(), mat); }
	// ���[���h�s��̐ݒ�
	void SetWorldMatrix(DirectX::SimpleMath::Matrix mat) { m_worldMatrix = mat; }

	// ---------------------------
	// �����o�֐�(���J)
	// ---------------------------
public:
	// �R���X�g���N�^
	Cudgel(Boss* boss);
	// �f�X�g���N�^
	~Cudgel();
	// ������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);
	// �I������
	void Finalize();
	// ���������Ƃ��̏���
	void HitAction(InterSectData) override;
	// �X�e�[�g��ύX����
	void ChangeState(void* state);

	// ---------------------------
	// �����o�֐�(����J)
	// ---------------------------
private:
	// �X�e�[�g�𐶐�
	void CreateState();
	// �����蔻��̐���
	void CreateCollision();

	// ---------------------------
	// �����o�ϐ�
	// ---------------------------
private:
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �p�x
	DirectX::SimpleMath::Vector3 m_angle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���f��
	DirectX::Model* m_model;

	// ���_�̓����蔻��1(���ۂ̓����蔻��)�@
	std::unique_ptr<DirectX::BoundingOrientedBox>	m_collision;
	// �I���W�i���̓����蔻�� (�I���W�i���͐��������邾���̂���)
	DirectX::BoundingOrientedBox m_originalBox;

	// ���݂̃X�e�[�g
	IWeapon* m_currentState;
	// �ҋ@
	std::unique_ptr<CudgelIdling> m_idling;
	// ��������
	std::unique_ptr<CudgelAttacking> m_attacking;
	// �ガ����
	std::unique_ptr<CudgelSweeping>	m_sweeping;
	// �X�e�[�g�̃��X�g
	std::vector<IWeapon*> m_states;

	// �{�X
	Boss* m_boss;

	// �{�X�����S������
	bool m_isDead;
};