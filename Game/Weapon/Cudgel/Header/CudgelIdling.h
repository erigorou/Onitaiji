// ----------------------------------------------------------
// ���O:	CudgelIdling
// 
// ���e:	�{�X�S�̕���̋��_�@�ҋ@�U���̃X�e�[�g
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

/// <summary>
/// �ҋ@���
/// </summary>
class CudgelIdling : public IWeapon
{
	// --------------------------
	// �����o�֐�(���J)
	// ---------------------------
public:
	// �R���X�g���N�^
	CudgelIdling(Cudgel* cudgel);
	// �f�X�g���N�^
	~CudgelIdling()override;
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
	// �����o�ϐ�
	// ---------------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �p�x
	float m_angle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���_�̌�
	Cudgel* m_cudgel;
};