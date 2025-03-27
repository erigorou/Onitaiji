// --------------------------------------------------
// ���O:	HitStop.cpp
// ���e:	�q�b�g�X�g�b�v���s�N���X
// �쐬:	�r�c����
// --------------------------------------------------

#include "pch.h"
#include "HitStop.h"
#include "Libraries/MyLib/EasingFunctions.h"

std::unique_ptr<HitStop> HitStop::s_hitStop = nullptr;


// ---------------------------------------------
/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>�|�C���^</returns>
// ---------------------------------------------
HitStop* const HitStop::GetInstance()
{
	// �C���X�^���X����������Ă��Ȃ��ꍇ
	if (s_hitStop == nullptr)
	{
		//�@��������
		s_hitStop.reset(new HitStop);
	}
	// �C���X�^���X��Ԃ�
	return s_hitStop.get();
}

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------
HitStop::HitStop()
	: m_isActive(false)
	, m_smoothDeltaTime(0.f)
	, m_totalSeconds(0.f)
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
HitStop::~HitStop()
{
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void HitStop::Update(float elapsedTime)
{
	// �o�ߎ��Ԃ�o�^
	m_smoothDeltaTime = elapsedTime;
	// �����Ȃ��ꍇ�I��
	if (!m_isActive) return;
	// �q�b�g�X�g�b�v���̌v�Z���s��
	CalculateSmoothDeltaTime(elapsedTime);
}

// ---------------------------------------------
/// <summary>
/// �q�b�g�X�g�b�v�̌v�Z�i�c�莞�ԁj
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void HitStop::CalculateSmoothDeltaTime(float elapsedTime)
{
	// �o�ߎ��Ԃ̋L�^
	m_totalSeconds += elapsedTime;
	// �q�b�g�X�g�b�v�����̔���
	m_isActive = (m_totalSeconds < HITSTOP_TIME);

	if (m_totalSeconds < DELAY) return;

	// �C�[�W���O�p�̎��Ԃ��v�Z
	float t = Easing::easeInQuint((m_totalSeconds - DELAY) / (HITSTOP_TIME - DELAY));

	// �q�b�g�X�g�b�v�̏�Ԃɉ����Čo�ߎ��Ԃ�ݒ�@TRUE : FALSE
	m_smoothDeltaTime = m_isActive ? elapsedTime * t : (m_totalSeconds = 0.0f);
}