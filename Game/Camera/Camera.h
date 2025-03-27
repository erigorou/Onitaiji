// ---------------------------------------------
// ���O:	Camera.h
// ���e:	�J�����{�̂̃N���X
// �쐬:	�r�c����
// ---------------------------------------------
// �C���N���[�h
#pragma once
#include "Interface/ICameraState.h"
#include "State/TitleCameraState.h"
#include "State/PlayCameraState.h"
#include "State/ClearCameraState.h"

// �J�����̃X�e�[�g
enum class CameraState
{
	Title,
	Play,
	Clear
};


/// <summary>
/// �J�����N���X
/// </summary>
class Camera
{
// ----------------------------
// �萔
// ----------------------------
public:
	// �J�����̏����ʒu
	static constexpr float CAMERA_POSITION_Y = 10.0f;
	// �J�����̏����p�x
	static constexpr float CAMERA_DIRECTION = 30.0f;
	// �^�[�Q�b�g�̍���
	static constexpr float TARGET_HEIGHT = 8.0f;

	// �J�����̐U��
	static constexpr float SHAKE_TIME = 0.5f;
	// �J�����̐U���̋���
	static constexpr float SHAKE_POWER = 0.5f;
	// �ɏ��l
	static constexpr float MINIMAL = 0.01f;

	// �J�����̒Ǐ]�W��
	static constexpr float CAMERA_EYE_RATE = 1.0f;
	// �^�[�Q�b�g�̒Ǐ]�W��
	static constexpr float CAMERA_TARGET_RATE = 0.05f;

	// ----------------------------
	// �A�N�Z�T
	// ----------------------------
public:
	// �r���[�s��
	DirectX::SimpleMath::Matrix GetViewMatrix() const { return m_view; }
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix GetProjectionMatrix() const { return m_projection; }
	// �J�������W
	DirectX::SimpleMath::Vector3 GetEyePosition() const { return m_position; }
	// �����_
	DirectX::SimpleMath::Vector3 GetTargetPosition() const { return m_target; }
	// �J�����̓��̕���
	DirectX::SimpleMath::Vector3 GetUpVector() const { return m_up; }
	// �A���O��
	float GetCameraAngle() const { return m_angle; }

	// ----------------------------
	// �����o�֐�(���J)
	// ----------------------------
public:
	// �R���X�g���N�^
	Camera(const DirectX::SimpleMath::Vector3& target = DirectX::SimpleMath::Vector3::Zero);
	// �f�X�g���N�^
	~Camera() = default;
	// �X�V����
	void Update(
		const DirectX::SimpleMath::Vector3& playerPos,
		const DirectX::SimpleMath::Vector3& enemyPos,
		const float elapsedTime
	);
	// �J������h�炷
	void SetShake(void* power);
	// �r���[�s��̌v�Z
	void CalculateViewMatrix();
	// �J�����̃A���O�����v�Z
	void CalculateCameraAngle();
	// �J������h�炷
	void Shake(float elapsedTime);
	// �X�e�[�g�̕ύX
	void ChangeState(void* state);

	// ----------------------------
	// �����o�֐�(����J)
	// ----------------------------
private:
	// �X�e�[�g�̍쐬
	void CreateState();

	// ----------------------------
	// �����o�ϐ�
	// ----------------------------
public:
	// �J�����̈ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// �r���[�s��
	DirectX::SimpleMath::Matrix	 m_view;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;
	// �J�����̒����_
	DirectX::SimpleMath::Vector3 m_target;
	// �J�����̓��̕���
	DirectX::SimpleMath::Vector3 m_up;
	// �J�����̃A���O��
	float m_currentAngle;
	// �J�����̃A���O��
	float m_angle;
	// �^�[�Q�b�g�̍���
	float m_targetHeight;
	// �J�����̐U��
	bool m_isShake;
	// �U������
	float m_shakeTime;
	// �J�����̐U���ʒu
	DirectX::SimpleMath::Vector3 m_shakePos;
	// �J�����̐U���̋���
	float m_shakePower;
	// ���݂̃X�e�[�g
	ICameraState* m_currentState;
	// �^�C�g���X�e�[�g
	std::unique_ptr<TitleCameraState> m_titleState;
	// �v���C�X�e�[�g
	std::unique_ptr<PlayCameraState> m_playState;
	// �N���A�X�e�[�g
	std::unique_ptr<ClearCameraState> m_clearState;

	// �X�e�[�g���i�[
	std::vector<ICameraState*> m_states;
};