// ---------------------------------------------
// ���O		:PlayCameraState.h
// ���e		:�v���C���̃J�����X�e�[�g�N���X
// �쐬		:�r�c����
// ---------------------------------------------
#pragma once
#ifndef PLAY_CAMERA_STATE
#define PLAY_CAMERA_STATE

// �C���N���[�h
#include "pch.h"
#include "Interface/ICameraState.h"

// �O���錾
class Camera;

/// <summary>
/// �v���C�V�[���̃J�����X�e�[�g�N���X
/// </summary>
class PlayCameraState : public ICameraState
{
	// ----------------------------
	// �萔
	// ----------------------------
public:
	// �X�e�[�W�̒���
	static constexpr float STAGE_LENGTH = 100;
	// �J�����̕�ԗ�
	static constexpr float LERP_RATE = 0.075f;

	// ----------------------------
	// �����o�֐�
	// ----------------------------
public:
	// �R���X�g���N�^
	PlayCameraState(Camera* camera);
	// �f�X�g���N�^
	~PlayCameraState()override;
	// �X�e�[�g�ύX�iin�j
	void PreUpdate()override;
	// �X�V����
	void Update(
		const DirectX::SimpleMath::Vector3& playerPos,
		const DirectX::SimpleMath::Vector3& enemyPos,
		float elapsedTime
	)override;
	// �X�e�[�g�ύX�iout�j
	void PostUpdate()override;

	// ----------------------------
	// �����o�ϐ�
	// ----------------------------
private:
	// �J����
	Camera* m_camera;
};

	#endif // !PLAY_CAMERA_STATE
