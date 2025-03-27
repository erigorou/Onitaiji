// ----------------------------------------------
// ���O:	PlayerIdling.h
// ���e:	�v���C���[�̑ҋ@���
// �쐬:	�r�c
// ----------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/Header/PlayerIdling.h"
#include "Game/Messenger/EventMessenger.h"

// ---------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�e�̃|�C���^</param>
// ---------------------------------------
PlayerIdling::PlayerIdling(Player* player)
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
PlayerIdling::~PlayerIdling()
{
}

// ---------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------
void PlayerIdling::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�ύX����(in)
/// </summary>
// ---------------------------------------------
void PlayerIdling::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;

	// �ړ����x�̏�����
	m_player->SetSpeed(DirectX::SimpleMath::Vector3::Zero);
	// �ړ������x�̏�����
	m_player->SetAcceleration(DirectX::SimpleMath::Vector3::Zero);
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void PlayerIdling::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ̉��Z
	m_totalSeconds += elapsedTime;
	// �^�[�Q�b�g�̈ʒu���擾
	DirectX::SimpleMath::Vector3 targetPos =
		*(DirectX::SimpleMath::Vector3*)EventMessenger::ExecuteGetter(GetterList::GetTargetPosition);
	// �v���C���[�̌�����G�Ɍ�����
	m_player->SetAngle(m_player->CalucratePlayerRotation(targetPos));
	// �v���C���[�̈ړ�
	m_player->MovePlayer();
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�ύX����(out)
/// </summary>
// ---------------------------------------------
void PlayerIdling::PostUpdate()
{
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꂽ�u��)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ----------------------------------------------
void PlayerIdling::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	// �U������
	if (key == DirectX::Keyboard::X) {
		m_player->ChangeState(PlayerState::Attacking1);
	}
	// �������
	if (key == DirectX::Keyboard::LeftShift) {
		m_player->ChangeState(PlayerState::Dodging);
	}
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꑱ���Ă����)
/// </summary>
/// <param name="key">������Ă���L�[</param>
// ---------------------------------------------
void PlayerIdling::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void PlayerIdling::Finalize()
{
}