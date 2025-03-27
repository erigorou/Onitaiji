// ---------------------------------------------------------
//
// ���O:	EnemyTitleIdling.cpp
// ���e:	�G�̑ҋ@���
//			�X�e�[�g�p�^�[���Ŏ���
// �쐬;	�r�c����
//
// ---------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "TitleEnemy.h"
#include "EnemyTitleIdling.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
EnemyTitleIdling::EnemyTitleIdling(TitleEnemy* enemy)
	: 
	m_enemy{ enemy },
	m_position{},
	m_velocity{},
	m_angle{},
	m_worldMat(DirectX::SimpleMath::Matrix::Identity),
	m_totalSeconds{}
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
EnemyTitleIdling::~EnemyTitleIdling()
{
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------
void EnemyTitleIdling::Initialize()
{
	// ���x��ݒ�i�O�ɂ��������Ȃ��j
	m_velocity = DirectX::SimpleMath::Vector3::Forward;
}

// ---------------------------------------------------------
/// <summary>
/// ���O�X�V����
/// </summary>
// ---------------------------------------------------------
void EnemyTitleIdling::PreUpdate()
{
	using namespace DirectX::SimpleMath;

	// �o�ߎ��Ԃ�������
	m_totalSeconds = 0.0f;

	m_position = Vector3::Zero;
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
// ---------------------------------------------------------
void EnemyTitleIdling::Update(const float& elapsedTime)
{
	// ���v�̎��Ԃ��v�Z����
	m_totalSeconds += elapsedTime;
	// ��莞�Ԍo�ߌ�A�X�e�[�g��ύX
	if (m_totalSeconds > TitleEnemy::COOL_TIME){
		m_enemy->ChangeState(TitleEnemy::BossState::MOVING);
	}
	// ��]�s��̍쐬
	DirectX::SimpleMath::Matrix angleMat = 
		// �X�P�[���s�� * ��]�s��
		DirectX::SimpleMath::Matrix::CreateScale(TitleEnemy::TITLE_ENEMY_SCALE) * 
		DirectX::SimpleMath::Matrix::CreateRotationY(-m_angle);

	// ��]�p��ݒ肷��
	m_enemy->SetAngle(m_angle);
	// ���W��ݒ肷��
	m_enemy->SetPosition(m_position);
}

// ---------------------------------------------------------
/// <summary>
/// ����X�V����
/// </summary>
// ---------------------------------------------------------
void EnemyTitleIdling::PostUpdate()
{
	// ���[���h�s���S�̂ɐݒ肷��
	m_enemy->SetWorldMatrix(m_worldMat);
	// �G�̈ʒu��0�ŌŒ肷��
	m_position.y = 0.0f;
	m_enemy->SetPosition(m_position);
}

// ---------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------------------
void EnemyTitleIdling::Finalize()
{
}