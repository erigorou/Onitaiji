// --------------------------------------------
//
// ���O:	NormalAction
// �@�\:	�������Ȃ��A�N�V����
// ����:	�r�c����
//
// --------------------------------------------

#pragma once
// �C���N���[�h
#include "Interface/IAction.h"

/// <summary>
/// �������Ȃ��A�N�V����
/// </summary>
class NormalAction final : public IAction
{
	// ------------------------------
	// �����o�֐�
	// ------------------------------
public:
	// ---------------------------------------------------
	/// <summary>
	/// �A�N�V�����̎��s
	/// </summary>
	/// <param name="param">�p�����[�^�[</param>
	/// <param name="time">����</param>
	/// <returns>�A�N�V������̃p�����[�^�[</returns>
	// ---------------------------------------------------
	ActionParams Execute(ActionParams param, const float time) override
	{
		// �A�N�V�������ɂȂ�
		UNREFERENCED_PARAMETER(time);
		return param;
	}
};