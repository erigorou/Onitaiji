// ----------------------------------------------
// ���O:	PlayerAttacking2.h
// ���e:	�v���C���[�̍U�����
// �쐬:	�r�c
// ----------------------------------------------
#pragma once
#ifndef PLAYER_ATTACKING2_DEFINED
#define PLAYER_ATTACKING2_DEFINED

// �C���N���[�h
#include "pch.h"
#include "Interface/IPlayer.h"

// �O���錾
class Player;

/// <summary>
/// �v���C���[�̍U�����
/// </summary>
class PlayerAttacking2 : public IPlayer
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// ������]�p
	static  constexpr float INIT_ROT = 40.0f;
	// �ŏI��]�p
	static  constexpr float END_ROT = 80.0f;


	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	PlayerAttacking2(Player* player);
	// �f�X�g���N�^
	~PlayerAttacking2() override;
	// ��������
	void Initialize() override;
	// ���O�X�V����
	void PreUpdate() override;
	// �X�V��������
	void Update(const float& elapsedTime) override;
	// ����X�V����
	void PostUpdate() override;
	// �I������
	void Finalize() override;
	// �L�[���͂�ʒm
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �L�[���͂�ʒm
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �A�j���[�V�����̍X�V
	void UpdateAnimation();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ������
	float m_totalSeconds;
	// �v���C���[
	Player* m_player;
};

#endif  // PLAYERATTACKING2_DEFINED