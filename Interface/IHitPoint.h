#pragma once

#ifndef I_HITPOINT
#define I_HITPOINT

#include "pch.h"

class IHitPoint
{
public:
	// �_���[�W���󂯂�
	virtual bool Damage(int damage) = 0;

	// �q�[�����󂯂�
	virtual void Heal(int heal) = 0;

	// HP�̎擾
	virtual int GetHP() const = 0;

	// �ő�HP�̎擾
	virtual int GetMaxHP() const = 0;
};

#endif // !I_HITPOINT
