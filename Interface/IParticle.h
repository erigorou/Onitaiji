// ----------------------------------------------
//
// @�p�[�e�B�N���̃C���^�[�t�F�[�X�N���X
// @ Ikeda Osuke
//
// ---------------------------------------------

#pragma once
#include "pch.h"

class IParticle
{
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�t���[�����ɂ�����������</param>
	/// <returns>�������Ă��邩</returns>
	virtual bool Update(float elapsedTime) = 0;
};