#pragma once
#include "pch.h"
#include "Libraries/MyLib/Collision/CollisionManager.h"

class IWeapon
{
public:
	// �f�X�g���N�^
	virtual~IWeapon() = default;
	// ������
	virtual void Initialize() = 0;
	// ���O����
	virtual void PreUpdate() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// ���㏈��
	virtual void PostUpdate() = 0;

	// �I������
	virtual void Finalize() = 0;

	virtual void HitAction(InterSectData data) = 0;
};