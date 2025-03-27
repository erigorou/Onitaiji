// --------------------------------------------------
//���O:	GoblinTutorial.h
//���e:	�`���[�g���A�����̃S�u�����X�e�[�g
//�쐬:	�r�c����
// --------------------------------------------------
#pragma once
#ifndef GOBLIN_TUTORIAL
#define GOBLIN_TUTORIAL
// �C���N���[�h
#include "pch.h"
#include "Interface/IState.h"
// �O���錾
class Goblin;

/// <summary>
/// �`���[�g���A�����̃S�u�����X�e�[�g
/// </summary>
class GoblinTutorial : public IState
{
	// --------------------
	// �萔
	// --------------------
private:
	// �X�N���[���V���b�g����鎞��
	static constexpr float SCREENSHOT_TIME = 3.0f;

	// --------------------
	// �����o�֐�(���J)
	// --------------------
public:
	// �R���X�g���N�^
	GoblinTutorial(Goblin* goblin);
	// �f�X�g���N�^
	~GoblinTutorial() override;
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

	// ----------------------
	// �����o�ϐ�
	// ----------------------
private:
	// �e
	Goblin* m_goblin;
	// �o�ߎ���
	float m_TotalTime;
	// �N�[���^�C��
	float m_coolTime;
};
#endif