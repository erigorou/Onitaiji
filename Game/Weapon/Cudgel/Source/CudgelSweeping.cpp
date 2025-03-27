// ----------------------------------------------------------
// ���O:	CudgeSweeping
// 
// ���e:	�{�X�S�̕���̋��_�@�ガ�����̃X�e�[�g
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Sound/Sound.h"
#include "Game/Weapon/WeaponState.h"
#include "Game/Boss/Boss.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Weapon/Cudgel/Header/CudgelSweeping.h"
#include "Game/Weapon/Cudgel/Cudgel.h"

// -----------------------------
// �R���X�g���N�^
// -----------------------------
CudgelSweeping::CudgelSweeping(Cudgel* cudgel)
	:
	m_cudgel(cudgel),
	m_position{},
	m_velocity{},
	m_angleRL{},
	m_angleUD{},
	m_parentAngleRL{},
	m_totalSeconds{},
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_playSound(false),
	m_playerCanHit(false)
{
}

// ----------------------------
// �f�X�g���N�^
// ----------------------------
CudgelSweeping::~CudgelSweeping()
{
}

// ----------------------------
// ����������
// ----------------------------
void CudgelSweeping::Initialize()
{
	// �{�X�̐ݒ�
	m_boss = m_cudgel->GetBoss();
}

// -----------------------------
// ���O����
// -----------------------------
void CudgelSweeping::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;
	// ���_�����ɂ���
	m_angleUD = DirectX::XMConvertToRadians(INITIAL_ROTATE_UD);
	// ����]�̏�����
	m_angleRL = 0.0f;
	// �e�̊p�x���擾
	m_parentAngleRL = m_boss->GetAngle();
	// �G�t�F�N�g�p�̒��_����������
	m_rootPos.clear();
	// �G�t�F�N�g�p�̒��_����������
	m_tipPos.clear();
	// �T�E���h�̍Đ��t���O��false�ɂ���
	m_playSound = false;
}

// --------------------------------
// �X�V����
// --------------------------------
void CudgelSweeping::Update(float elapsedTime)
{
	// ���v���Ԃ��v��
	m_totalSeconds += elapsedTime;

	// �A�j���[�V�������X�V����
	UpdateCudgelRotation();

	// ���[���h�s����v�Z
	CalculateModelMatrix();
	// ���[���擾����
	GetCudgelBothEnds();

	// ���[���h�s���ݒ肷��
	m_cudgel->SetWorldMatrix(m_worldMatrix);
	// �����蔻��p�̍s����擾
	m_collMatrix = m_worldMatrix;
	// �����蔻��̈ʒu�𒲐�����
	m_collMatrix._42 = 0.0f;
	m_cudgel->SetCollisionPosition(m_collMatrix);
}

// ------------------------------
// Cudgel�̏c���̉�]�̍X�V�֐�
// ------------------------------
void CudgelSweeping::UpdateCudgelRotation()
{
	// �G�̍��W���擾
	m_position = m_boss->GetPosition();
	// ���x���Ńt���O��false�ɂ���
	m_playerCanHit = false;

	// ���߃��[�V����
	ChargeAnimation();
	// �U�����[�V����
	AttackAnimation();
	// �I�����[�V����
	EndAnimation();
	// �v���C���[�ɍU���\����ʒm
	EventMessenger::Execute(EventList::PlayerCanDamageCudgel, &m_playerCanHit);
}

// --------------------------------
// ���߃��[�V����
// --------------------------------
void CudgelSweeping::ChargeAnimation()
{
	// �U���O�̒��߂�A�j���[�V�������s��
	if (m_totalSeconds <= CHARGE_TIME)
	{
		// �b���𐳋K��
		float easing = m_totalSeconds / CHARGE_TIME;
		// �C�[�W���O���|������]�p���v�Z
		m_angleRL = -CHARGE_ROTATE_ANGLE * Easing::easeOutCirc(easing);
	}
}

// --------------------------------
// �U�����[�V����
// --------------------------------
void CudgelSweeping::AttackAnimation()
{
	// �U�����[�V����
	if (Math::InTime(WINDUP_TIME, m_totalSeconds, ATTACK_TIME))
	{
		// �U���\��ʒm
		bool attack = true;
		EventMessenger::Execute(EventList::PlayerCanDamageCudgel, &attack);

		// �b���̐��K��
		float easing = (m_totalSeconds - WINDUP_TIME) / (ATTACK_TIME - WINDUP_TIME);
		// �C�[�W���O���|������]���v�Z
		m_angleRL = CHARGE_ROTATE_ANGLE + WINDUP_ROTATE_ANGLE * Easing::easeOutBack(easing);
		// �v���C���[�ɍU���\����ʒm
		m_playerCanHit = true;
		// SE�̍Đ�
		if (m_playSound == false)
		{
			// 1�x�����Đ�����
			Sound::PlaySE(Sound::SE_TYPE::BOSS_SWEEP);
			m_playSound = true;
		}
	}
}

