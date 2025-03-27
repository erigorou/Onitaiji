// ---------------------------------------------------------------
//
// ���O:	EasingFunctions.h
// ���e:	���^��Ԋ֐���񋟂���
// ����:	�r�c����
// 
// ---------------------------------------------------------------

#ifndef EASING_FUNCTIONS_H
#define EASING_FUNCTIONS_H

// �C���N���[�h
#include "Math.h"
#include <cmath>

// M_PI ����`����Ă��Ȃ��ꍇ�͎蓮�Œ�`
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/// <summary>
/// �C�[�W���O�֐�
/// </summary>
class Easing
{
public:
	/// <summary>
	/// �C�[�Y�C���T�C���֐�
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInSine(float easing) {
		return 1.0f - static_cast<float>(cos((easing * M_PI) / 2.0f));
	}

	/// <summary>
	/// �C�[�Y�A�E�g�T�C���֐�
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutSine(float easing) {
		return static_cast<float>(sin((easing * M_PI) / 2.0f));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�T�C���֐�
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutSine(float easing) {
		return static_cast<float>(-(cos(M_PI * easing) - 1.0) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���񎟊֐��i�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInQuad(float easing) {
		return easing * easing;
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�񎟊֐��i�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutQuad(float easing) {
		return easing < 0.5f ? 2.0f * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 2) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���L���[�r�b�N�֐��i�O���֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInCubic(float easing) {
		return easing * easing * easing;
	}

	/// <summary>
	/// �C�[�Y�A�E�g�L���[�r�b�N�֐��i�O���֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutCubic(float easing) {
		return 1.0f - static_cast<float>(pow(1.0f - easing, 3));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�L���[�r�b�N�֐��i�O���֐��E�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutCubic(float easing) {
		return easing < 0.5f ? 4.0f * easing * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 3) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���N�H�[�g�֐��i�l���֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInQuart(float easing) {
		return easing * easing * easing * easing;
	}

	/// <summary>
	/// �C�[�Y�A�E�g�N�H�[�g�֐��i�l���֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutQuart(float easing) {
		return 1.0f - static_cast<float>(pow(1.0f - easing, 4));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�N�H�[�g�֐��i�l���֐��E�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutQuart(float easing) {
		return easing < 0.5f ? 8.0f * easing * easing * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 4) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���N�B���g�֐��i�܎��֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInQuint(float easing) {
		return easing * easing * easing * easing * easing;
	}

	/// <summary>
	/// �C�[�Y�A�E�g�N�B���g�֐��i�܎��֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutQuint(float easing) {
		return 1.0f - static_cast<float>(pow(1.0f - easing, 5));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�N�B���g�֐��i�܎��֐��E�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutQuint(float easing) {
		return easing < 0.5f ? 16.0f * easing * easing * easing * easing * easing : 1.0f - static_cast<float>(pow(-2.0f * easing + 2.0f, 5) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���G�N�X�|�֐��i�w���֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInExpo(float easing) {
		return easing == 0 ? 0 : static_cast<float>(pow(2.0, 10.0f * easing - 10.0f));
	}

	/// <summary>
	/// �C�[�Y�A�E�g�G�N�X�|�֐��i�w���֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutExpo(float easing) {
		return easing == 1 ? 1 : 1.0f - static_cast<float>(pow(2.0, -10.0f * easing));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�G�N�X�|�֐��i�w���֐��E�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutExpo(float easing) {
		return easing == 0 ?
			0 : easing == 1 ?
			1 : easing < 0.5f ?
			static_cast<float>(pow(2.0, 20.0f * easing - 10.0f) / 2.0) : 
			static_cast<float>((2.0f - pow(2.0, -20.0f * easing + 10.0f)) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���T�[�N�֐��i�~�ʊ֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInCirc(float easing) {
		return 1.0f - static_cast<float>(sqrt(1.0f - pow(easing, 2)));
	}

	/// <summary>
	/// �C�[�Y�A�E�g�T�[�N�֐��i�~�ʊ֐��E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutCirc(float easing) {
		return static_cast<float>(sqrt(1.0f - pow(easing - 1.0f, 2)));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�T�[�N�֐��i�~�ʊ֐��E�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutCirc(float easing) {
		return easing < 0.5f ? static_cast<float>((1.0f - sqrt(1.0f - pow(2.0f * easing, 2))) / 2.0) : static_cast<float>((sqrt(1.0f - pow(-2.0f * easing + 2.0f, 2)) + 1.0f) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���o�b�N�֐��i�I�[�o�[�V���[�g�E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInBack(float easing) {
		const float overshoot = 1.70158f;
		const float factor = overshoot + 1.0f;
		return factor * easing * easing * easing - overshoot * easing * easing;
	}

	/// <summary>
	/// �C�[�Y�A�E�g�o�b�N�֐��i�I�[�o�[�V���[�g�E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutBack(float easing) {
		const float overshoot = 1.70158f;
		const float factor = overshoot + 1.0f;
		return 1.0f + factor * static_cast<float>(pow(easing - 1.0f, 3)) + overshoot * static_cast<float>(pow(easing - 1.0f, 2));
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�o�b�N�֐��i�I�[�o�[�V���[�g�E�����E�����j
	/// </summary>
	/// <param name="easing">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutBack(float easing) {
		const float overshoot = 1.70158f;
		const float adjustedOvershoot = overshoot * 1.525f;
		return easing < 0.5f
			? static_cast<float>((pow(2.0f * easing, 2) * ((adjustedOvershoot + 1.0f) * 2.0f * easing - adjustedOvershoot)) / 2.0)
			: static_cast<float>((pow(2.0f * easing - 2.0f, 2) * ((adjustedOvershoot + 1.0f) * (2.0f * easing - 2.0f) + adjustedOvershoot) + 2.0f) / 2.0);
	}

	/// <summary>
	/// �C�[�Y�C���E�G���X�e�B�b�N�֐��i�e�ނ悤�ȉ����j
	/// </summary>
	/// <param name="progress">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInElastic(float progress) {
		const float period = (2.0f * M_PI) / 3.0f;
		return progress == 0 ? 0 : progress == 1 ? 1 : -static_cast<float>(pow(2.0, 10.0f * progress - 10.0f) * sin((progress * 10.0f - 10.75f) * period));
	}

	/// <summary>
	/// �C�[�Y�A�E�g�E�G���X�e�B�b�N�֐��i�e�ނ悤�Ȍ����j
	/// </summary>
	/// <param name="progress">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutElastic(float progress) {
		const float period = (2.0f * M_PI) / 3.0f;
		return progress == 0 ? 0 : progress == 1 ? 1 : static_cast<float>(pow(2.0, -10.0f * progress) * sin((progress * 10.0f - 0.75f) * period) + 1.0f);
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�E�G���X�e�B�b�N�֐��i�e�ނ悤�ȉ����E�����j
	/// </summary>
	/// <param name="progress">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutElastic(float progress) {
		const float period = (2.0f * M_PI) / 4.5f;
		return progress == 0 ? 
			0 : progress == 1 ?
			1 : progress < 0.5f ?
			static_cast<float>(-(pow(2.0, 20.0f * progress - 10.0f) * sin((20.0f * progress - 11.125f) * period)) / 2.0):
			static_cast<float>((pow(2.0, -20.0f * progress + 10.0f) * sin((20.0f * progress - 11.125f) * period)) / 2.0 + 1.0f);
	}

	/// <summary>
	/// �C�[�Y�C���E�o�E���X�֐��i���˂�悤�ȉ����j
	/// </summary>
	/// <param name="progress">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInBounce(float progress) {
		return 1.0f - easeOutBounce(1.0f - progress);
	}

	/// <summary>
	/// �C�[�Y�A�E�g�E�o�E���X�֐��i���˂�悤�Ȍ����j
	/// </summary>
	/// <param name="progress">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeOutBounce(float progress) {
		const float coefficient = 7.5625f;
		const float divisor = 2.75f;
		if (progress < 1.0f / divisor) {
			return coefficient * progress * progress;
		}
		else if (progress < 2.0f / divisor) {
			return coefficient * (progress -= 1.5f / divisor) * progress + 0.75f;
		}
		else if (progress < 2.5f / divisor) {
			return coefficient * (progress -= 2.25f / divisor) * progress + 0.9375f;
		}
		else {
			return coefficient * (progress -= 2.625f / divisor) * progress + 0.984375f;
		}
	}

	/// <summary>
	/// �C�[�Y�C���A�E�g�E�o�E���X�֐��i���˂�悤�ȉ����E�����j
	/// </summary>
	/// <param name="progress">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeInOutBounce(float progress) {
		return progress < 0.5
			? (1 - easeOutBounce(1 - 2 * progress)) / 2
			: (1 + easeOutBounce(2 * progress - 1)) / 2;
	}

	/// <summary>
	/// �C�[�Y�C���E�C�[�Y�A�E�g�̒��ԓ_��ݒ肷���Ԋ֐��i�O����Out�A�㔼��In�j
	/// </summary>
	/// <param name="t">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <param name="threshold">�O���ƌ㔼�̐؂�ւ��|�C���g�i0.0�`1.0�j</param>
	/// <param name="firstSize">��ԊJ�n���̒l</param>
	/// <param name="maxSize">��ԏI�����̒l</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeBetweenIn(float t, float threshold, float firstSize, float maxSize)
	{
		// threshold �� 0 ~ 1 �͈̔͊O�̏ꍇ�A�␳
		threshold = Math::Clamp(threshold, 0.0f, 1.0f);

		if (t <= threshold) {
			return firstSize * Easing::easeOutBack(t / threshold);
		}
		else {
			return firstSize + (maxSize - firstSize) * Easing::easeInQuad((t - threshold) / (1.0f - threshold));
		}
	}

	/// <summary>
	/// �C�[�Y�A�E�g�E�C�[�Y�C���̒��ԓ_��ݒ肷���Ԋ֐��i�O����Out�A�㔼��InOut�j
	/// </summary>
	/// <param name="t">��Ԃ̐i�s�x�i0.0�`1.0�j</param>
	/// <param name="threshold">�O���ƌ㔼�̐؂�ւ��|�C���g�i0.0�`1.0�j</param>
	/// <param name="firstSize">��ԊJ�n���̒l</param>
	/// <param name="maxSize">��ԏI�����̒l</param>
	/// <returns>��Ԍ�̒l</returns>
	static float easeBetweenOut(float t, float threshold, float firstSize, float maxSize)
	{
		// threshold �� 0 ~ 1 �͈̔͊O�̏ꍇ�A�␳
		threshold = Math::Clamp(threshold, 0.0f, 1.0f);

		if (t <= threshold)
		{
			return firstSize * Easing::easeOutSine(t / threshold);
		}
		else
		{
			return firstSize + (maxSize - firstSize) * Easing::easeInOutCubic((t - threshold) / (1.0f - threshold));
		}
	}
};

#endif // EASING_FUNCTIONS_H