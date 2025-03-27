// ---------------------------------------------------------------------------
//
// ���O:	TitleLogoAction
// �@�\:	�^�C�g����ʂŏォ��~���Ă��郍�S�̃A�j���[�V����
// ����:	�r�c����
//
// ---------------------------------------------------------------------------

#pragma once
// �C���N���[�h
#include "pch.h"
#include "Interface/IAction.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Libraries/MyLib/Math.h"

/// <summary>
/// �^�C�g�����S�̃A�N�V����
/// </summary>
class TitleLogoAction final : public IAction
{
	// ------------------------------
	// �Œ�l
	// ------------------------------
private:
	// �x��
	static constexpr float DELAY = 1.5f;
	// �ړ�����
	static constexpr float MOVE_TIME = 1.5f;
	// �������W
	static constexpr float INIT_POSITION_Y = 200.0f;
	// �ړ�����
	static constexpr float MOVE_DISTANCE = 200.0f;

	// ------------------------------
	// ���J�֐�
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
		ActionParams result = param;

		// �x�����Ȃ�Όv�Z����
		if (time < DELAY) return result;

		// �b���𐳋K������
		float easing = Math::Clamp(time - DELAY, 0.0f, MOVE_TIME) / MOVE_TIME;
		// �㉺�ɃA�j���[�V����������
		result.position.y = MOVE_DISTANCE * Easing::easeOutElastic(easing) - INIT_POSITION_Y;

		// ���ʂ�Ԃ�
		return result;
	}
};