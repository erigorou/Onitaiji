/// ---------------------------
///
/// �v���C���[�̌��̍U���i�~�؂�j(���])
///
/// ---------------------------

#include "pch.h"
#include <cassert>
#include "Game/Weapon/Sword/Sword.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/Math.h"
#include "Libraries/MyLib/Collision.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Messenger/EventMessenger.h"

#include "Game/Player/Player.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Sword/Header/SwordAttacking1.h"

// --------------------------------
//  �Œ�l
// --------------------------------
const float SwordAttacking1::RADIAN_90 = DirectX::XMConvertToRadians(90);

// --------------------------------
//  �R���X�g���N�^
// --------------------------------
SwordAttacking1::SwordAttacking1(Sword* sword)
	: m_sword(sword)
	, m_position(5.0f, 0.0f, 5.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
	, m_angle(0.0f)
	, m_rot(0.0f, 0.0f, 0.0f)
	, m_totalSeconds(0.0f)
	, m_worldMatrix(DirectX::SimpleMath::Matrix::Identity)
{
}

// --------------------------------
//  �f�X�g���N�^
// --------------------------------
SwordAttacking1::~SwordAttacking1()
{
}

// --------------------------------
//  ����������
// --------------------------------
void SwordAttacking1::Initialize()
{
}

// --------------------------------
//  ��ԊJ�n����
// --------------------------------
void SwordAttacking1::PreUpdate()
{
	// �U���t���O�𗧂Ă�
	m_sword->SetAttackFlag(true);

	m_totalSeconds = 0.0f;	// ���Ԍo�߂̃��Z�b�g

	m_rootPos.clear();	// ���{�̍��W���N���A
	m_tipPos.clear();	// ��[�̍��W���N���A

	bool canHit = true;

	// �Փˉ\�t���O��G�S�̂ɕt�^
	EventMessenger::Execute(EventList::EnemyCanHit, &canHit);
}

// --------------------------------
//  �X�V����
// --------------------------------
void SwordAttacking1::Update(float elapsedTime)
{
	// �o�ߎ��Ԃ��v��
	m_totalSeconds += elapsedTime;

	// �v���C���[���擾
	auto player = m_sword->GetPlayer();
	// �v���C���[�̍��W���擾
	m_position = player->GetPosition();
	// �v���C���[�̉�]���擾
	m_angle = player->GetAngle();

	// �A�j���[�V�����̍X�V
	UpdateAnimation();
	// ���[���h�s��̍X�V
	UpdateWorldMatrix();
	// �����蔻��̈ʒu��ݒ�
	m_sword->SetCollisionPosition(m_worldMatrix);
	// �G�t�F�N�g�`��p�̍��{�ƒ��_��`��
	GetCudgelBothEnds();
}

// --------------------------------
//  �A�j���[�V�����X�V����
// --------------------------------
void SwordAttacking1::UpdateAnimation()
{
	// �C�[�W���O�֐����g���ĉ�]���v�Z
	float t = 0.0f;

	if (m_totalSeconds <= ATTACK_TIME)
	{
		// ���Ԃ̐��K��
		t = m_totalSeconds / ATTACK_TIME;

		m_rot.y = MAX_SIDE_ANGLE * Easing::easeOutBack(t);
		m_rot.x = INIT_ANGLE - MAX_VERTICAL_ANGLE * Easing::easeOutBack(t);

		if (m_rot.y < MAX_SIDE_ANGLE)
		{
			m_sword->SetAttackFlag(false);
		}

		// �ݒ�
		m_rot.x = DirectX::XMConvertToRadians(m_rot.x);
		m_rot.y = DirectX::XMConvertToRadians(m_rot.y);
	}
}

// --------------------------------
// ���[���h�s��̍X�V����
// --------------------------------
void SwordAttacking1::UpdateWorldMatrix()
{
	// ���[���h�s����X�V����
	m_worldMatrix = Matrix::CreateScale(Sword::SWORD_SCALE);

	// ����90�x���Ɍ�����
	Quaternion initialRotation = Quaternion::CreateFromAxisAngle(Vector3::UnitX, RADIAN_90);

	// �ガ�����̉�]
	Quaternion attackRotation = Quaternion::CreateFromYawPitchRoll(
		m_rot.y,
		m_rot.x,
		0.0f
	);

	// �v���C���[�̉�]
	Quaternion playerRotation = Quaternion::CreateFromAxisAngle(Vector3::UnitY, -m_angle);

	// ��]�̍���
	Quaternion totalRotation = initialRotation * attackRotation * playerRotation;

	// ���[���h�s��ɉ�]�ƕ��s�ړ���K�p
	m_worldMatrix *= Matrix::CreateTranslation(MATRIX_DIRECTION); // �����������炷
	m_worldMatrix *= Matrix::CreateFromQuaternion(totalRotation); // ����������]�𔽉f
	m_worldMatrix *= Matrix::CreateTranslation(m_position); // �v���C���[�̈ʒu�Ɉړ�

	// ���[���h�s���ݒ�
	m_sword->SetWorldMatrix(m_worldMatrix);
}

// --------------------------------
//  �ʒ��_�̎擾
// --------------------------------
void SwordAttacking1::GetCudgelBothEnds()
{
	// ���{�ƒ��_�̃��[���h���W�����ꂼ��擾
	m_rootPos.push_back(Vector3::Transform(Vector3(0.0f, Sword::MODEL_ROOT_HEIGHT, 0.0f), m_worldMatrix));
	m_tipPos.push_back(Vector3::Transform(Vector3(0.0f, Sword::MODEL_TOP_HEIGHT, 0.0f), m_worldMatrix));

	// �p�[�e�B�N���𐶐�
	CreateSwordParticle();
}

// --------------------------------
//  �a���G�t�F�N�g�̐�������
// --------------------------------
void SwordAttacking1::CreateSwordParticle()
{
	int max = static_cast<int>(m_rootPos.size()) - 1;
	if (max > 1)
	{
		DirectX::VertexPositionTexture ver[4] =
		{
			DirectX::VertexPositionTexture(m_tipPos[max]		,Vector2(0, 0)),	// ����
			DirectX::VertexPositionTexture(m_tipPos[max - 1]	,Vector2(1, 0)),	// �E��
			DirectX::VertexPositionTexture(m_rootPos[max - 1]	,Vector2(1, 1)),	// �E��
			DirectX::VertexPositionTexture(m_rootPos[max]		,Vector2(0, 1)),	// ����
		};
		EventMessenger::Execute(EventList::CreateWeaponTrail, &ver);	// �p�[�e�B�N���̐���
	}
}

// --------------------------------
//  ��ԏI������
// --------------------------------
void SwordAttacking1::PostUpdate()
{
	bool canHit = false;

	// �Փˉ\�t���O��G�S�̂ɕt�^
	EventMessenger::Execute(EventList::EnemyCanHit, &canHit);
}

// --------------------------------
//  �I������
// --------------------------------
void SwordAttacking1::Finalize()
{
}

// --------------------------------
//  �Փˏ����C�x���g
// --------------------------------
void SwordAttacking1::HitAction(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}