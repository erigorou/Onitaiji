// ---------------------------------------------------------
//
// ���O:	EnemyTitleMoving.cpp
// ���e:	�G�̍U�����
//			�X�e�[�g�p�^�[���Ŏ���
// �쐬;	�r�c����
//
// ---------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/Messenger/EventMessenger.h"
#include "Libraries/MyLib/Math.h"
#include "TitleEnemy.h"
#include "EnemyTitleMoving.h"

// ------------------------------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="enemy">�G�̃|�C���^</param>
// ------------------------------------------------------------------------------
EnemyTitleMoving::EnemyTitleMoving(TitleEnemy* enemy)
	: 
	m_enemy(enemy),
	m_position{},
	m_velocity{},
	m_angle{},
	m_worldMat(DirectX::SimpleMath::Matrix::Identity),
	m_totalSeconds{},
	m_isJump(false),
	m_canShake(false),
	m_shakePower(SHAKE_POWER)
{
}

// ------------------------------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ------------------------------------------------------------------------------
EnemyTitleMoving::~EnemyTitleMoving()
{
}

// ------------------------------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ------------------------------------------------------------------------------
void EnemyTitleMoving::Initialize()
{
	// ���x��ݒ�i�O�ɂ��������Ȃ��j
	m_velocity = DirectX::SimpleMath::Vector3::Forward;
}

// ------------------------------------------------------------------------------
/// <summary>
/// ���O�X�V����
/// </summary>
// ------------------------------------------------------------------------------
void EnemyTitleMoving::PreUpdate()
{
	// �o�ߎ��Ԃ�������
	m_totalSeconds = 0.0f;
	// ���W��������
	m_position = Vector3::Zero;
}

// ------------------------------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ------------------------------------------------------------------------------
void EnemyTitleMoving::Update(const float& elapsedTime)
{
	// ���v�̎��Ԃ��v�Z����
	m_totalSeconds += elapsedTime;

	// �T�C���g�̌v�Z(�㉺�ړ�)
	m_position.y = Math::CalculatingSinWave(m_totalSeconds, AMPLITUDE, FREQUENCY);

	// ��Βl����邱�ƂŃW�����v���Ă���悤�ȋ���������
	m_position.y = fabsf(m_position.y);

	// �ړ��ŃJ������h�炷
	if (m_position.y <= MINIMAL)
	{
		// �J������h�炷
		EventMessenger::Execute(EventList::ShakeCamera, &m_shakePower);

		// �y���𔭐�������
		EventMessenger::Execute(EventList::CreateBashDust, &m_position);

		// �X�e�[�g��ύX����
		m_enemy->ChangeState(TitleEnemy::BossState::IDLING);
	}

	// ��]�p��ݒ肷��
	m_enemy->SetAngle(m_angle);
	// ���W��ݒ肷��
	m_enemy->SetPosition(m_position);
}

// ------------------------------------------------------------------------------
/// <summary>
/// ����X�V����
/// </summary>
// ------------------------------------------------------------------------------
void EnemyTitleMoving::PostUpdate()
{
	// ���[���h�s���S�̂ɐݒ肷��
	m_enemy->SetWorldMatrix(m_worldMat);
	// �G�̈ʒu��0�ŌŒ肷��
	m_position.y = 0.0f;
	m_enemy->SetPosition(m_position);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ------------------------------------------------------------------------------
void EnemyTitleMoving::Finalize()
{
}
