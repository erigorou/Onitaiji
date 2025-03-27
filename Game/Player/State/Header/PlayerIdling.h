// ----------------------------------------------
// ���O:	PlayerIdling.h
// ���e:	�v���C���[�̑ҋ@���
// �쐬:	�r�c
// ----------------------------------------------
#pragma once
#ifndef PLAYER_IDLING_DEFINED
#define PLAYER_IDLING_DEFINED

// �C���N���[�h
#include "pch.h"
#include "Interface/IPlayer.h"

// �O���錾
class Player;

/// <summary>
/// �v���C���[�̑ҋ@���
/// </summary>
class PlayerIdling : public IPlayer
{
	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	PlayerIdling(Player* player);
	// �f�X�g���N�^
	~PlayerIdling() override;
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

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �L�[����
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �L�[����
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// ������
	float m_totalSeconds;
	// �v���C���[
	Player* m_player;
};

#endif  // PLAYER_IDLING_DEFINED