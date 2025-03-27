// --------------------------------------------------
//���O:	GoblinIdling.cpp
//���e:	�S�u�����̑ҋ@���
//�쐬:	�r�c����
// --------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "../Header/GoblinIdling.h"
#include "../../Goblin.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Messenger/EventMessenger.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goblin">�S�u�����̃|�C���^</param>
// ---------------------------------------------
GoblinIdling::GoblinIdling(Goblin* goblin)
	: 
	m_goblin{ goblin },
	m_TotalTime{}
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
GoblinIdling::~GoblinIdling()
{
}

// ---------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------
void GoblinIdling::Initialize()
{
	// �����_���ɃN�[���^�C����ݒ肷��
	m_coolTime = INIT_COOLTIME;
}

// ---------------------------------------------
/// <summary>
/// �����������iin�����j
/// </summary>
// ---------------------------------------------
void GoblinIdling::PreUpdate()
{
	m_goblin->SetIsAttacking(false);
	m_TotalTime = 0.0f;

	// �����_���ɃN�[���^�C����ݒ肷��
	m_coolTime = Math::RandomFloat(MIN_COOLTIME, MAX_COOLTIME);
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void GoblinIdling::Update(const float& elapsedTime)
{
	// �v���C���[�̕���������
	SearchPlayer();

	// ���Ԃ����Z����
	m_TotalTime += elapsedTime;

	// �U���X�e�[�g�ɑJ�ڂ���
	if (m_TotalTime > m_coolTime)
	{
		m_goblin->ChangeState(GoblinState::ATTACKING);
	}
}

// ---------------------------------------------
/// <summary>
/// �����������iout�����j
/// </summary>
// ---------------------------------------------
void GoblinIdling::PostUpdate()
{
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void GoblinIdling::Finalize()
{
}


// ---------------------------------------------
/// <summary>
/// �v���C���[�̒T�������i�S�u�����̉�]��Lerp��ǉ��j
/// </summary>
// ---------------------------------------------
void GoblinIdling::SearchPlayer()
{
	// �v���C���[���擾
	auto object = EventMessenger::ExecuteGetter(GetterList::GetPlayer);
	auto player = static_cast<IObject*>(object);
	// �v���C���[�̈ʒu���擾
	DirectX::SimpleMath::Vector3 playerPos = player->GetPosition();
	// ���S�̈ʒu���擾
	m_position = m_goblin->GetPosition();

	// �v���C���[�̕������v�Z
	float targetAngle = Math::CalculationAngle(playerPos, m_position);

	// ���݂̉�]�p�x���Ԃ��ĖڕW�p�x�ɏ��X�ɋ߂Â���
	m_angle = Math::LerpFloat(m_angle, targetAngle, 0.1f); // 0.1f�͕�ԗ��i�����\�j

	// ��]�s����X�V
	m_rotMatrix = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);
	m_goblin->SetAngle(-m_angle);
}
