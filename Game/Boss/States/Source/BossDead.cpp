// -----------------------------------------------------
// ���O:	BossDead.cpp
// ���e:	�{�X�̎��S�X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Libraries//MyLib/EasingFunctions.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Cudgel/Cudgel.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Boss/States/Header/BossDead.h"
#include "Game/Camera/Camera.h"

// ---------------------------
// �R���X�g���N�^
// ---------------------------
BossDead::BossDead(Boss* boss)
	:
	m_boss(boss),
	m_angle{},
	m_totalSeconds{},
	m_tiltAngle{}
{
}

// ---------------------------
// �f�X�g���N�^
// ---------------------------
BossDead::~BossDead()
{
	Finalize();
}

// ---------------------------
// ����������
// ---------------------------
void BossDead::Initialize()
{
	// ���_�̎擾
	auto object = EventMessenger::ExecuteGetter(GetterList::GetCudgel);
	m_cudgel = object ? static_cast<Cudgel*>(object) : nullptr;
}

// ---------------------------
// �ύX����(in)
// ---------------------------
void BossDead::PreUpdate()
{
	// �J�����̃X�e�[�g��ύX
	CameraState camera = CameraState::Clear;
	EventMessenger::Execute(EventList::ChangeCamera,&camera);

	// �o�ߎ��Ԃ�������
	m_totalSeconds = 0.0f;
	// ��]���擾
	m_angle = m_boss->GetAngle();
	// ��ԊJ�n���̌X�����擾
	m_startTilt = m_boss->GetBodyTilt();
	// ��̃X�e�[�g��ύX
	CudgelState state = CudgelState::Idle;
	EventMessenger::Execute(EventList::ChangeBossFace, &state);

	// �S�Ă̓G��HP��0�ɂ���
	EventMessenger::Execute(EventList::DeleteAllGoblin, nullptr);

	// �{�X�Ɏ��S�������Ƃ�`����
	m_cudgel->BossDead();
}

// ---------------------------
// �X�V����
// ---------------------------
void BossDead::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ����Z
	m_totalSeconds += elapsedTime;

	// �P�b�ōs����ύX����
	if (m_totalSeconds >= TOTAL_TIME)
	{
		// �G��������
		m_boss->DeadAction();
		return;
	}
	// �A�j���[�V�����̍X�V
	UpdateAnimation();
}

// ---------------------------
// �A�j���[�V�����̍X�V
// ---------------------------
void BossDead::UpdateAnimation()
{
	// ���K���������Ԃ����߂�
	float t = m_totalSeconds / TOTAL_TIME;

	// �C�[�W���O�A�j���[�V������p���ČX�������߂�
	m_tiltAngle = m_startTilt + (MAX_TILT_ANGLE - m_startTilt) * Easing::easeOutBounce(t);

	// �X����ݒ�
	m_boss->SetBodyTilt(DirectX::XMConvertToRadians(m_tiltAngle));

	// �J������h�炷�^�C�~���O��}��
	if (m_tiltAngle <= CAMERA_SHAKE_TIMING)
	{
		float shakePower = CAMERA_SHAKE_POWER;
		// �J������h�炷
		EventMessenger::Execute(EventList::ShakeCamera, &shakePower);

		// �{�X�̈ʒu���擾
		DirectX::SimpleMath::Vector3 BossPos = m_boss->GetPosition();
		// �_�X�g�𐶐�
		EventMessenger::Execute(EventList::CreateBashDust, &BossPos);
		// �X�N�V�������
		EventMessenger::Execute(EventList::TakeCapture, nullptr);
	}
}

// ---------------------------
// �ύX����(out)
// ---------------------------
void BossDead::PostUpdate()
{
}

// ---------------------------
// �I������
// ---------------------------
void BossDead::Finalize()
{
}