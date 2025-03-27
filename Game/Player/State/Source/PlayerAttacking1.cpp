// ----------------------------------------------
// ���O:	PlayerAttacking1.h
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
#include "Game/Player/State/Header/PlayerAttacking1.h"

// ---------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�e�̃|�C���^</param>
// ---------------------------------------
PlayerAttacking1::PlayerAttacking1(Player* player)
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
PlayerAttacking1::~PlayerAttacking1()
{
}

// ---------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------
void PlayerAttacking1::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�X�V��(in)
/// </summary>
// ---------------------------------------------
void PlayerAttacking1::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;

	// ������U����ԂɕύX
	SwordState state = SwordState::Attack1;
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
void PlayerAttacking1::Update(const float& elapsedTime)
{
	m_totalSeconds += elapsedTime;

	// �A�j���[�V�����̍X�V
	UpdateAnimation();

	// ���Ԃ��v�����A��莞�Ԍo�߂ŃX�e�[�g��J��
	m_player->TimeComparison(m_totalSeconds, Player::APPLIED_ATTACK_TIME, PlayerState::Idling, elapsedTime);
}

// ---------------------------------------------
/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
// ---------------------------------------------
void PlayerAttacking1::UpdateAnimation()
{
	if (m_totalSeconds > Player::NORMAL_ATTACK_TIME) return;

	// �A�j���[�V�����̉�]�ʂ��擾
	DirectX::SimpleMath::Vector3 currentAnimPos = DirectX::SimpleMath::Vector3::Zero;
	// �v���C���[�̉�]�ʂ��擾
	float currentAngle = m_player->GetAngle();
	// �C�[�W���O�Ŏg�p���邽�߂̕ϐ� 0-1
	float easing = m_totalSeconds / Player::NORMAL_ATTACK_TIME;
	// ��]�ʂ̌v�Z���s��
	currentAnimPos.y = INIT_ROT - END_ROT * Easing::easeOutExpo(easing) + currentAngle;
	// radian�ɕϊ�
	currentAnimPos.y = DirectX::XMConvertToRadians(currentAnimPos.y);
	// �v���C���[�ɐݒ肷��
	m_player->SetAnimationRotate(currentAnimPos);
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꂽ�u��)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ----------------------------------------------
void PlayerAttacking1::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	// �A���U��
	if (key == DirectX::Keyboard::X && m_totalSeconds >= Player::X_COOL_TIME){
		m_player->ChangeState(PlayerState::Attacking2);
	}
	// ���
	if (key == DirectX::Keyboard::LeftShift){
		m_player->ChangeState(PlayerState::Dodging);
	}
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꑱ���Ă����)
/// </summary>
/// <param name="key">������Ă���L�[</param>
// ---------------------------------------------
void PlayerAttacking1::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�X�V����(out)
/// </summary>
// ---------------------------------------------
void PlayerAttacking1::PostUpdate()
{
	// �A�j���[�V�����̍X�V
	m_player->SetAnimationRotate(DirectX::SimpleMath::Vector3::Zero);

	// �����ҋ@��ԂɕύX
	SwordState state = SwordState::Idle;
	EventMessenger::Execute(EventList::ChangeSwordState, &state);
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void PlayerAttacking1::Finalize()
{
}