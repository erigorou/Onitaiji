// -----------------------------------------------
//
// �Q�[�W�nUI�̃C���^�[�t�F�[�X�N���X
//
// -----------------------------------------------

#pragma once

#ifndef IGaugeUI_DEFINED
#define IGaugeUI_DEFINED

#include "pch.h"

class IUserInterface
{
public:

	// �f�X�g���N�^
	virtual ~IUserInterface() = default;
	// �������֐�
	virtual void Initialize(DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 size) = 0;
	// �X�V�֐�
	virtual void Update() = 0;
	// �`��֐�5
	virtual void Render() = 0;
	// �I���֐�
	virtual void Finalize() = 0;

	// �����֐�
	virtual void MinusValue(float value) = 0;
	// �㏸�֐�
	virtual void PlusValue(float value) = 0;

	// �Q�[�W�̗ʂ�ݒ�
	virtual void SetValue(float max) = 0;
	// �Q�[�W�̗ʂ��擾
	virtual void GetValue(float value) = 0;
};

#endif
