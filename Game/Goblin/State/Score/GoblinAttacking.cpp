// --------------------------------------------------
//���O:	GoblinAttacking.cpp
//���e:	�S�u�����̍U�����
//�쐬:	�r�c����
// --------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "../Header/GoblinAttacking.h"
#include "../../Goblin.h"
#include "Game/Messenger/EventMessenger.h"
#include "Libraries/MyLib/Math.h"
#include "Libraries/MyLib/EasingFunctions.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goblin">�S�u�����̃|�C���^</param>
// ---------------------------------------------
GoblinAttacking::GoblinAttacking(Goblin* goblin)
	: m_goblin{ goblin }
	, m_totalTime{}
	, m_angle{}
	, m_rotMatrix{ DirectX::SimpleMath::Matrix::Identity }
	, m_moveValue{}
	, m_position{}
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
GoblinAttacking::~GoblinAttacking()
{
}

// ---------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// ���O�X�V����
/// </summary>
// ---------------------------------------------
void GoblinAttacking::PreUpdate()
{
	// �v���C���[�̕���������
	SearchPlayer();
	// �o�ߎ��Ԃ����Z�b�g����
	m_totalTime = 0.0f;
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void GoblinAttacking::Update(const float& elapsedTime)
{
	// ���Ԃ����Z����
	m_totalTime += elapsedTime;

	// �A�j���[�V�����̍X�V
	UpdateAnimation();

	if (m_totalTime > STATE_TIME)
	{
		m_goblin->ChangeState(GoblinState::IDLING);
	}
}

// ---------------------------------------------
/// <summary>
/// ���߃A�j���[�V��������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::UpdateAnimation()
{
	// �U�����t���O�����낷
	m_goblin->SetIsAttacking(false);

	ChargeAnimation();
	AttackAnimation();
	ReturnAnimation();
}

// ---------------------------------------------
/// <summary>
/// �U���A�j���[�V��������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::ChargeAnimation()
{
	// ���ԓ��o�Ȃ��ꍇ�͏I��
	if (!Math::InTime(0, m_totalTime, CHARGE_TIME)) return;

	// �b���𐳋K��
	float t = m_totalTime / CHARGE_TIME;

	// �傫��y��sin�g�ŕύX
	float sin = Math::NormalizeSin(t);
	float sizeY = 1.0f - (sin * MAX_MINUS_SIZE);

	// �傫����ݒ�
	m_goblin->SetScale(DirectX::SimpleMath::Vector3(1.0f, sizeY, 1.0f));

	// �v���C���[�̕���������
	SearchPlayer();
}

// ---------------------------------------------
/// <summary>
/// �U���A�j���[�V��������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::AttackAnimation()
{
	bool flag = false;
	EventMessenger::Execute(EventList::PlayerCanDamageGoblin, &flag);

	// �U�����Ԃ��߂�����I��
	if (!Math::InTime(CHARGE_TIME, m_totalTime, ATTACK_TIME)) return;

	flag = true;
	EventMessenger::Execute(EventList::PlayerCanDamageGoblin, &flag);

	// �b���𐳋K��
	float t = (m_totalTime - CHARGE_TIME) / (ATTACK_TIME - CHARGE_TIME);

	// sin�ƃC�[�W���O���|���ď㉺�ړ�������
	float sin = Math::NormalizeSin(t);
	float easingUD = std::fabs(1 - Easing::easeOutBack(t));
	float posY = sin * easingUD * MAX_Y_POS;

	// �����̈ړ�
	float easingLR = Easing::easeOutCubic(t);

	// �ړ��ʒu��ݒ�
	m_movePosition = m_position + m_moveValue * easingLR;
	m_movePosition.y = posY;

	// �ړ��ʂ�ݒ�
	m_goblin->SetPosition(m_movePosition);
}

// ---------------------------------------------
/// <summary>
/// ���ɖ߂�A�j���[�V��������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::ReturnAnimation()
{
	if (!Math::InTime(ATTACK_TIME, m_totalTime, RETURN_TIME))return;
}

// ---------------------------------------------
/// <summary>
/// ����X�V����
/// </summary>
// ---------------------------------------------
void GoblinAttacking::PostUpdate()
{
	m_goblin->SetIsAttacking(false);
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::Finalize()
{
}

// ---------------------------------------------
/// <summary>
/// �v���C���[�̒T������
/// </summary>
// ---------------------------------------------
void GoblinAttacking::SearchPlayer()
{
	// �v���C���[���擾
	auto object = EventMessenger::ExecuteGetter(GetterList::GetPlayer);
	auto player = static_cast<IObject*>(object);
	// �v���C���[�̈ʒu���擾
	DirectX::SimpleMath::Vector3 playerPos = player->GetPosition();
	// ���S�̈ʒu���擾
	m_position = m_goblin->GetPosition();

	// �v���C���[�̈ʒu��T��
	m_angle = Math::CalculationAngle(playerPos, m_position);
	m_rotMatrix = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);
	m_goblin->SetAngle(-m_angle);

	// �S�u�����ƃv���C���[�̋������擾
	m_moveValue = playerPos - m_position;
}