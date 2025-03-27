// -----------------------------------------------------
// ���O:	BossStarting.h
// ���e:	�{�X�̊J�n���̃X�e�[�g�N���X
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
#ifndef BOSS_STARTING_DEFINED
#define BOSS_STARTING_DEFINED
// �C���N���[�h
#include "Interface/IState.h"

// �O���錾
class Boss;
class Player;
class IObject;

/// <summary>
/// �{�X�̊J�n���̃X�e�[�g
/// </summary>
class BossStarting : public IState
{
	// ---------------------------
	// �Œ�l
	// ---------------------------
public:
	// ������
	static constexpr float TOTAL_TIME = 4.0f;
	// �x������
	static constexpr float DELAY_TIME = 0.5f;
	// ���[�V��������
	static constexpr float MOVE_TIME = 2.5f;
	// �J�n���̍���
	static constexpr float START_HEIGHT = 100.0f;
	// �G�t�F�N�g�̍���
	static constexpr float PLAY_EFFECT_HEIGHT = 5.0f;
	// �J������h�炷����
	static constexpr float SHAKE_POWER = 2.0f;

	// ---------------------------
	// �����o�֐��i���J�j
	// ---------------------------
public:
	// �R���X�g���N�^
	BossStarting(Boss* boss);
	// �f�X�g���N�^
	~BossStarting() override;
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

	// ---------------------------
	// �����o�֐��i����J�j
	// ---------------------------
private:
	// �A�j���[�V�����̍X�V����
	void UpdateAnimation();
	// �x�����Ԃ̍X�V
	void UpdateDelay();
	// �ړ��̍X�V
	void UpdateMove();
	// �G�t�F�N�g���Đ�����
	void PlayEffect();

	// ---------------------------
	// �����o�ϐ�
	// ---------------------------
private:
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ��]
	float m_angle;
	// �J�n�̒x�����I�����Ă��邩
	bool m_isEndDelay;
	// ������
	float m_totalSeconds;
	// �G
	Boss* m_boss;
	// �v���C���[
	IObject* m_player;
};

#endif
