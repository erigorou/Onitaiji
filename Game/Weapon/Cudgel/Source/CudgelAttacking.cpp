// ----------------------------------------------------------
// ���O:	CudgelAttacking
// 
// ���e:	�{�X�S�̕���̋��_�@���������U���̃X�e�[�g
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Cudgel/Header/CudgelAttacking.h"
#include "Game/Weapon/Cudgel/Cudgel.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/Sound/Sound.h"

// -----------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="cudgel">�X�e�[�g�̏��L��</param>
// -----------------------------------------------
CudgelAttacking::CudgelAttacking(Cudgel* cudgel)
	:
	m_cudgel(cudgel),
	m_position{},
	m_velocity{},
	m_angleRL{},
	m_angleUD{},
	m_totalSeconds{},
	m_recordPointTimer{},
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_canGenerateSlamParticles(true)
{
}

// -----------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// -----------------------------------------------
CudgelAttacking::~CudgelAttacking()
{
}

// -----------------------------------------------
/// <summary>
/// ����������
/// </summary>
// -----------------------------------------------
void CudgelAttacking::Initialize()
{
	// ���[���h�s��̏�����
	m_worldMatrix = Matrix::Identity;
}

// -----------------------------------------------
/// <summary>
/// �X�e�[�g�ύX����(in)
/// </summary>
// -----------------------------------------------
void CudgelAttacking::PreUpdate()
{
	// �o�ߎ��Ԃ̏�����
	m_totalSeconds = 0.0f;
	m_angleUD = 0.0f;
	m_canHit = false;
	m_recordPointTimer = 0.0f;

	// ���_���̏�����
	m_rootPos.clear();
	m_tipPos.clear();

	// �p�[�e�B�N���𐶐��\��
	m_canGenerateSlamParticles = true;
	// �����T�E���h���\��
	m_playSound = false;
}

// -----------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -----------------------------------------------
void CudgelAttacking::Update(float elapsedTime)
{
	// ���v���Ԃ��v��
	m_totalSeconds += elapsedTime;
	m_recordPointTimer += elapsedTime;

	// �{�X�̃|�C���^���擾
	auto boss = m_cudgel->GetBoss();
	// �G�̍��W���擾
	m_position = boss->GetPosition();
	// �G�̉�]���擾
	m_enemyAngle = boss->GetAngle();
	// �G�̉�]��ݒ�
	m_angleRL = m_enemyAngle;
	// �A�j���[�V�����̍X�V
	UpdateAnimation();
}

// -----------------------------------------------
/// <summary>
/// �A�j���[�V�����̍X�V����
/// </summary>
// -----------------------------------------------
void CudgelAttacking::UpdateAnimation()
{
	// ���_�̉�]���X�V
	UpdateCudgelRotation();
	// ���_�̃��[���h�s����v�Z
	CalculateModelMatrix();
	// ���_�̍��{�Ɛ�[�̍��W���擾
	GetCudgelBothEnds(m_totalSeconds);

	// �v�Z�������[���h�s���ݒ�
	m_cudgel->SetWorldMatrix(m_worldMatrix);
	m_cudgel->SetCollisionPosition(m_worldMatrix);
}

// -----------------------------------------------
/// <summary>
/// Cudgel�̏c���̉�]�̍X�V�֐�
/// </summary>
// -----------------------------------------------
void CudgelAttacking::UpdateCudgelRotation()
{
	UpdateAttackState();	// �U����Ԃ̍X�V
}

// -----------------------------------------------
/// <summary>
/// �U�肩�����̏����B�����20�x�����グ��B
/// </summary>
/// <param name="t">���K����������</param>
// -----------------------------------------------
void CudgelAttacking::HandleChargePhase(float t)
{
	// 20�x�グ��i0.5�b�ԂŁA�C�[�W���O�g�p�j
	m_angleUD = DirectX::XMConvertToRadians(-CHARGE_ANGLE * Easing::easeInOutBack(t));
}

// -----------------------------------------------
/// <summary>
/// �ҋ@��Ԃ̏����B�����20�x�̊p�x�ŕێ�����B
/// </summary>
// -----------------------------------------------
void CudgelAttacking::HandleWindoupPhase()
{
	// �U�肩�����̊p�x��ێ��i-40�x�̏�Ԃ��ێ��j
	m_angleUD = DirectX::XMConvertToRadians(-CHARGE_ANGLE);
}

