// --------------------------------------------
//
// ���O:	BossFightButtonAction
// �@�\:	�{�X��ɐi�ރ{�^���̃A�N�V����
// ����:	�r�c����
//
// --------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "Interface/IAction.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Data/GameData.h"

/// <summary>
/// �{�X��̃{�^���̃A�N�V����
/// </summary>
class BossFightButtonAction final : public IAction
{
	// ------------------------------
	// �Œ�l
	// ------------------------------
private:
	// �x��
	static constexpr float DELAY = 2.2f;
	// �ړ�����
	static constexpr float MOVE_TIME = 1.5f;
	// �������W
	static constexpr float INIT_POSITION_Y = 2080.0f;
	// �ړ�����
	static constexpr float MOVE_DISTANCE = 800.0f;

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
	// ���s���e
	ActionParams Execute(ActionParams param, const float time) override
	{
		ActionParams result = param;

		// �{�X��{�^���̓����x��ݒ�
		if (GameData::GetInstance()->GetSelectStage() != 1)
			result.alpha = 0.5f;

		// �x�����Ȃ�Όv�Z����
		if (time < DELAY) return result;
		// �b���𐳋K������
		float easing = Math::Clamp(time - DELAY, 0.0f, MOVE_TIME) / MOVE_TIME;
		// �㉺�ɃA�j���[�V����������
		result.position.x = INIT_POSITION_Y - MOVE_DISTANCE * Easing::easeOutBack(easing);

		// ���ʂ�Ԃ�
		return result;
	}
};