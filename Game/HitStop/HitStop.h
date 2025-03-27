// --------------------------------------------------
// ���O:	HitStop.cpp
// ���e:	�q�b�g�X�g�b�v���s�N���X
// �쐬:	�r�c����
// --------------------------------------------------
#pragma once
#ifndef HITSTOP_H
#define HITSTOP_H
// �C���N���[�h
#include "pch.h"

/// <summary>
/// �΂��ƃX�g�b�v�N���X
/// </summary>
class HitStop
{

	// ------------------------------
	// �萔
	// ------------------------------

public:
	// �q�b�g�X�g�b�v�̒x������
	static constexpr float DELAY = 0.05f;
	// �q�b�g�X�g�b�v����
	static constexpr float HITSTOP_TIME = DELAY + 0.2f;


	// ------------------------------
	// �A�N�Z�T
	// ------------------------------
	// �C���X�^���X�̎擾
	static HitStop* const GetInstance();
	// �q�b�g�X�g�b�v���L����
	bool IsActive() const { return m_isActive; }
	// �q�b�g�X�g�b�v��L���ɂ���
	void SetActive() { m_isActive = true; }
	// �q�b�g�X�g�b�v���v�Z�������Ԃ��擾
	inline float GetSmoothDeltaTime() const { return m_smoothDeltaTime; }

	// ------------------------------
	// �����o�֐�(���J)
	// ------------------------------
public:
	// �R���X�g���N�^
	HitStop();
	// �f�X�g���N�^
	~HitStop();
	// �X�V����
	void Update(float elapsedTime);

	// ------------------------------
	// �����o�֐�(����J)
	// ------------------------------
private:
	// �q�b�g�X�g�b�v�̌v�Z�i�c�莞�ԁj
	void CalculateSmoothDeltaTime(float elapsedTime);

	// ------------------------------
	// �����o�ϐ�
	// ------------------------------
private:
	// �C���X�^���X
	static std::unique_ptr<HitStop> s_hitStop;
	// �q�b�g�X�g�b�v���L����
	bool m_isActive;
	// �q�b�g�X�g�b�v�֘A�̎���
	float m_smoothDeltaTime;
	// �o�ߎ���
	float m_totalSeconds;
};

#endif // !HITSTOP_H