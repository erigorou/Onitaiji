// ------------------------------------------------
// ���O:	HPSystem.h
// ���e:	HP�V�X�e���̃N���X
//			HP�������ׂẴI�u�W�F�N�g�����L����
// �쐬;	�r�c����
// ------------------------------------------------
#ifndef HP_SYSTEM
#define HP_SYSTEM
#pragma once
// �C���N���[�h
#include "pch.h"

/// <summary>
/// HP�V�X�e���N���X
/// </summary>
class HPSystem
{
// ------------------------------------------------
// �A�N�Z�T
// ------------------------------------------------
public:
	// �ő�HP
	float GetMaxHP() const { return m_maxHP; }
	// ���݂�HP
	float GetHP() const { return m_hp; }
	// HP��ݒ�
	void SetHP(float hp) { m_hp = hp; }

// ------------------------------------------------
// �����o�֐�(���J)
// ------------------------------------------------
public:
	// �R���X�g���N�^
	HPSystem(float max);
	// �f�X�g���N�^
	~HPSystem();
	// ��
	void Heal(float hp);
	// �_���[�W
	bool Damage(float hp);

// ------------------------------------------------
// �����o�֐�(����J)
// ------------------------------------------------
private:
	// ���S����
	bool CheckDie();


// ------------------------------------------------
// �����o�ϐ�
// ------------------------------------------------
private:
	// �ő�HP
	float m_maxHP;
	// ���݂�HP
	float m_hp;
};
#endif