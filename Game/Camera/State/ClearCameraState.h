// ---------------------------------------------
// ���O:	ClearCameraState.h
// ���e:	�N���A���̃J�����X�e�[�g�N���X
// �쐬:	�r�c����
// ---------------------------------------------
#pragma once
#ifndef CLEAR_CAMERA_STATE
#define CLEAR_CAMERA_STATE

// �C���N���[�h
#include "pch.h"
#include "Interface/ICameraState.h"

// �O���錾
class Camera;

/// <summary>
/// �N���A���̃J�����X�e�[�g�N���X
/// </summary>
class ClearCameraState : public ICameraState
{
	// ----------------------------
	// �萔
	// ----------------------------
public:
	// �J�����̉�]���x
	static constexpr float ROTATION_SPEED = 0.2f;
	// �ő厞�ԁi���o���ԁj
	static constexpr float MAX_TIME = 3.0f;
	// �ŏ��̃J���������i�J�n���̋����j
	static constexpr float START_DISTANCE = 10.0f;
	// �ő�J���������i�Y�[���A�E�g���̋����j
	static constexpr float MAX_DISTANCE = 20.0f;
	//�@�J�����̍���
	static constexpr float CAMERA_HEIGHT = 10.0f;


	// ----------------------------
	// �����o�֐�
	// ----------------------------
public:
	// �R���X�g���N�^
	ClearCameraState(Camera* camera);
	// �f�X�g���N�^
	~ClearCameraState()override;
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
	// �o�ߎ���
	float m_totalTime;

};

#endif // !CLEAR_CAMERA_STATE