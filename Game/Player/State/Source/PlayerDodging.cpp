// ----------------------------------------------
// ���O:	PlayerDodging.h
// ���e:	�v���C���[�̉�����
// �쐬:	�r�c
// ----------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Libraries/MyLib/Math.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/Header/PlayerDodging.h"

// ---------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�e�̃|�C���^</param>
// ---------------------------------------
PlayerDodging::PlayerDodging(Player* player)
	:
	m_player(player),
	m_totalSeconds{},
	m_finishTime{},
	m_rollingValue{}
{
}

// ---------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------
PlayerDodging::~PlayerDodging()
{
}

// ---------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------
void PlayerDodging::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// ���O�X�V����
/// </summary>
// ---------------------------------------------
void PlayerDodging::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;
	// �ړ������̐ݒ�
	m_velocity = DirectX::SimpleMath::Vector3::Forward * DODGING_SPEED;
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void PlayerDodging::Update(const float& elapsedTime)
{
	float t = elapsedTime;
	// �o�ߎ��Ԃ����Z
	m_totalSeconds += t;
	// �A�j���[�V�����̍X�V
	UpdateAnimation(m_totalSeconds);
	// �X�e�[�g�J�n���玞�Ԃ��v���A��莞�Ԃŕʂ�State�֑J�ڂ�����
	m_player->TimeComparison(m_totalSeconds, ANIMATION_END_TIME, PlayerState::Idling, elapsedTime);
}

// ---------------------------------------------
/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
/// <param name="totalTime">�o�ߎ���</param>
// ---------------------------------------------
void PlayerDodging::UpdateAnimation(float totalTime)
{
	// �v���C���[�̍��W���擾
	m_position = m_player->GetPosition();

	// ���[�����O�A�j���[�V����
	RollingAnimation(totalTime);
	// �L�����N�^�[�̈ړ��𒲐�
	AdjustCharacterTransition(totalTime);
}

// -----------------------------------------
/// <summary>
/// ���[�����O�A�j���[�V����
/// </summary>
/// <param name="totalTime">�o�ߎ���</param>
// -----------------------------------------
void PlayerDodging::RollingAnimation(float totalTime)
{
	// �C�[�W���O�̗v�f��
	float value;

	// ��]�����̕���
	if (totalTime <= SPIN_TIME)
	{
		value = Easing::easeInOutQuad(totalTime / SPIN_TIME);

		m_rollingValue.x = DirectX::XMConvertToRadians(value * ROLLING_ROT + ROLLING_REST_ROT);
	}
	// ���[�����O��̍d������
	else if (totalTime <= SPIN_REST_TIME)
	{
		// SPIN_TIME ���z�������̎��ԂŊ������v�Z
		value = (totalTime - SPIN_TIME) / (SPIN_REST_TIME - SPIN_TIME);
		float easeValue = Easing::easeOutBack(value);

		float rot = ROLLING_REST_ROT - (easeValue * ROLLING_REST_ROT);

		// ��]�����W�A���ɕϊ�
		m_rollingValue.x = DirectX::XMConvertToRadians(rot);
	}
	// ��]��K�p
	m_player->SetAnimationRotate(m_rollingValue);
}

// -----------------------------------------
/// <summary>
/// �v���C���[�̈ړ��𒲐�
/// </summary>
/// <param name="totalTime">�o�ߎ���</param>
// -----------------------------------------
void PlayerDodging::AdjustCharacterTransition(float totalTime)
{
	// �C�[�W���O�̗v�f��
	float value = 0.0f;

	// ���[�����O�����̕���
	if (totalTime <= ANIMATION_TIME)
	{
		// �C�[�W���O���|���邽�߂̎���
		value = Easing::easeOutCubic(totalTime / ANIMATION_TIME);
		m_position.y = value * UP_VALUE;
	}
	// ���[�����O��̍d������
	else if (totalTime - ANIMATION_TIME <= DODGING_RECOVERY_TIME - ANIMATION_TIME)
	{
		// �㏈�����s��
		value = Easing::easeInOutQuad((totalTime - ANIMATION_TIME) / (DODGING_RECOVERY_TIME - ANIMATION_TIME));
		m_position.y = UP_VALUE - (value * UP_VALUE);
	}

	// �v���C���[�̈ړ���K�p
	ApplyPlayerMovement(m_position);
}

// -----------------------------------------
/// <summary>
/// �v���C���[�̈ړ���K�p
/// </summary>
/// <param name="parentPos">�v���C���[�̍��W</param>
// -----------------------------------------
void PlayerDodging::ApplyPlayerMovement(DirectX::SimpleMath::Vector3& parentPos)
{
	// �v���C���[�̉�]���擾
	Matrix angle = Matrix::CreateRotationY(-m_player->GetAngle());
	// ���x��ݒ�
	m_velocity *= DODGE_FUNCTION;
	// �[����������΂��B
	m_velocity = Math::truncate_vector(m_velocity, TRUNCATION_DIGIT);
	// �ړ��ʂ����W�ɔ��f�����Ȃ�����W���ړ�������B
	parentPos += Vector3::Transform(m_velocity, angle);
	// �v���C���[�̍��W���X�V
	m_player->SetPosition(parentPos);
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꂽ�u��)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ----------------------------------------------
void PlayerDodging::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꑱ���Ă����)
/// </summary>
/// <param name="key">������Ă���L�[</param>
// ---------------------------------------------
void PlayerDodging::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// ����X�V����
/// </summary>
// ---------------------------------------------
void PlayerDodging::PostUpdate()
{
	m_position.y = 0.0f;
	// �v���C���[�̍��W���X�V
	m_player->SetPosition(m_position);
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void PlayerDodging::Finalize()
{
}