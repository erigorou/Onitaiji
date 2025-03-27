/// ---------------------------
///
/// �v���C���[�̌��̑ҋ@���
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
#include "Game/Messenger/EventMessenger.h"

#include "Game/Player/Player.h"
#include "Game/Weapon/Sword/Header/SwordIdling.h"

// -----------------------
// �R���X�g���N�^
// -----------------------
SwordIdling::SwordIdling(Sword* sword)
	:
	m_sword(sword),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity)
{
}

// -----------------------
// �f�X�g���N�^
// -----------------------
SwordIdling::~SwordIdling()
{
}

// -----------------------
// ����������
// -----------------------
void SwordIdling::Initialize()
{
	// ���[���h�s���������
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
}

// -----------------------
// ���O����
// -----------------------
void SwordIdling::PreUpdate()
{
	// �U���t���O�����Z�b�g
	m_sword->SetAttackFlag(false);

	// �G�S�̂��Փ˕s�ɂ���
	bool canHit = false;

	// �Փˉ\�t���O��G�S�̂ɕt�^
	EventMessenger::Execute(EventList::EnemyCanHit, &canHit);
}

// -----------------------
// �X�V����
// -----------------------
void SwordIdling::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	// ���[���h�s��̍X�V����
	UpdateWorldMatrix();
}

// -----------------------
// ���[���h�s��̍X�V����
// -----------------------
void SwordIdling::UpdateWorldMatrix()
{
	using namespace DirectX::SimpleMath;

	// �v���C���[���擾
	auto player = m_sword->GetPlayer();
	// �v���C���[�̌������擾
	float rotation = player->GetAngle();

	// ���̊�b��]�i�����p�x�j
	Quaternion baseRotation =
		Quaternion::CreateFromAxisAngle(Vector3::UnitY, INIT_Y_ROT) *
		Quaternion::CreateFromAxisAngle(Vector3::UnitX, INIT_Z_ROT);

	// �v���C���[�̉�]��K�p
	Quaternion playerRotation = Quaternion::CreateFromAxisAngle(Vector3::UnitY, -rotation);

	// ���[���h�s����X�V
	m_worldMatrix =
		// ���̃X�P�[����K�p
		Matrix::CreateScale(Sword::SWORD_SCALE) *
		// ��{��]��K�p
		Matrix::CreateFromQuaternion(baseRotation) *
		// ������ʒu��K�p
		Matrix::CreateTranslation(Sword::SWORD_DIR_FOR_PLAYER) *
		// �v���C���[�̌�����K�p
		Matrix::CreateFromQuaternion(playerRotation) *
		// �v���C���[�̈ʒu��K�p
		Matrix::CreateTranslation(player->GetPosition());

	// ���Ƀ��[���h�s���ݒ�
	m_sword->SetWorldMatrix(m_worldMatrix);
	// ���̓����蔻��ʒu��ݒ�
	m_sword->SetCollisionPosition(m_worldMatrix);
}

// -----------------------
// ���㏈��
// -----------------------
void SwordIdling::PostUpdate()
{
}

// -----------------------
// �I������
// -----------------------
void SwordIdling::Finalize()
{
}

// -----------------------
// �����蔻�菈��
// -----------------------
void SwordIdling::HitAction(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}