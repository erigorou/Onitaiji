// ----------------------------------------------
// ���O;	Math.h
// 
// ���e:	�v�Z�����N���X
//			�����̂������������܂Ƃ߂Ă����Ƃ���
// ����:	�r�c����
//
// ----------------------------------------------

#pragma once
// �C���N���[�h
#include "pch.h"
#include "random"

// ���O���
using namespace DirectX::SimpleMath;

// M_PI ����`����Ă��Ȃ��ꍇ�͎蓮�Œ�`
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/// <summary>
/// �v�Z�����N���X
/// </summary>
class Math
{
public:
	/// <summary>
	/// �����_��Z�Z�ʂ�艺��؂�̂Ă鏈��
	/// </summary>
	/// <param name="num">�؂�̂Ă鐔</param>
	/// <param name="prec">�����_��Z�Z��</param>
	/// <returns>�؂�̂Ă��l</returns>
	static float truncate_float(const float num, const int prec)
	{
		// �w�肳�ꂽ���x�Ɋ�Â��ăX�P�[�����v�Z
		float scale = static_cast<float>(std::pow(10.0f, prec));
		// �����_�ȉ��� "prec" �ʁ@������؂�̂Ă��A�Ԃ��B
		return std::trunc(num * scale) / scale;
	};

	/// <summary>
	/// �����_��Z�Z�ʂ�艺��؂�̂Ă鏈��
	/// </summary>
	/// <param name="num">�؂�̂Ă鐔</param>
	/// <param name="prec">�����_��Z�Z��</param>
	/// <returns>�؂�̂Ă��l</returns>
	static Vector3 truncate_vector(Vector3 num, const int prec)
	{
		// x,y,z�����ꂼ��؂�̂Ă���
		num.x = truncate_float(num.x, prec);
		num.y = truncate_float(num.y, prec);
		num.z = truncate_float(num.z, prec);
		// �v�Z���ʂ�Ԃ�
		return num;
	}

	/// <summary>
	/// �v���C���[�Ɠ������Ă��鎞�ɉ����߂��̗ʂ��v������
	/// </summary>
	/// <param name="A">�����߂���鑤��Sphere</param>
	/// <param name="B">�Œ肳���ق���Sphere</param>
	/// <returns>�����߂��̒l�@[ A�̍��W�@+= return�l ]</returns>
	static Vector3 pushBack_BoundingSphere(DirectX::BoundingSphere A, DirectX::BoundingSphere B)
	{
		Vector3 diffVec = A.Center - B.Center;	// A�̒��S��B�̒��S�Ƃ̍����x�N�g�����擾����

		float diffLength = diffVec.Length();	// A�̒��S��B�̒��S�Ƃ̋������擾����
		float sumLength = A.Radius + B.Radius;	// A��B�̔��a�̍��v���擾����

		diffLength = sumLength - diffLength;	// A���߂荞�񂾋������v�Z����
		diffVec.Normalize();					// �����x�N�g���𐳋K������

		return diffVec * diffLength;			// �����߂��x�N�g�����v�Z���A�Ԃ�
	}

	/// <summary>
	/// �Q�[���̃X�e�[�W���̓����ɂ���Ƃ��ɊO�ɏo��Ȃ��悤�ɉ����߂��̗ʂ��v�Z����
	/// </summary>
	/// <param name="A">�����߂����ق���Sphere</param>
	/// <param name="B">�����Ȃ��ق���Sphere</param>
	/// <returns>�����߂��̒l [ A�̍��W += return�l ]</returns>
	static Vector3 pushFront_BoundingSphere(DirectX::BoundingSphere A, DirectX::BoundingSphere B)
	{
		Vector3 diffVec = A.Center - B.Center; // A�̒��S��B�̒��S�Ƃ̍����x�N�g�����擾����

		float diffLength = diffVec.Length(); // A�̒��S��B�̒��S�Ƃ̋������擾����
		float boundaryLength = B.Radius - A.Radius; // A��B�̓����Ɏ��܂邽�߂̋������v�Z����

		// A��B�̊O���ɂ���ꍇ
		if (diffLength > boundaryLength)
		{
			diffLength = boundaryLength - diffLength; // A���߂荞�񂾋������v�Z����
			diffVec.Normalize(); // �����x�N�g���𐳋K������

			// �����߂��x�N�g�����v�Z���Ԃ�
			return diffVec * diffLength;
		}

		// �����߂����s�v�ȏꍇ�̓[���x�N�g����Ԃ�
		return Vector3(0, 0, 0);
	}

