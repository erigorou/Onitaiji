// ---------------------------------------------
// ���O:	TitleCameraState.cpp
// ���e:	�^�C�g�����̃J�����X�e�[�g�N���X
// �쐬:	�r�c����
// ---------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "TitleCameraState.h"
#include "../Camera.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera">�J�����I�u�W�F�N�g</param>
// ---------------------------------------------
TitleCameraState::TitleCameraState(Camera* camera)
	: m_camera(camera)
	, m_angle{}
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
TitleCameraState::~TitleCameraState()
{
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̑O�X�V����
/// </summary>
// ---------------------------------------------
void TitleCameraState::PreUpdate()
{
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̍X�V����
/// </summary>
/// <param name="playerPos">�v���C���[�̍��W</param>
/// <param name="enemyPos">�G�̍��W</param>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void TitleCameraState::Update(
	const DirectX::SimpleMath::Vector3& playerPos,
	const DirectX::SimpleMath::Vector3& enemyPos,
	float elapsedTime
)
{
	UNREFERENCED_PARAMETER(playerPos);
	UNREFERENCED_PARAMETER(enemyPos);

	// ��]
	m_angle += ROTATE_SPEED * elapsedTime; // ���Ԃɉ����Ċp�x���X�V
	// �J�����̈ʒu���~�^���Ɋ�Â��Čv�Z
	m_camera->m_position.x = TITLE_DIRECTION.x * cosf(m_angle) + m_camera->m_shakePos.x; // x���W
	m_camera->m_position.z = TITLE_DIRECTION.z * sinf(m_angle) + m_camera->m_shakePos.z; // z���W
	m_camera->m_position.y = TITLE_DIRECTION.y + m_camera->m_shakePos.y;                 // �������Œ�
	// �J�����̒����_�𒆐S�ɐݒ�
	m_camera->m_target = DirectX::SimpleMath::Vector3::Zero + CAMERA_Y_PLUS + m_camera->m_shakePos;

	// �r���[�s����X�V
	m_camera->CalculateViewMatrix();
	m_camera->CalculateCameraAngle();
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̌�X�V����
/// </summary>
// ---------------------------------------------
void TitleCameraState::PostUpdate()
{
}