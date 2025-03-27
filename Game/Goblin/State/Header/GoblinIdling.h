// --------------------------------------------------
//���O:	GoblinIdling.h
//���e:	�S�u�����̑ҋ@���
//�쐬:	�r�c����
// --------------------------------------------------
#pragma once
#ifndef GOBLIN_IDLING
#define GOBLIN_IDLING
// �C���N���[�h
#include "pch.h"
#include "Interface/IState.h"

// �O���錾
class Goblin;

/// <summary>
///	�S�u�����̑ҋ@���
/// </summary>
class GoblinIdling : public IState
{
	// -----------------------
	// �Œ�l
	// -----------------------
public:
	// �ŏ��N�[���^�C��
	static constexpr float MIN_COOLTIME = 1.0f;
	// �ő�N�[���^�C��
	static constexpr float MAX_COOLTIME = 4.0f;
	// �ŏ��̃N�[���^�C��
	static constexpr float INIT_COOLTIME = 5.0f;

	// -----------------------
	// �����o�֐�(���J)
	// -----------------------
public:
	// �R���X�g���N�^
	GoblinIdling(Goblin* goblin);
	// �f�X�g���N�^
	~GoblinIdling() override;
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
	// �v���C���[��T��
	void SearchPlayer();

	// -----------------------
	// �����o�ϐ�
	// -----------------------
private:
	// �e
	Goblin* m_goblin;
	// �o�ߎ���
	float m_TotalTime;
	// �N�[���^�C��
	float m_coolTime;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �p�x
	float m_angle;
	// ��]�s��
	DirectX::SimpleMath::Matrix m_rotMatrix;
};

#endif