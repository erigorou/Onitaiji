// ------------------------------------------------
// ���O:	HPSystem.cpp
// ���e:	HP�V�X�e���̃N���X
//			HP�������ׂẴI�u�W�F�N�g�����L����
// �쐬;	�r�c����
// ------------------------------------------------

// �C���N���[�h
#include "pch.h"
#include "HPSystem.h"

// ---------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="max">�ő�HP</param>
// ---------------------------------
HPSystem::HPSystem(float max)
	: m_maxHP(max)
	, m_hp(max)
{
}

// ---------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------
HPSystem::~HPSystem()
{
}

// ---------------------------------
/// <summary>
/// ��
/// </summary>
// ---------------------------------
void HPSystem::Heal(float hp)
{
	m_hp = std::min(m_hp + hp, m_maxHP);
}


// ---------------------------------
/// <summary>
/// �_���[�W
/// </summary>
//---------------------------------
bool HPSystem::Damage(float hp)
{
	m_hp = std::max(m_hp - hp, 0.0f);
	return CheckDie();
}

// ---------------------------------
/// <summary>
/// ���S����
/// </summary>
/// <returns>���S���Ă��邩</returns>
// ---------------------------------
bool HPSystem::CheckDie()
{
	return m_hp <= 0.0f;
}