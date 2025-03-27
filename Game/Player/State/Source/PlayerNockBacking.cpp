// ----------------------------------------------
// ���O:	PlayerNockBacking
// ���e:	�v���C���[�̂�����
// �쐬:	�r�c
// ----------------------------------------------
// �C���N���[�h
#pragma once
#include "pch.h"
#include "Libraries/MyLib/Math.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Player/Player.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Player/State/Header/PlayerNockBacking.h"
#include "Game/Messenger/EventMessenger.h"

// ---------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�e�̃|�C���^</param>
// ---------------------------------------
PlayerNockBacking::PlayerNockBacking(Player* player)
	: m_player{ player },
	m_totalSeconds{},
	m_elapsedTime{},
	m_velocity{ 0.0f, 0.0f, -SPEED },
	m_bodyTilt{}
{
}

// ---------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------
PlayerNockBacking::~PlayerNockBacking()
{
}

// ---------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------
void PlayerNockBacking::Initialize()
{
}

// ---------------------------------------
/// <summary>
/// �X�e�[�g�X�V��(in)
/// </summary>
// ---------------------------------------
void PlayerNockBacking::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void PlayerNockBacking::Update(const float& elapsedTime)
{
	// �o�ߎ��Ԃ��L�^
	m_elapsedTime = elapsedTime;
	// �v���C���[�̈ʒu���擾
	m_position = m_player->GetPosition();
	// �^�[�Q�b�g�̈ʒu���擾
	Vector3 targetPos = *(Vector3*)EventMessenger::ExecuteGetter(GetterList::GetTargetPosition);
	// �v���C���[�̌�����G�Ɍ�����
	m_player->SetAngle(Math::CalculationAngle(m_position, targetPos));
	// �A�j���[�V�����̍X�V
	UpdateAnimation();
	// �X�e�[�g�J�n���玞�Ԃ��v���A��莞�Ԃŕʂ�State�֑J�ڂ�����
	m_player->TimeComparison(m_totalSeconds, END_TIME, PlayerState::Idling, elapsedTime);
}

// ---------------------------------------------
/// <summary>
/// �A�j���[�V�����X�V
/// </summary>
// ---------------------------------------------
void PlayerNockBacking::UpdateAnimation()
{
	// �o�ߎ��Ԃ����Z
	m_totalSeconds += m_elapsedTime;

	// �m�b�N�o�b�N�̃A�j���[�V����
	if (m_totalSeconds <= NOCKBACKING_TIME){
		NockBackAnimation();
	}
	// �ċA�A�j���[�V����
	else if (m_totalSeconds <= RETURN_TIME){
		ReturnAnimation();
	}
}

// ---------------------------------------------
/// <summary>
/// �m�b�N�o�b�N�A�j���[�V����
/// </summary>
// ---------------------------------------------
void PlayerNockBacking::NockBackAnimation()
{
	// ���Ԃ𐳋K������
	float t = std::min(1.0f, m_totalSeconds / NOCKBACKING_TIME);

	// �^�[�Q�b�g�̈ʒu���擾
	Vector3 targetPos = *(Vector3*)EventMessenger::ExecuteGetter(GetterList::GetTargetPosition);
	Vector3 playerPos = m_player->GetPosition();

	// �ǂ����̕����Ƀm�b�N�o�b�N����̂�
	m_nockBackAngle = Math::CalculationAngle(targetPos, playerPos);
	Matrix rotMatrix = Matrix::CreateRotationY(-m_nockBackAngle);

	// �m�b�N�o�b�N��
	m_position += Vector3::Transform(m_velocity, rotMatrix) * m_elapsedTime;

	// sin�g�ŏ㉺�ړ�������
	m_position.y = Math::NormalizeSin(t) * MAX_UP_VALUE;

	// �X��
	m_bodyTilt.x = DirectX::XMConvertToRadians(-90 * Easing::easeOutBack(t));

	// �v���C���[�̈ʒu��ݒ�
	m_player->SetPosition(m_position);
	// �A�j���[�V�����p�̐ݒ�
	m_player->SetAnimationRotate(m_bodyTilt);
}

// -------------------------------------------
/// <summary>
/// �ċA�A�j���[�V����
/// </summary>
// -------------------------------------------
void PlayerNockBacking::ReturnAnimation()
{
	// ���Ԃ𐳋K������
	float t = std::min(1.0f, (m_totalSeconds - NOCKBACKING_TIME) / (RETURN_TIME - NOCKBACKING_TIME));
	// �m�b�N�o�b�N��
	Matrix rotMatrix = Matrix::CreateRotationY(-m_nockBackAngle);
	m_position += Vector3::Transform(m_velocity, rotMatrix) * m_elapsedTime;
	// sin�g�ŏ㉺�ړ�������
	m_position.y = Math::NormalizeSin(t) * RETURN_UP_VALUE;
	// �X��
	m_bodyTilt.x = DirectX::XMConvertToRadians(-90 - 270 * Easing::easeOutBack(t));
	// �v���C���[�̈ʒu��ݒ�
	m_player->SetPosition(m_position);
	// �A�j���[�V�����p�̐ݒ�
	m_player->SetAnimationRotate(m_bodyTilt);
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꂽ�u��)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ----------------------------------------------
void PlayerNockBacking::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// �L�[���͏��� (�L�[�������ꑱ���Ă����)
/// </summary>
/// <param name="key">������Ă���L�[</param>
// ---------------------------------------------
void PlayerNockBacking::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�X�V����(out)
/// </summary>
// ---------------------------------------------
void PlayerNockBacking::PostUpdate()
{	
	// �����ҋ@��ԂɕύX
	SwordState state = SwordState::Idle;
	EventMessenger::Execute(EventList::ChangeSwordState, &state);
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void PlayerNockBacking::Finalize()
{
}