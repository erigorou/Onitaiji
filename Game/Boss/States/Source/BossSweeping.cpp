// -----------------------------------------------------
// ���O:	BossSweeping.cpp
// ���e:	�{�X�̓ガ�����U���X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Boss/Boss.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Boss/States/Header/BossSweeping.h"

// ----------------------------------
// �R���X�g���N�^
// ----------------------------------
BossSweeping::BossSweeping(Boss* Boss)
	:
	m_angle{},
	m_boss(Boss),
	m_totalSeconds{}
{
}

// ----------------------------------
// �f�X�g���N�^
// ----------------------------------
BossSweeping::~BossSweeping()
{
}

// ----------------------------------
// ����������
// ----------------------------------
void BossSweeping::Initialize()
{
}

// ----------------------------------
// ���O�X�V����
// ----------------------------------
void BossSweeping::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;
	m_angle = DirectX::XMConvertToDegrees(m_boss->GetAngle());

	// ����̃X�e�[�g��ύX
	CudgelState state = CudgelState::Sweep;
	EventMessenger::Execute(EventList::ChangeCudgelState, &state);

	// ��̃X�e�[�g��ύX
	FaceState face = FaceState::Attacking;
	EventMessenger::Execute(EventList::ChangeBossFace, &face);
}

// ----------------------------------
// �X�V����
// ----------------------------------
void BossSweeping::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ̉��Z
	m_totalSeconds += elapsedTime;
	// �A�j���[�V�����̍X�V
	UpdateAnimation();
	// �p�x�̍X�V
	m_boss->SetAngle(DirectX::XMConvertToRadians(m_targetAngle));
}

// ----------------------------------
// �A�j���[�V�����̍X�V
// ----------------------------------
void BossSweeping::UpdateAnimation()
{
	// ���߃��[�V���������s
	if (Math::InTime(0.0f, m_totalSeconds, CHARGE_TIME))
		UpdateChargeMotion();

	// ���ԓ��ɂ���Ȃ�ガ�������[�V���������s
	else if (Math::InTime(WINDUP_TIME, m_totalSeconds, ATTACK_TIME))
		UpdateSweepMotion();

	if (m_totalSeconds > END_TIME)
	{
		// �X�e�[�g��ύX�i�ҋ@��ԁj
		BossState state = BossState::Idling;
		EventMessenger::Execute(EventList::ChangeBossState, &state);
	}
}

// ----------------------------------
// ���߃��[�V�����̍X�V
// ----------------------------------
void BossSweeping::UpdateChargeMotion()
{
	// ���߂鎞�Ԃɑ΂���o�ߎ��Ԃ̊���
	float easing = m_totalSeconds / CHARGE_TIME;
	// �C�[�W���O��p�����p�x�̌v�Z
	m_targetAngle = m_angle - ROTATE_ANGLE * Easing::easeOutCirc(easing);
}

// ----------------------------------
// �ガ�������[�V�����̍X�V
// ----------------------------------
void BossSweeping::UpdateSweepMotion()
{
	// �ガ�������[�V�����̌o�ߎ��Ԃɑ΂��銄��
	float easing = (m_totalSeconds - WINDUP_TIME) / (ATTACK_TIME - WINDUP_TIME);
	// �C�[�W���O��p�����p�x�̌v�Z
	m_targetAngle = m_angle - ROTATE_ANGLE + ROTATE_ANGLE * Easing::easeOutBack(easing);
}

// ----------------------------------
// ����X�V����
// ----------------------------------
void BossSweeping::PostUpdate()
{
	// ����̃X�e�[�g��ύX
	CudgelState state = CudgelState::Idle;
	EventMessenger::Execute(EventList::ChangeCudgelState, &state);

	// ��̃X�e�[�g��ύX
	FaceState face = FaceState::Idling;
	EventMessenger::Execute(EventList::ChangeBossFace, &face);
}

// ----------------------------------
// �I������
// ----------------------------------
void BossSweeping::Finalize()
{
}