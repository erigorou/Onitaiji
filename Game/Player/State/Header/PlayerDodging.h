// ----------------------------------------------
// ���O:	PlayerDodging.h
// ���e:	�v���C���[�̉�����
// �쐬:	�r�c
// ----------------------------------------------
#pragma once
#ifndef PLAYER_DODGING_DEFINED
#define PLAYER_DODGING_DEFINED

// �C���N���[�h
#include "pch.h"
#include "Interface/IPlayer.h"

// �O���錾
class Player;

/// <summary>
/// �v���C���[�̉�����
/// </summary>
class PlayerDodging : public IPlayer
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
private:
	// ��𒆂̉�]����
	static constexpr float SPIN_TIME = 1.0f;
	// �����̉�]����
	static constexpr float SPIN_REST_TIME = 1.5f;
	// ��𒆂̃A�j���[�V��������
	static constexpr float ANIMATION_TIME = 0.4f;
	// �����̍d������
	static constexpr float DODGING_RECOVERY_TIME = 1.0f;
	// ���[�����O�I������
	static constexpr float ANIMATION_END_TIME = 1.5f;
	// ������̖��C
	static constexpr float DODGE_FUNCTION = 0.93f;
	// �����Z�Z���ȉ��폜
	static constexpr int TRUNCATION_DIGIT = 4;
	// ������̑��x
	// �㏸��
	static constexpr float DODGING_SPEED = 1.5f;
	static constexpr float UP_VALUE = 3.0f;
	// ��]��
	static constexpr float ROLLING_ROT = 360.0f;
	// ���[�����O��̉�]�p�x
	static constexpr float ROLLING_REST_ROT = 30.0f;

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �f�X�g���N�^
	~PlayerDodging() override;
	// ����������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V��������
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �I������
	void Finalize() override;
	// �R���X�g���N�^
	PlayerDodging(Player* player);
	// �L�[����
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �L�[����
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �v���C���[�̃A�j���[�V�����p�X�V����
	void UpdateAnimation(float totalTime);
	// ���[�����O�A�j���[�V����
	void RollingAnimation(float totalTime);
	// �v���C���[�̈ړ���K�p
	void AdjustCharacterTransition(float totalTime);
	// �v���C���[�̈ړ���K�p
	void ApplyPlayerMovement(DirectX::SimpleMath::Vector3& parentPos);

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ������
	float m_totalSeconds;
	// �I������
	float m_finishTime;
	// �|�W�V����
	DirectX::SimpleMath::Vector3 m_position;
	// �v���C���[�̈ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �v���C���[
	Player* m_player;
	// �㏸��
	float m_upValue;
	// ���~��
	float m_downValue;
	// ��]��
	DirectX::SimpleMath::Vector3 m_rollingValue;
};

#endif  // PLAYER_DODGING_DEFINED