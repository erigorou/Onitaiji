// -----------------------------------------------------
// ���O:	BossDashAttacking.cpp
// ���e:	�{�X�̓ːi�X�e�[�g���`
// �쐬:	�r�c����
// -----------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Libraries/MyLib/Math.h"
#include "Libraries//MyLib/EasingFunctions.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Cudgel/Cudgel.h"
#include "../../States/Header/BossDashAttacking.h"

// --------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="boss">�{�X�̃|�C���^</param>
// --------------------------------------
BossDashAttacking::BossDashAttacking(Boss* boss)
	:
	m_boss(boss),
	m_angle{},
	m_bodyTilt{},
	m_totalSeconds{}
{
}

// --------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------------
BossDashAttacking::~BossDashAttacking()
{
}

// --------------------------------------
/// <summary>
/// ����������
/// </summary>
// --------------------------------------
void BossDashAttacking::Initialize()
{
	// �v���C���[�̎擾
	void* player = EventMessenger::ExecuteGetter(GetterList::GetPlayer);
	m_player = player ? static_cast<IObject*>(player) : nullptr;

	// ���_
	void* cudgel = EventMessenger::ExecuteGetter(GetterList::GetCudgel);
	m_cudgel = cudgel ? static_cast<Cudgel*>(cudgel) : nullptr;
}

// --------------------------------------
/// <summary>
/// ���O�X�V����
/// </summary>
// --------------------------------------
void BossDashAttacking::PreUpdate()
{
	// �o�ߎ��Ԃ�������
	m_totalSeconds = 0.0f;

	// ��̃X�e�[�g��ύX
	FaceState face = FaceState::Attacking;
	EventMessenger::Execute(EventList::ChangeBossFace, &face);

	// �ŏ��͍U�����ł͂Ȃ�
	m_isAttacking = false;

	// ����̃X�e�[�g��ύX
	CudgelState state = CudgelState::Idle;
	EventMessenger::Execute(EventList::ChangeCudgelState, &state);
}

// --------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// --------------------------------------
void BossDashAttacking::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ��X�V
	m_elapsedTime = elapsedTime;
	m_totalSeconds += m_elapsedTime;

	// �G�̋������X�V����
	UpdateAction();

	// �ҋ@��ԂɑJ��
	if (m_totalSeconds >= TOTAL_TIME)
	{
		// �X�e�[�g��ύX�i�ҋ@��ԁj
		BossState state = BossState::Idling;
		EventMessenger::Execute(EventList::ChangeBossState, &state);
	}
}

// --------------------------------------
/// <summary>
/// �G�̋����X�V����
/// </summary>
// --------------------------------------
void BossDashAttacking::UpdateAction()
{
	// ���߃��[�V�����̎�
	if (m_totalSeconds <= CHARGE_TIME)	ChargeAction();	// ����
	else if (m_totalSeconds <= DASH_TIME)	DashAction();	// �_�b�V��
	else if (m_totalSeconds <= WAIT_TIME)	WaitAction();	// �ҋ@
	else if (m_totalSeconds <= RETURN_TIME)	ReturnAction();	// ���ɖ߂�
}

// --------------------------------------
/// <summary>
/// ����
/// </summary>
// --------------------------------------
void BossDashAttacking::ChargeAction()
{
	// �v���C���[�ɍU�����󂯂���t���O�𖳌���
	EventMessenger::Execute(EventList::PlayerCanDamageBoss, &m_isAttacking);

	// �v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();
	// �G�̍��W���擾
	Vector3 parentPos = m_boss->GetPosition();
	// �G���猩���v���C���[�̈ʒu��ݒ肷��
	m_angle = Math::CalculationAngle(parentPos, playerPos);
	m_rotMatrix = DirectX::SimpleMath::Matrix::CreateRotationY(-m_angle);
	m_boss->SetAngle(m_angle);

	// �C�[�W���O�p�̕ϐ�
	float t = m_totalSeconds / CHARGE_TIME;
	// �̂̌X���̊p�x�ݒ�
	m_bodyTilt = DirectX::XMConvertToRadians(-TILT_ANGLE * Easing::easeOutBack(t));
	m_boss->SetBodyTilt(m_bodyTilt);
}

