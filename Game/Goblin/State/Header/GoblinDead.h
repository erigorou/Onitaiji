// --------------------------------------------------
//���O:	GoblinDead.h
//���e:	�S�u�����̎��S���
//�쐬:	�r�c����
// --------------------------------------------------
#pragma once
#ifndef GOBLIN_DEAD
#define GOBLIN_DEAD

// �C���N���[�h
#include "pch.h"
#include "Interface/IState.h"

// �O���錾
class Goblin;

/// <summary>
/// ���S�̎��S���
/// </summary>
class GoblinDead : public IState
{
	// --------------------
	// �Œ�l
	// --------------------
public:
	// ���S����
	static constexpr float DEAD_TIME = 2.5f;


	// ---------------------
	// �����o�֐�(���J)
	// ---------------------
public:
	// �R���X�g���N�^
	GoblinDead(Goblin* goblin);
	// �f�X�g���N�^
	~GoblinDead() override;
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

	// -------------------
	// �����o�֐�(����J)
	// -------------------
private:
	// �A�j���[�V�����̍X�V����
	void UpdateAnimation();

	// -------------------
	// �����ϐ�
	// -------------------
private:
	// ���S
	Goblin* m_goblin;
	// �o�ߎ���
	float m_totalTime;
	// �X�P�[��
	float m_scale;
	// �J�n�n�_
	DirectX::SimpleMath::Vector3 m_startPos;
};

#endif