	/// <summary>
	/// �T�C���g���v�Z������@�iUpdate�ōX�V�j
	/// </summary>
	/// <param name="totalTime">�v�Z���n�܂��Ă���̎���</param>
	/// <param name="amplitude">�U��</param>
	/// <param name="frequency">���g��</param>
	/// <returns>�T�C���g�̒l</returns>
	static float CalculatingSinWave(const float totalTime, const float amplitude, const float frequency)
	{
		// �T�C���g�̌v�Z����
		return amplitude * std::sin(2.0f * DirectX::XM_PI * frequency * totalTime);
	}

	/// <summary>
	/// 2�̈ʒu�x�N�g���Ԃ̊p�x���v�Z���܂��B
	/// </summary>
	/// <param name="posA">�ŏ��̈ʒu�x�N�g��</param>
	/// <param name="posB">2�Ԗڂ̈ʒu�x�N�g��</param>
	/// <returns>�ʒu�x�N�g���Ԃ̊p�x�i���W�A���P�ʁj</returns>
	static float CalculationAngle(DirectX::SimpleMath::Vector3 posA, DirectX::SimpleMath::Vector3 const posB)
	{
		using namespace DirectX::SimpleMath;

		Vector3 forward = posB - posA;		// �G�̕������x�N�g���Ŏ擾
		forward.Normalize();				// ���K��

		Vector3 worldForward = Vector3::Forward;			// ���[���h���W�̑O���x�N�g�����쐬
		float dotProduct = forward.Dot(worldForward);		// ���ς��擾
		float angle = acosf(dotProduct);					// ���ς���p�x���擾(�ʓx�@)

		Vector3 crossProduct = forward.Cross(worldForward);	// �J�����̑O�����x�N�g�����E�����Ɍ����Ă��邩�ǂ����ŕ���������
		angle = (crossProduct.y < 0) ? -angle : angle;		// -180 ~ 180�Ɏ��߂�B

		return angle;		// �p�x�i���W�A���P�ʁj��Ԃ�
	}

	/// <summary>
	/// min <= return <= max �͈̔͂ŗ����𐶐�����
	/// </summary>
	/// <param name="min">�Œ�l</param>
	/// <param name="max">�ō��l</param>
	static int RandomInt(int min, int max)
	{
		if (min > max) std::swap(min, max);

		std::random_device seed;							// �����_���ȃV�[�h�l�𐶐�
		std::default_random_engine engine(seed());			// �V�[�h�l�����ɗ��������G���W�����`
		std::uniform_int_distribution<> random(min, max);	// min����max�܂ł̈�l������������`
		return random(engine);								// �����𐶐����ĕԂ�
	}

	/// <summary>
	/// min <= return <= max �͈̔͂ŕ��������_���^�̗����𐶐�����
	/// </summary>
	/// <param name="min">�Œ�l</param>
	/// <param name="max">�ō��l</param>
	/// <returns>�������ꂽ����</returns>
	static float RandomFloat(float min, float max)
	{
		if (min > max) std::swap(min, max);

		std::random_device seed;								// �����_���ȃV�[�h�l�𐶐�
		std::default_random_engine engine(seed());				// �V�[�h�l�����ɗ��������G���W�����`
		std::uniform_real_distribution<float> random(min, max); // min����max�܂ł̈�l������������`
		return random(engine);									// �����𐶐����ĕԂ�
	}

