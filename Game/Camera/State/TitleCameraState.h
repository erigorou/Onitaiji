// ---------------------------------------------
// ���O:	TitleCameraState.h
// ���e:	�^�C�g�����̃J�����X�e�[�g�N���X
// �쐬:	�r�c����
// ---------------------------------------------
#pragma once
#ifndef TITLE_CAMERA_STATE
#define TITLE_CAMERA_STATE

// �C���N���[�h
#include "pch.h"
#include "Interface/ICameraState.h"

// �O���錾
class Camera;

class TitleCameraState : public ICameraState
{
// ----------------------------
// �萔
// ----------------------------
private:
	// �J������Y���W
	static constexpr DirectX::SimpleMath::Vector3 CAMERA_Y_PLUS = { 0.0f, 40.0f, 0.0f };
	// �^�C�g���ł̃J�����̋���
	static constexpr DirectX::SimpleMath::Vector3 TITLE_DIRECTION = { 125.0f, 10.0f, 125.0f };
	// ��]���x
	static constexpr float ROTATE_SPEED = -0.1f;

// ----------------------------
// �����o�֐�
// ----------------------------
public:
	// �R���X�g���N�^
	TitleCameraState(Camera* camera);
	// �f�X�g���N�^
	~TitleCameraState()override;
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
	// �p�x
	float m_angle;
};

#endif