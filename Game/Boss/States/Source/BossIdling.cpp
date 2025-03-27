// -----------------------------------------------------
// ���O:	BossIdling.cpp
// ���e:	�{�X�̑ҋ@�X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Boss/Boss.h"
#include "Game/Boss/States/Header/BossIdling.h"

// --------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// --------------------------------------
BossIdling::BossIdling(Boss* boss)
	:
	m_boss(boss),
	m_angle{},
	m_totalSeconds{}
{
}

// --------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------------
BossIdling::~BossIdling()
{
}

// --------------------------------------
/// <summary>
/// ����������
/// </summary>
// --------------------------------------
void BossIdling::Initialize()
{
	// �v���C���[�̎擾
	void* object = EventMessenger::ExecuteGetter(GetterList::GetPlayer);
	m_player = object ? static_cast<IObject*>(object) : nullptr;

	DirectX::SimpleMath::Vector3 pos = m_player->GetPosition();
}

// --------------------------------------
/// <summary>
/// �ݒ菈��(in)
/// </summary>
// --------------------------------------
void BossIdling::PreUpdate()
{
	// �o�ߎ��Ԃ�������
	m_totalSeconds = 0.0f;

	// ����̃X�e�[�g��ύX
	CudgelState state = CudgelState::Idle;
	EventMessenger::Execute(EventList::ChangeCudgelState, &state);

	// ���ύX
	FaceState face = FaceState::Idling;
	EventMessenger::Execute(EventList::ChangeBossFace, &face);

	// ��]���擾
	m_angle = m_boss->GetAngle();

}

// --------------------------------------
/// <summary>
/// �X�V����
/// </summary>
// --------------------------------------
void BossIdling::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ����Z
	m_totalSeconds += elapsedTime;
	// �A�j���[�V�����̍X�V
	UpdateAnimation();
	// ���̃X�e�[�g�ɑJ�ڂ��邩�����m
	CheckNextState();
}

// --------------------------------------
/// <summary>
/// �G�̋����X�V����
/// </summary>
// --------------------------------------
void BossIdling::UpdateAnimation()
{
	// �v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();
	Vector3 parentPos = m_boss->GetPosition();

	// �A���O�����v�Z
	float targetAngle = Math::CalculationAngle(parentPos, playerPos);
	// �p�x�����v�Z
	float angleDiff = targetAngle - m_angle;

	// �p�x����180�x�𒴂���ꍇ�A��]�����𔽓]
	if (angleDiff > DirectX::XM_PI)
	{
		angleDiff -= DirectX::XM_2PI;
	}
	else if (angleDiff < -DirectX::XM_PI)
	{
		angleDiff += DirectX::XM_2PI;
	}
	// ���`��ԂōŒZ�����ŉ�]
	m_angle += angleDiff * LERP_RATE;
	// �p�x��ݒ�
	m_boss->SetAngle(m_angle);
}

// --------------------------------------
/// <summary>
/// ���̃X�e�[�g�ɑJ�ڂ��邩�����m
/// </summary>
// --------------------------------------
void BossIdling::CheckNextState()
{
	// �v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();
	Vector3 parentPos = m_boss->GetPosition();

	// �P�b�ōs����ύX����
	if (m_totalSeconds >= TOTAL_TIME)
	{
		// �����_���ōs����ύX����
		int random = Math::RandomInt(0, TOTAL_RATE);
		// �v���C���[�Ƃ̋������v�Z
		float distance = Vector3::Distance(parentPos, playerPos);
		// ���̃{�X�̃X�e�[�g
		BossState state = BossState::Idling;

		// ���������̏ꍇ
		if (distance > FAR_DISTANCE)
		{
			// �Ǐ]
			if (random % 2 == 0) state = BossState::Approaching;
			// �_�b�V���U��
			else state = BossState::DashAttacking;
		}
		// �߂������̏ꍇ
		else
		{
			// �ガ����
			if (random <= SWEEPING_RATE) state = BossState::Sweeping;
			// �U��
			else if (random <= ATTACKING_RATE) state = BossState::Attacking;
			// �_�b�V���U��
			else if (random <= DASH_ATTACK_RATE) state = BossState::DashAttacking;
			// �������Ȃ�
			else if (random <= IDLING_RATE) state = BossState::Idling;
		}

		// �{�X�̃X�e�[�g��ύX
		EventMessenger::Execute(EventList::ChangeBossState, &state);
	}
}

// --------------------------------------
/// <summary>
/// �ݒ菈��(out)
/// </summary>
// --------------------------------------
void BossIdling::PostUpdate()
{
}

// --------------------------------------
/// <summary>
/// �I������
/// </summary>
// --------------------------------------
void BossIdling::Finalize()
{
}