	/// <summary>
	/// min <= return <= max �͈̔͂ŕ��������_���^�̗����𐶐�����
	/// </summary>
	/// <param name="min">�Œ�l</param>
	/// <param name="max">�ō��l</param>
	/// <returns>�������ꂽ����</returns>
	static DirectX::SimpleMath::Vector3 RandomVector3(DirectX::SimpleMath::Vector3 min, DirectX::SimpleMath::Vector3 max)
	{
		std::random_device seed;								// �����_���ȃV�[�h�l�𐶐�
		std::default_random_engine engine(seed());				// �V�[�h�l�����ɗ��������G���W�����`
		std::uniform_real_distribution<float> randomX(min.x, max.x); // min����max�܂ł̈�l������������`
		std::uniform_real_distribution<float> randomY(min.y, max.y); // min����max�܂ł̈�l������������`
		std::uniform_real_distribution<float> randomZ(min.z, max.z); // min����max�܂ł̈�l������������`

		return Vector3(randomX(engine), randomY(engine), randomZ(engine)); // �����𐶐����ĕԂ�
	}

	/// <summary>
	/// 0 ~ 1 �Ő��K�����ꂽ�T�C���g��Ԃ�
	/// </summary>
	/// <param name="t">�b��</param>
	/// <returns>���K�����ꂽ�T�C���g</returns>
	static float NormalizeSin(float t)
	{
		return static_cast<float>(sin(t * M_PI));
	}

	/// <summary>
	/// ���`��Ԃ��s���A�J�n�l�ƏI���l�̊Ԃ̒l��Ԃ��܂��B
	/// </summary>
	/// <param name="start">��Ԃ̊J�n�l</param>
	/// <param name="end">��Ԃ̏I���l</param>
	/// <param name="t">��Ԃ̊����i0.0 �` 1.0�j</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	static float LerpFloat(float start, float end, float t)
	{
		// t ��͈� [0, 1] �ɃN�����v
		t = Clamp(t, 0.0f, 1.0f);

		// ���`��Ԃ̌v�Z
		return (1.0f - t) * start + t * end;
	}

	/// <summary>
	/// ���`��Ԃ��s���A2�̃x�N�g���Ԃ̒��ԃx�N�g����Ԃ��܂��B
	/// </summary>
	/// <param name="start">��Ԃ̊J�n�x�N�g��</param>
	/// <param name="end">��Ԃ̏I���x�N�g��</param>
	/// <param name="t">��Ԃ̊����i0.0 �` 1.0�j</param>
	/// <returns>��Ԃ��ꂽ�x�N�g��</returns>
	static DirectX::SimpleMath::Vector3 LerpVector(
		const DirectX::SimpleMath::Vector3& start,
		const DirectX::SimpleMath::Vector3& end,
		float t
	)
	{
		// t ��͈� [0, 1] �ɃN�����v
		t = Clamp(t, 0.0f, 1.0f);

		// �e��������`���
		return {
			(1.0f - t) * start.x + t * end.x,
			(1.0f - t) * start.y + t * end.y,
			(1.0f - t) * start.z + t * end.z
		};
	}

	/// <summary>
	/// �N�����v�֐� min max �̊Ԃɐ�������
	/// </summary>
	/// <typeparam name="T">�e���v���[�g</typeparam>
	/// <param name="value">��ƂȂ�l</param>
	/// <param name="min">�ŏ��l</param>
	/// <param name="max">�ő�l</param>
	/// <returns>����</returns>
	template <typename T>
	static T Clamp(const T& value, const T& min, const T& max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

	/// <summary>
	/// �p�x�� -�� �` �� �͈̔͂Ɏ��߂�֐�
	/// </summary>
	/// <param name="angle">�͈͂����߂����p�x�i���W�A���P�ʁj</param>
	/// <returns>-�� �` �� �͈̔͂Ɏ��߂�ꂽ�p�x�i���W�A���P�ʁj</returns>
	static float WrapAngle(float angle)
	{
		return DirectX::XM_2PI * (angle / DirectX::XM_2PI - floorf(angle / DirectX::XM_2PI));
	}

	/// <summary>
	/// ���ԓ��ɂ���̂��𔻒肷��
	/// </summary>
	/// <param name="first">�J�n����</param>
	/// <param name="now">����</param>
	/// <param name="end">�I������</param>
	/// <returns>����(bool)</returns>
	static bool InTime(float first, float now, float end)
	{
		return first < now && now <= end;
	}
};