// -----------------------------------------------
/// <summary>
/// �U���t�F�[�Y�̏����B�����20�x����95�x�܂ŐU�艺�낷�B
/// </summary>
/// <param name="t">0����1�ɐ��K�����ꂽ���ԁB</param>
// -----------------------------------------------
void CudgelAttacking::HandleAttackPhase(float t)
{
	m_canHit = true;

	// �U�艺�낷�p�x���v�Z����
	m_angleUD = DirectX::XMConvertToRadians(-CHARGE_ANGLE + END_ANGLE * Easing::easeInQuint(t));
	// ����]���v�Z����
	m_angleRL = DirectX::XMConvertToRadians(-INIT_ANGLE * Easing::easeInQuint(t)) + m_angleRL;

	// SE���Đ�����
	if (t > SOUND_TIME && m_playSound == false)
	{
		Sound::PlaySE(Sound::SE_TYPE::BOSS_ATTACK);
		m_playSound = true;
	}
}

// -----------------------------------------------
/// <summary>
/// ���������Ă���ҋ@���郂�[�V����
/// </summary>
// -----------------------------------------------
void CudgelAttacking::KeepStampPhase()
{
	m_canHit = false;

	m_angleUD = DirectX::XMConvertToRadians(ATTACK_ANGLE);
	m_angleRL = DirectX::XMConvertToRadians(-INIT_ANGLE) + m_angleRL;

	// �����������u�ԂɃp�[�e�B�N���̐���
	HandleSlamParticles();
}

// -----------------------------------------------
/// <summary>
/// �ҋ@��Ԃɖ߂鏈���B
/// </summary>
/// <param name="t">���K����������</param>
// -----------------------------------------------
void CudgelAttacking::ReturnToOriginalPhase(float t)
{
	// ���Əc�̉�]�����ɖ߂�
	m_angleUD = DirectX::XMConvertToRadians(ATTACK_ANGLE - ATTACK_ANGLE * t);
	m_angleRL = DirectX::XMConvertToRadians(-INIT_ANGLE + INIT_ANGLE * t) + m_angleRL;
}

// -----------------------------------------------
/// <summary>
/// �㌄�̃p�[�e�B�N����������
/// ����̐�[�ɐo�𔭐������A�J������U��������B
/// </summary>
// -----------------------------------------------
void CudgelAttacking::HandleSlamParticles()
{
	if (m_canGenerateSlamParticles)
	{
		m_canGenerateSlamParticles = false;

		// �p�[�e�B�N���̐���
		EventMessenger::Execute(EventList::CreateBashDust, (&m_tipPos[m_tipPos.size() - 1]));

		// �J�����̐U����ݒ�
		float m_shakePower = 1.5f;
		EventMessenger::Execute(EventList::ShakeCamera, &m_shakePower);
	}
}

// -----------------------------------------------
/// <summary>
/// �X�V���鏈��
/// </summary>
// -----------------------------------------------
void CudgelAttacking::UpdateAttackState()
{
	// ������������̑ҋ@���[�V����
	if (m_totalSeconds < CHARGE_TIME) HandleChargePhase(m_totalSeconds / CHARGE_TIME);
	// �U���O�̃��[�V����
	else if (Math::InTime(CHARGE_ANGLE, m_totalSeconds, WINDUP_TIME)) HandleWindoupPhase();
	// �U�����[�V����
	else if (Math::InTime(WINDUP_TIME, m_totalSeconds, ATTACK_TIME)) HandleAttackPhase((m_totalSeconds - WINDUP_TIME) / (ATTACK_TIME - WINDUP_TIME));
	// ������������̑ҋ@���[�V����
	else if (Math::InTime(ATTACK_TIME, m_totalSeconds, STOP_TIME))	KeepStampPhase();
	// �߂�A�j���[�V����
	else if (Math::InTime(STOP_TIME, m_totalSeconds, RETURN_TIME)) ReturnToOriginalPhase((m_totalSeconds - STOP_TIME) / (RETURN_TIME - STOP_TIME));

	// �v���C���[�ɍU���\����ʒm
	EventMessenger::Execute(EventList::PlayerCanDamageCudgel, &m_canHit);
}