// ---------------------------------
// �A�j���[�V�����I��
// ---------------------------------
void CudgelSweeping::EndAnimation()
{
	if (m_totalSeconds > END_TIME)
	{
		// �U���s��ʒm
		bool attack = false;
		EventMessenger::Execute(EventList::PlayerCanDamageCudgel, &attack);

		// �X�e�[�g��ύX
		CudgelState state = CudgelState::Idle;
		EventMessenger::Execute(EventList::ChangeCudgelState, &state);
	}
}

// ----------------------------------
// �`��p���[���h�s����v�Z����֐�
// ----------------------------------
void CudgelSweeping::CalculateModelMatrix()
{
	m_worldMatrix = Matrix::CreateScale(Cudgel::CUDGEL_SCALE);		// �T�C�Y�̐ݒ� & ������
	m_worldMatrix
		*= Matrix::CreateTranslation(CudgelSweeping::ZERO_DIREC)	// �����ʒu�ւ̈ړ�
		*= CalculateAttackMatrix();									// �U�����[�V�������̌v�Z
}

// ----------------------------------------
// Cudgel�̃��[���h�s����v�Z����֐�
// ----------------------------------------
DirectX::SimpleMath::Matrix CudgelSweeping::CalculateAttackMatrix()
{
	return
		// �c��]���s��
		Matrix::CreateRotationX(-m_angleUD)
		// ����]���s��
		*= Matrix::CreateRotationY(DirectX::XMConvertToRadians(-m_angleRL) - m_parentAngleRL - DirectX::XMConvertToRadians(180))
		// �r�̒������ړ�
		*= Matrix::CreateTranslation(CudgelSweeping::ARM_LENGTH)
		// �Ō�ɓG�̈ʒu�ɐݒ�
		*= Matrix::CreateTranslation(m_position);
}

// ----------------------------------------------------
// ���_�̍��{�ƒ��_�̍��W���擾����֐�
// ----------------------------------------------------
void CudgelSweeping::GetCudgelBothEnds()
{
	DirectX::SimpleMath::Vector3 root;
	DirectX::SimpleMath::Vector3 tip;

	// ���f���̍��{�̈ʒu���擾
	Matrix rootMat = Matrix::CreateTranslation(CudgelSweeping::ZERO_DIREC);
	rootMat
		*= Matrix::CreateTranslation(Cudgel::CUDGEL_HADLE_POS)
		*= CalculateAttackMatrix();
	root = Vector3::Transform(Vector3::Zero, rootMat);

	// ���f���̐�[�̈ʒu���擾
	Matrix tipMat = Matrix::CreateTranslation(CudgelSweeping::ZERO_DIREC);
	tipMat
		*= Matrix::CreateTranslation(Cudgel::CUDGEL_LENGTH)
		*= CalculateAttackMatrix();
	tip = Vector3::Transform(Vector3::Zero, tipMat);

	// ���{���W���X�g�̐�[�ɋL�^
	m_rootPos.push_back(root);
	// ���_���W���X�g�̐�[�ɋL�^
	m_tipPos.push_back(tip);

	// 2�ȏ�Ȃ��ꍇ�͏����𔲂���
	int max = static_cast<int>(m_rootPos.size() - 1);
	if (max >= 1)
	{
		// ���_���̐����i�p�[�e�B�N���̐����ɕK�v�j
		DirectX::VertexPositionTexture ver[4] =
		{
			// ����
			DirectX::VertexPositionTexture(m_tipPos[max] ,DirectX::SimpleMath::Vector2(0, 0)),
			// �E��
			DirectX::VertexPositionTexture(m_tipPos[max - 1]  ,DirectX::SimpleMath::Vector2(1, 0)),
			// �E��
			DirectX::VertexPositionTexture(m_rootPos[max - 1] ,DirectX::SimpleMath::Vector2(1, 1)),
			// ����
			DirectX::VertexPositionTexture(m_rootPos[max] ,DirectX::SimpleMath::Vector2(0, 1)),
		};
		// �p�[�e�B�N���̐���
		EventMessenger::Execute(EventList::CreateWeaponTrail, &ver);
	}
}

// ------------------------
// ��ԍX�V����
// ------------------------
void CudgelSweeping::PostUpdate()
{
}

// ------------------------
// �I������
// ------------------------
void CudgelSweeping::Finalize()
{
}

// ------------------------
// �Փ˔���
// ------------------------
void CudgelSweeping::HitAction(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}