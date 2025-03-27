// ---------------------------------------------
// ���O:	Camera.cpp
// ���e:	�J�����{�̂̃N���X
// �쐬:	�r�c����
// ---------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/Camera/Camera.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Messenger/EventMessenger.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target">�^�[�Q�b�g���W</param>
// ---------------------------------------------
Camera::Camera(const DirectX::SimpleMath::Vector3& target)
	:m_view{}
	, m_projection{}
	, m_target{ target }
	, m_up{ DirectX::SimpleMath::Vector3::UnitY }
	, m_position{}
	, m_angle{}
	, m_targetHeight{ TARGET_HEIGHT }
	, m_isShake{ false }
	, m_shakeTime{ SHAKE_TIME }
	, m_shakePos{}
{
	// �X�e�[�g���쐬
	CreateState();

	// �J�����̃V�F�C�N���C�x���g�ɓo�^
	EventMessenger::Attach(EventList::ShakeCamera, std::bind(&Camera::SetShake, this, std::placeholders::_1));
	// �J�����̃X�e�[�g�ύX���C�x���g��
	EventMessenger::Attach(EventList::ChangeCamera, std::bind(&Camera::ChangeState, this, std::placeholders::_1));
}

// ---------------------------------------------
/// <summary>
/// �J�����̍X�V����
/// </summary>
/// <param name="playerPos">�v���C���[�̍��W</param>
/// <param name="enemyPos">�G�̍��W</param>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void Camera::Update(
	const DirectX::SimpleMath::Vector3& playerPos,
	const DirectX::SimpleMath::Vector3& enemyPos,
	const float elapsedTime
)
{
	// �X�e�[�g���X�V
	m_currentState->Update(
		playerPos,
		enemyPos,
		elapsedTime
	);
}

// ---------------------------------------------
/// <summary>
/// �J�����̃r���[�s����v�Z����
/// </summary>
// ---------------------------------------------
void Camera::CalculateViewMatrix()
{
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_target, m_up);
}

// ---------------------------------------------
/// <summary>
/// �J�����̃A���O�����v�Z����
/// </summary>
// ---------------------------------------------
void Camera::CalculateCameraAngle()
{
	// �J�����̑O�����x�N�g��
	DirectX::SimpleMath::Vector3 forward = m_target - m_position;
	forward.Normalize();

	// ���E���W�n�̑O�����x�N�g��
	DirectX::SimpleMath::Vector3 worldForward = DirectX::SimpleMath::Vector3::Forward;

	// ���ς��v�Z
	float dotProduct = forward.Dot(worldForward);

	// ���ς���p�x���v�Z�i�ʓx�@�j
	float targetAngle = acosf(dotProduct);

	// �J�����̑O�����x�N�g�����E�����Ɍ����Ă��邩�ǂ����ŕ���������
	DirectX::SimpleMath::Vector3 crossProduct = forward.Cross(worldForward);
	if (crossProduct.y < 0)
	{
		targetAngle = -targetAngle;
	}

	// ���`��ԂŌ��݂̃A���O�����X�V
	m_currentAngle = Math::LerpFloat(m_currentAngle, targetAngle, CAMERA_TARGET_RATE);

	// �X�V���ꂽ�A���O���𔽉f
	m_angle = m_currentAngle;
}

// ---------------------------------------------
/// <summary>
/// �J�����̐U��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void Camera::Shake(float elapsedTime)
{
	if (!m_isShake) return;

	m_shakeTime -= elapsedTime;

	// �U�����Ԃ�0�ȉ��ɂȂ�����U�����I��
	if (m_shakeTime <= 0.0f)
	{
		m_isShake = false;
		return;
	}

	// shakeTime�ɉ����ĐU���̋���������
	float power = (m_shakeTime / SHAKE_TIME) * m_shakePower;

	DirectX::SimpleMath::Vector3 max = DirectX::SimpleMath::Vector3(power, power, power);
	DirectX::SimpleMath::Vector3 min = DirectX::SimpleMath::Vector3(-power, -power, -power);

	// �J�����̈ʒu��h�炷
	m_shakePos = Math::RandomVector3(min, max);
	m_target += Math::RandomVector3(min, max);
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="state">�V�����J�����X�e�[�g</param>
// ---------------------------------------------
void Camera::ChangeState(void* state)
{
	int index = *static_cast<int*>(state);

	// �X�e�[�g�������Ȃ�ύX���Ȃ�
	if (m_currentState == m_states[index]) return;

	// �X�e�[�g�̕ύX�葱��
	m_currentState->PostUpdate();
	m_currentState = m_states[index];
	m_currentState->PreUpdate();
}

// ---------------------------------------------
/// <summary>
/// �X�e�[�g�̍쐬
/// </summary>
// ---------------------------------------------
void Camera::CreateState()
{
	// �^�C�g���X�e�[�g�̍쐬
	m_titleState = std::make_unique<TitleCameraState>(this);
	m_states.push_back(m_titleState.get());

	// �v���C�X�e�[�g�̍쐬
	m_playState = std::make_unique<PlayCameraState>(this);
	m_states.push_back(m_playState.get());

	// �N���A�X�e�[�g�̍쐬
	m_clearState = std::make_unique<ClearCameraState>(this);
	m_states.push_back(m_clearState.get());

	// �����X�e�[�g��ݒ�
	m_currentState = m_titleState.get();
}

// ---------------------------------------------
/// <summary>
/// �J�����̐U�����J�n
/// </summary>
/// <param name="power">�U���̋���</param>
// ---------------------------------------------
void Camera::SetShake(void* power)
{
	m_isShake = true;
	m_shakeTime = SHAKE_TIME;
	m_shakePower = *static_cast<float*>(power);
}