// -----------------------------------------------
/// <summary>
/// �`��p���[���h�s����v�Z����֐�
/// </summary>
// -----------------------------------------------
void CudgelAttacking::CalculateModelMatrix()
{
	// �T�C�Y�̐ݒ� & ������
	m_worldMatrix = Matrix::CreateScale(Cudgel::CUDGEL_SCALE);
	m_worldMatrix
		// �����ʒu�ւ̈ړ�
		*= Matrix::CreateTranslation(CudgelAttacking::ZERO_DIREC)
		// �U�����[�V�������̌v�Z
		*= CalculateAttackMatrix();
}

// -----------------------------------------------
/// <summary>
/// Cudgel�̃��[���h�s����v�Z����֐�
/// </summary>
/// <returns>�U�����[�V��������Cudgel�̉�]���[���h�s��</returns>
// -----------------------------------------------
DirectX::SimpleMath::Matrix CudgelAttacking::CalculateAttackMatrix()
{
	return
		// �c��]���s��
		Matrix::CreateRotationX(-m_angleUD)
		// ����]���s��
		*= Matrix::CreateRotationY(-m_angleRL)
		// �r�̒������ړ�
		*= Matrix::CreateTranslation(CudgelAttacking::ARM_LENGTH)
		// �Ō�ɓG�̈ʒu�ɐݒ�
		*= Matrix::CreateTranslation(m_position);
}

// -----------------------------------------------
/// <summary>
/// �G�t�F�N�g�ȂǂɎg�p������_�̍��{�ƒ��_�̍��W���擾����֐�
/// </summary>
/// <param name="_elapsedTime">�o�ߎ���</param>
// -----------------------------------------------
void CudgelAttacking::GetCudgelBothEnds(float _totalTime)
{
	UNREFERENCED_PARAMETER(_totalTime);

	DirectX::SimpleMath::Vector3 root;
	DirectX::SimpleMath::Vector3 tip;

	// ���f���̍��{�̈ʒu���擾
	Matrix rootMat = Matrix::CreateTranslation(CudgelAttacking::ZERO_DIREC);
	rootMat
		*= Matrix::CreateTranslation(Cudgel::CUDGEL_HADLE_POS)
		*= CalculateAttackMatrix();
	root = Vector3::Transform(Vector3::Zero, rootMat);

	// ���f���̐�[�̈ʒu���擾
	Matrix tipMat = Matrix::CreateTranslation(CudgelAttacking::ZERO_DIREC);
	tipMat
		*= Matrix::CreateTranslation(Cudgel::CUDGEL_LENGTH)
		*= CalculateAttackMatrix();
	tip = Vector3::Transform(Vector3::Zero, tipMat);

	m_recordPointTimer = 0.0f;
	// ���{���W���X�g�̐�[�ɋL�^
	m_rootPos.push_back(root);
	// ���_���W���X�g�̐�[�ɋL�^
	m_tipPos.push_back(tip);

	using namespace DirectX;

	// 2�ȏ�Ȃ��ꍇ�͏����𔲂���
	int max = static_cast<int>(m_rootPos.size()) - 1;
	if (max >= 1)
	{
		// ���_���̐����i�p�[�e�B�N���̐����ɕK�v�j
		VertexPositionTexture ver[4] =
		{
			// ����
			VertexPositionTexture(m_tipPos[max] ,Vector2(0, 0)),
			// �E��
			VertexPositionTexture(m_tipPos[max - 1]	,Vector2(1, 0)),
			// �E��
			VertexPositionTexture(m_rootPos[max - 1] ,Vector2(1, 1)),
			// ����
			VertexPositionTexture(m_rootPos[max] ,Vector2(0, 1)),
		};
		// �p�[�e�B�N���̐���
		EventMessenger::Execute(EventList::CreateWeaponTrail, &ver);
	}
}

// -----------------------------------------------
/// <summary>
/// ���㏈��
/// </summary>
// -----------------------------------------------
void CudgelAttacking::PostUpdate()
{
}

// -----------------------------------------------
/// <summary>
/// �I������
/// </summary>
// -----------------------------------------------
void CudgelAttacking::Finalize()
{
}

// -----------------------------------------------
/// <summary>
/// �Փ˃C�x���g
/// </summary>
/// <param name="data">����̃f�[�^</param>
// -----------------------------------------------
void CudgelAttacking::HitAction(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}