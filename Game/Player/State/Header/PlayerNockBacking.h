// ----------------------------------------------
// ���O:	PlayerNockBacking
// ���e:	�v���C���[�̂�����
// �쐬:	�r�c
// ----------------------------------------------
#pragma once
#ifndef PLAYER_NOCKBACKING_DEFINED
#define PLAYER_NOCKBACKING_DEFINED

// �C���N���[�h
#include "pch.h"
#include "Interface/IPlayer.h"

// �O���錾
class Player;

/// <summary>
/// �v���C���[�̂�����
/// </summary>
class PlayerNockBacking : public IPlayer
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
private:
	// ����S�̂̎���
	static constexpr float NOCKBACKING_TIME = 1.0f;
	// ���ꂩ�畜�A���鎞��
	static constexpr float RETURN_TIME = 2.0f;
	// ���ꂩ�畜�A���鎞��
	static constexpr float END_TIME = 2.3f;
	// �㏸�l
	static constexpr float MAX_UP_VALUE = 2.0f;
	// �㏸�l
	static constexpr float RETURN_UP_VALUE = 1.0f;
	// ���x
	static constexpr float SPEED = 50.0f;

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �f�X�g���N�^
	~PlayerNockBacking() override;
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
	PlayerNockBacking(Player* player);
	// �L�[����
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �L�[����
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �A�j���[�V�����̍X�V
	void UpdateAnimation();
	// �m�b�N�o�b�N�A�j���[�V����
	void NockBackAnimation();
	// �ċA�A�j���[�V����
	void ReturnAnimation();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �o�ߎ���
	float m_elapsedTime;
	// ������
	float m_totalSeconds;
	// �m�b�N�o�b�N����
	float m_nockBackAngle;
	// �X��
	DirectX::SimpleMath::Vector3 m_bodyTilt;
	// �|�W�V����
	DirectX::SimpleMath::Vector3 m_position;
	// �v���C���[�̈ړ����x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �v���C���[
	Player* m_player;
	// ���f��
	DirectX::Model* m_model;
};

#endif  // PLAYER_DODGING_DEFINED