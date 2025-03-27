// ----------------------------------------------
// ���O:	PlayerAttacking2.h
// ���e:	�v���C���[�̍U�����
// �쐬:	�r�c
// ----------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Game/Sound/Sound.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/Header/PlayerAttacking2.h"

// ---------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�e�̃|�C���^</param>
// ---------------------------------------
PlayerAttacking2::PlayerAttacking2(Player* player)
	:
	m_player{ player },
	m_totalSeconds{}
{
}

// ---------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------
PlayerAttacking2::~PlayerAttacking2()
{
}

// ---------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------
void PlayerAttacking2::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�ύX����(in)
/// </summary>
// ---------------------------------------------
void PlayerAttacking2::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;

	// ������U����ԂɕύX
	SwordState state = SwordState::Attack2;
	EventMessenger::Execute(EventList::ChangeSwordState, &state);

	// ���ʉ��̍Đ�
	Sound::PlaySE(Sound::SE_TYPE::PLAYER_ATTACK);
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void PlayerAttacking2::Update(const float& elapsedTime)
{
	m_totalSeconds += elapsedTime;

	UpdateAnimation();

	// ���Ԃ��v�����A��莞�Ԍo�߂ŃX�e�[�g��J��
	m_player->TimeComparison(m_totalSeconds, Player::APPLIED_ATTACK_TIME, PlayerState::Idling, elapsedTime);
}

// ---------------------------------------------
/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
// ---------------------------------------------
void PlayerAttacking2::UpdateAnimation()
{
	if (m_totalSeconds > Player::NORMAL_ATTACK_TIME) return;

	// �A�j���[�V�����̉�]�ʂ��擾
	DirectX::SimpleMath::Vector3 currentAnimPos = DirectX::SimpleMath::Vector3::Zero;
	// �v���C���[�̉�]�ʂ��擾
	float currentAngle = m_player->GetAngle();
	// �C�[�W���O�Ŏg�p���邽�߂̕ϐ� 0-1
	float easing = m_totalSeconds / Player::NORMAL_ATTACK_TIME;
	// ��]�ʂ̌v�Z���s��
	currentAnimPos.y = -INIT_ROT + END_ROT * Easing::easeOutBack(easing) + currentAngle;
	// radian�ɕϊ�
	currentAnimPos.y = DirectX::XMConvertToRadians(currentAnimPos.y);
	// �v���C���[�̐ݒ�
	m_player->SetAnimationRotate(currentAnimPos);
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꂽ�u��)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ----------------------------------------------
void PlayerAttacking2::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	// ���
	if (key == DirectX::Keyboard::LeftShift && m_totalSeconds >= Player::X_COOL_TIME) {
		m_player->ChangeState(PlayerState::Dodging);
	}
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꑱ���Ă����)
/// </summary>
/// <param name="key">������Ă���L�[</param>
// ---------------------------------------------
void PlayerAttacking2::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g��X�V����(out)
/// </summary>
// ---------------------------------------------
void PlayerAttacking2::PostUpdate()
{
	// �A�j���[�V������������
	m_player->SetAnimationRotate(DirectX::SimpleMath::Vector3::Zero);

	// �U����ԂɕύX
	SwordState state = SwordState::Idle;
	EventMessenger::Execute(EventList::ChangeSwordState, &state);
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void PlayerAttacking2::Finalize()
{
}