// --------------------------------------
/// <summary>
/// �_�b�V��
/// </summary>
// --------------------------------------
void BossDashAttacking::DashAction()
{
	// �A�^�b�N��
	m_isAttacking = true;

	// �v���C���[�ɍU�����󂯂���t���O��L����
	EventMessenger::Execute(EventList::PlayerCanDamageBoss, &m_isAttacking);

	// ���݂̎��ԂɊ�Â��ăT�C���g�ŉ����x���v�Z
	float easing = (m_totalSeconds - CHARGE_TIME) / (DASH_TIME - CHARGE_TIME);

	// ���W�̍X�V
	float accelerationFactor = sin(static_cast<float>(easing * M_PI));

	// �G�̌����Ɋ�Â��đO�������v�Z
	Vector3 position = m_boss->GetPosition();
	m_velocity = Vector3(0, 0, -MAX_SPEED * accelerationFactor);
	position += Vector3::Transform(m_velocity, m_rotMatrix) * m_elapsedTime;

	// �T�C���g�ŏ㉺�^��
	float y = fabsf(sin(easing * SIN_SPEED)) * accelerationFactor;
	position.y = y;

	// �v�Z�������W��{�̂ɐݒ肷��
	m_boss->SetPosition(position);

	// �v���C���[���X����
	m_bodyTilt = DirectX::XMConvertToRadians(-TILT_ANGLE + TILT_ANGLE_DASH * Easing::easeOutBack(easing));
	m_boss->SetBodyTilt(m_bodyTilt);
}

// --------------------------------------
/// <summary>
/// �ҋ@
/// </summary>
// --------------------------------------
void BossDashAttacking::WaitAction()
{
	// �A�^�b�N�I���
	m_isAttacking = false;

	// �v���C���[�ɍU�����󂯂���t���O��L����
	EventMessenger::Execute(EventList::PlayerCanDamageBoss, &m_isAttacking);

	// �C�[�W���O�Ɏg�p����b�����v�Z�i�b����Normalize)
	float easing = (m_totalSeconds - DASH_TIME) / (WAIT_TIME - DASH_TIME);

	// �v���C���[���X����
	m_bodyTilt = DirectX::XMConvertToRadians(TILT_ANGLE - TILT_ANGLE * Easing::easeOutBounce(easing));
	m_boss->SetBodyTilt(m_bodyTilt);
}

// --------------------------------------
/// <summary>
/// ���ɖ߂�
/// </summary>
// --------------------------------------
void BossDashAttacking::ReturnAction()
{
	// ���Ԃ̐��K��
	float easing = (m_totalSeconds - WAIT_TIME) / (RETURN_TIME - WAIT_TIME);

	// �v���C���[�̍��W���擾
	Vector3 playerPos = m_player->GetPosition();
	// �G�̍��W���擾
	Vector3 parentPos = m_boss->GetPosition();
	// �G���猩���v���C���[�̈ʒu��ݒ肷��
	float angle = Math::CalculationAngle(parentPos, playerPos);

	m_angle = Math::LerpFloat(m_angle, angle, easing);

	m_rotMatrix = DirectX::SimpleMath::Matrix::CreateRotationY(-m_angle);
	m_boss->SetAngle(m_angle);
}

// --------------------------------------
/// <summary>
/// ����X�V����
/// </summary>
// --------------------------------------
void BossDashAttacking::PostUpdate()
{
	// ����̃X�e�[�g��ύX
	CudgelState state = CudgelState::Idle;
	EventMessenger::Execute(EventList::ChangeCudgelState, &state);

	// ��̃X�e�[�g��ύX
	FaceState face = FaceState::Idling;
	EventMessenger::Execute(EventList::ChangeBossFace, &face);
}

// --------------------------------------
/// <summary>
/// �I������
/// </summary>
// --------------------------------------
void BossDashAttacking::Finalize()
{
}