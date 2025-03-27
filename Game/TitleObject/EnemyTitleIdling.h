// ---------------------------------------------------------
//
// ���O:	EnemyTitleIdling.h
// ���e:	�G�̑ҋ@���
//			�X�e�[�g�p�^�[���Ŏ���
// �쐬;	�r�c����
//
// ---------------------------------------------------------
#pragma once
#ifndef ENEMY_TITLEIDLING_DEFINED
#define ENEMY_TITLEIDLING_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class TitleEnemy;


/// <summary>
/// �G�̑ҋ@��Ԃ��`
/// </summary>
class EnemyTitleIdling : public IState
{
	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	EnemyTitleIdling(TitleEnemy* enemy);
	// �f�X�g���N�^
	~EnemyTitleIdling() override;
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

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------

private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// �ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��]
	float m_angle;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMat;
	// ������
	float m_totalSeconds;
	// �G
	TitleEnemy* m_enemy;
};

#endif		// ENEMY_IDLING_DEFINED
