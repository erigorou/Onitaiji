// ---------------------------------------------
// ���O		:PlayCameraState.cpp
// ���e		:�v���C���̃J�����X�e�[�g�N���X
// �쐬		:�r�c����
// ---------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "PlayCameraState.h"
#include "../Camera.h"
#include "Libraries/MyLib/Math.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="camera">�J�����I�u�W�F�N�g</param>
// ---------------------------------------------
PlayCameraState::PlayCameraState(Camera* camera)
	: m_camera(camera)
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
PlayCameraState::~PlayCameraState()
{
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̑O�X�V����
/// </summary>
// ---------------------------------------------
void PlayCameraState::PreUpdate()
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
void PlayCameraState::Update(
	const DirectX::SimpleMath::Vector3& playerPos,
	const DirectX::SimpleMath::Vector3& enemyPos,
	float elapsedTime
)
{
	// �v���C���[����G�ւ̕����x�N�g�����v�Z
	Vector3 playerToEnemy = enemyPos - playerPos;
	playerToEnemy.Normalize();
	// �v���C���ƓG�̋������擾
	float distance = Vector3::Distance(playerPos, enemyPos);
	// �����ɂ���ăJ�����̍�����ύX
	float normalizedDistance = std::min(std::max((distance / STAGE_LENGTH), 0.8f), 1.2f);
	// �J�����̖ڕW�ʒu���v�Z
	Vector3 targetCameraPos = playerPos - playerToEnemy * Camera::CAMERA_DIRECTION;
	// �����������ˑ��ɕύX
	targetCameraPos.y = Camera::CAMERA_POSITION_Y * normalizedDistance;
	// �J�����ʒu���Ԃ��ĒǏ]
	float followSpeed = LERP_RATE;
	// �J�����̈ʒu���Ԃ��ĒǏ]
	m_camera->m_position = Math::LerpVector(m_camera->m_position, targetCameraPos, followSpeed);
	// �����_�̖ڕW�ʒu���v�Z
	Vector3 targetLookAt = enemyPos;
	targetLookAt.y = m_camera->m_targetHeight;
	// �����_���Ԃ��ĒǏ]
	m_camera->m_target = Math::LerpVector(m_camera->m_target, targetLookAt, followSpeed);
	// �J�����̐U�������i�K�v�Ȃ�U�����Ԃ�n���j
	m_camera->Shake(elapsedTime);
	// �r���[�s��ƃA���O���̍X�V
	m_camera->CalculateViewMatrix();
	m_camera->CalculateCameraAngle();
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̌�X�V����
/// </summary>
// ---------------------------------------------
void PlayCameraState::PostUpdate()
{
}