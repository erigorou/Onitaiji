#pragma once

#include "pch.h"

class ICameraState
{
public:
	virtual	~ICameraState()
	{}  // �f�X�g���N�^

	virtual void PreUpdate() = 0;		// �X�e�[�g�ύX�iin�j

	virtual void Update(
		const DirectX::SimpleMath::Vector3& playerPos,
		const DirectX::SimpleMath::Vector3& enemyPos,
		float elapsedTime

	) = 0;
	virtual void PostUpdate() = 0;		// �X�e�[�g�ύX�iout)
};
