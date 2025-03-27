// ----------------------------------------------------------
// ���O:	CudgelAttacking
// 
// ���e:	�{�X�S�̕���̋��_�@�ҋ@�U���̃X�e�[�g
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Cudgel/Header/CudgelIdling.h"
#include "Game/Weapon/Cudgel/Cudgel.h"

// -----------------------------------------------
// �R���X�g���N�^
// -----------------------------------------------
CudgelIdling::CudgelIdling(Cudgel* cudgel)
	:
	m_cudgel(cudgel),
	m_position{},
	m_velocity{},
	m_angle{},
	m_worldMatrix{ DirectX::SimpleMath::Matrix::Identity }
{
}

// -----------------------------------------------
// �f�X�g���N�^
// -----------------------------------------------
CudgelIdling::~CudgelIdling()
{
}

// -----------------------------------------------
// ����������
// -----------------------------------------------
void CudgelIdling::Initialize()
{
	// ���[���h�s��̏�����
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
}

// -----------------------------------------------
// ���O����
// -----------------------------------------------
void CudgelIdling::PreUpdate()
{
}

// -----------------------------------------------
// �X�V����
// -----------------------------------------------
void CudgelIdling::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// �G�̍��W���擾
	m_position = m_cudgel->GetBoss()->GetPosition();
	// �G�̉�]���擾
	m_angle = m_cudgel->GetBoss()->GetAngle();

	// �傫���̐ݒ�@���@���Z�b�g
	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateScale(Cudgel::CUDGEL_SCALE)
		// ���_�̈ʒu���炷�������炷
		*= DirectX::SimpleMath::Matrix::CreateTranslation(Cudgel::DIRECTION_ENEMY)
		// ���S�̂̉�]���s��
		*= DirectX::SimpleMath::Matrix::CreateRotationY(-m_angle)
		// �S�̍��W�Ɉړ�����
		*= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// ���[���h�s���ݒ肷��
	m_cudgel->SetWorldMatrix(m_worldMatrix);
	// �����蔻��̈ʒu��ݒ肷��
	m_cudgel->SetCollisionPosition(m_worldMatrix);
}

// -----------------------------------------------
// ���㏈��
// -----------------------------------------------
void CudgelIdling::PostUpdate()
{
}

// -----------------------------------------------
// �I������
// -----------------------------------------------
void CudgelIdling::Finalize()
{
}

// -----------------------------------------------
// �Փ˔���
// -----------------------------------------------
void CudgelIdling::HitAction(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}