// ---------------------------------------------------------
// ���O; KeyboardChacker.h
// 
// ���e: �L�[�{�[�h���͂̃`�F�b�N���s���N���X
// ����: �r�c����
//
// ---------------------------------------------------------

#pragma once
#include "pch.h"

/// <summary>
/// �L�[�{�[�h���͂̃`�F�b�N���s���N���X
/// </summary>
class KeyboardChacker
{
	// -------------------
	// �����o�֐�
	// -------------------
public:
	/// <summary>
	/// ���L�[�����͂��ꂽ���ǂ����𔻒肷��
	/// </summary>
	/// <param name="key">�����ꂽ�L�[</param>
	/// <returns>������Ă��邩</returns>
	static bool IsInputArrowKey(DirectX::Keyboard::Keys key)
	{
		return
			key == DirectX::Keyboard::Keys::Up ||
			key == DirectX::Keyboard::Keys::Down ||
			key == DirectX::Keyboard::Keys::Left ||
			key == DirectX::Keyboard::Keys::Right;
	}
};