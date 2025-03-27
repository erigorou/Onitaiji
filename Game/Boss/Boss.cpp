// -----------------------------------------------------
// ���O:	Boss.cpp
// ���e:	�{�X����������N���X
//			�X�e�[�g��Փ˔�����Ǘ�
// �쐬:	�r�c����
// -----------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/Math.h"
#include "../HitStop/HitStop.h"
#include "Game/GameResources.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Cudgel/Cudgel.h"
#include "Interface/IState.h"
#include "Game/Factory/Factory.h"
#include "Effects/EnemyEffect/EnemyEffect.h"
// �X�e�[�g
#include "States/Header/BossStarting.h"
#include "States/Header/BossIdling.h"
#include "States/Header/BossAttacking.h"
#include "States/Header/BossSweeping.h"
#include "States/Header/BossDashAttacking.h"
#include "States/Header/BossApproaching.h"
#include "States/Header/BossDead.h"
// ��
#include "Face/Header/BossFaceIdling.h"
#include "Face/Header/BossFaceAttacking.h"

// --------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// --------------------------------
Boss::Boss()
	:
	m_worldMatrix{ DirectX::SimpleMath::Matrix::Identity },
	m_currentState{}
	, m_idling{}
	, m_attacking{}
	, m_approaching{}
	, m_position{}
	, m_angle{}
	, m_bodyTilt{}
	, m_pushBackValue{}
	, m_canHit(false)
	, m_shakePower{ SHAKE_POWER }
	, m_currentFace{}
	, m_model{}
{
}

// --------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------
Boss::~Boss()
{
	m_idling->Finalize();
	m_attacking->Finalize();
	m_approaching->Finalize();
	m_dead->Finalize();
	m_dashAttacking->Finalize();
}

// --------------------------------
/// <summary>
/// ����������
/// </summary
// --------------------------------
void Boss::Initialize()
{
	// ����̐���
	m_cudgel = Factory::CreateCudgel(this);
	// ���f�����擾
	m_model = GameResources::GetInstance()->GetModel("boss");
	// HP��ݒ�
	m_hp = std::make_unique<HPSystem>(HP);
	// �X�e�[�g�̍쐬
	CreateState();
	// ��p�[�c�̐���
	CreateFace();
	// �G�t�F�N�g�̐���
	m_effect = std::make_unique<EnemyEffect>();
	// �����蔻��̍쐬
	CreateCollision();
	// �C�x���g�̓o�^
	AttachEvent();
}

// --------------------------------
/// <summary>
/// �X�e�[�g�̐�������
/// </summary>
// --------------------------------
void Boss::CreateState()
{
	// �J�n
	m_starting = std::make_unique<BossStarting>(this);
	m_starting->Initialize();
	m_states.push_back(m_starting.get());

	// �ҋ@
	m_idling = std::make_unique<BossIdling>(this);
	m_idling->Initialize();
	m_states.push_back(m_idling.get());

	// �U��
	m_attacking = std::make_unique<BossAttacking>(this);
	m_attacking->Initialize();
	m_states.push_back(m_attacking.get());

	// �ガ����
	m_sweeping = std::make_unique<BossSweeping>(this);
	m_sweeping->Initialize();
	m_states.push_back(m_sweeping.get());

	// �ˌ�
	m_dashAttacking = std::make_unique<BossDashAttacking>(this);
	m_dashAttacking->Initialize();
	m_states.push_back(m_dashAttacking.get());

	// �ǔ�
	m_approaching = std::make_unique<BossApproaching>(this);
	m_approaching->Initialize();
	m_states.push_back(m_approaching.get());

	// ���S
	m_dead = std::make_unique<BossDead>(this);
	m_dead->Initialize();
	m_states.push_back(m_dead.get());

	// �����̃X�e�[�g��ҋ@��ԂɊ��蓖�Ă�
	m_currentState = m_starting.get();
}

// --------------------------------
/// <summary>
/// ��̐�������
/// </summary>
// --------------------------------
void Boss::CreateFace()
{
	// �ʏ���
	m_faceIdling = std::make_unique<BossFaceIdling>(this);
	m_faces.push_back(m_faceIdling.get());
	// �U�����
	m_faceAttacking = std::make_unique<BossFaceAttacking>(this);
	m_faces.push_back(m_faceAttacking.get());
	// �����̊��ҋ@��Ɋ��蓖�Ă�
	m_currentFace = m_faceIdling.get();
}

// --------------------------------
/// <summary>
/// �����蔻��̐�������
/// </summary>
// --------------------------------
void Boss::CreateCollision()
{
	// �����蔻��̐���
	m_bodyCollision = std::make_unique<DirectX::BoundingSphere>(m_position, BOSS_SCALE * COLLISION_RADIUS);

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingSphere> data =
	{
		ObjectType::Boss,		// �I�u�W�F�N�g�̎��
		CollisionType::Sphere,	// �����蔻��̎��
		this,					// ���̃N���X�̃|�C���^
		m_bodyCollision.get()	// �����蔻��̃|�C���^
	};

	// �Փ˔����Manager�ɓo�^
	EventMessenger::Execute(EventList::AddSphereCollision, &data);
}

// --------------------------------
/// <summary>
/// �X�e�[�g�̍X�V����
/// </summary>
/// <param name="state">���̃X�e�[�g</param>
// --------------------------------
void Boss::ChangeState(void* state)
{
	// int�^�ɕϊ�
	int index = *static_cast<int*>(state);

	// �X�e�[�g�̕ύX
	if (m_currentState == m_states[index]) return;

	// �V�K�̏�ԑJ�ڑO�Ɏ���X�V���s��
	m_currentState->PostUpdate();
	// �V�K�̏�Ԃ����݂̏�Ԃɐݒ肷��
	m_currentState = m_states[index];
	// �V�K�̏�ԑJ�ڌ�Ɏ��O�X�V���s��
	m_currentState->PreUpdate();
}

// --------------------------------
/// <summary>
/// ��̕ύX����
/// </summary>
/// <param name="face">���̊�</param>
// --------------------------------
void Boss::ChangeFace(void* face)
{
	// int�^�ɕϊ�
	int index = *static_cast<int*>(face);
	// �V�K�̏�Ԃ����݂̏�Ԃɐݒ肷��
	m_currentFace = m_faces[index];
}

// --------------------------------
/// <summary>
/// �C�x���g�̓o�^
/// </summary>
// --------------------------------
void Boss::AttachEvent()
{
	// ��ԕύX�̃C�x���g
	EventMessenger::Attach(EventList::ChangeBossState, std::bind(&Boss::ChangeState, this, std::placeholders::_1));
	// ��ύX�̃C�x���g
	EventMessenger::Attach(EventList::ChangeBossFace, std::bind(&Boss::ChangeFace, this, std::placeholders::_1));
}

// --------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// --------------------------------
void Boss::Update(float elapsedTime)
{
	// �X�e�[�^�X�̍X�V����
	m_currentState->Update(elapsedTime);
	// �G�t�F�N�g�̍X�V
	m_effect->Update(elapsedTime);
	// ���[���h�s��̌v�Z
	CalcrationWorldMatrix();
	// �����蔻��̍X�V
	m_bodyCollision->Center = DirectX::SimpleMath::Vector3(m_position.x, m_position.y + COLISION_POS_Y, m_position.z);
	// �����m�F
	CheckAlive();
	// ����̍X�V
	m_cudgel->Update(elapsedTime);

#ifdef _DEBUG

	// �f�o�b�O���Ȃ� F1~F3�ŃX�e�[�g��ύX
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();

	if (keyboardState.F1) {
		BossState state = BossState::Attacking;
		ChangeState(&state);
	}
	if (keyboardState.F2) {
		BossState state = BossState::Sweeping;
		ChangeState(&state);
	}
	if (keyboardState.F3) {
		BossState state = BossState::DashAttacking;
		ChangeState(&state);
	}

#endif // _DEBUG
}

// --------------------------------
/// <summary>
/// ���[���h�s��̌v�Z
/// </summary>
// --------------------------------
void Boss::CalcrationWorldMatrix()
{
	using namespace DirectX::SimpleMath;

	// �{�X�̉�]�iX���̌X�� + Y����]�j
	Quaternion bodyTiltRotation = Quaternion::CreateFromYawPitchRoll(
		-m_angle + DirectX::XMConvertToRadians(180.f),
		m_bodyTilt,
		0.0f
	);

	// ��]�s��̓K�p
	m_worldMatrix = Matrix::CreateFromQuaternion(bodyTiltRotation);

	// �ړ���K�p�i���x����]��̕����ɕϊ��j
	m_velocity *= Boss::BOSS_SPEED;
	m_position += Vector3::Transform(m_velocity, m_worldMatrix);

	// �X�P�[���ƕ��s�ړ���K�p
	m_worldMatrix *= Matrix::CreateScale(BOSS_SCALE);	// �T�C�Y����
	m_worldMatrix *= Matrix::CreateTranslation(m_position);	// �ʒu�ݒ�
}

// --------------------------------
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
// --------------------------------
void Boss::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// �`��ɕK�v�ȃf�[�^���擾����
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// �[�x�l���Q�Ƃ��ď�������
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	// ��̕`��
	m_currentFace->DrawFace(m_worldMatrix, view, projection);
	// �_���[�W�̃G�t�F�N�g��t�^
	m_effect->DrawWithEffect(m_model, m_worldMatrix, view, projection);
	// ���_�̕`��
	m_cudgel->Render(view, projection);
}

// --------------------------------
/// <summary>
/// �I������
/// </summary>
// --------------------------------
void Boss::Finalize()
{
	// �폜�p�Փ˔���̃f�[�^���쐬
	DeleteCollisionData data = { CollisionType::Sphere, this };
	// �폜�C�x���g�����s
	EventMessenger::Execute(EventList::DeleteCollision, &data);
}

// --------------------------------
/// <summary>
/// �Փ˔���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// --------------------------------
void Boss::HitAction(InterSectData data)
{
	HitSword(data);
	HitStage(data);
}


// --------------------------------
/// <summary>
/// ���Ƃ̏Փ˔���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// --------------------------------
void Boss::HitSword(InterSectData data)
{
	if (
		m_canHit &&
		data.objType == ObjectType::Sword &&
		data.colType == CollisionType::OBB)
	{
		m_hp->Damage(1);
		m_canHit = false;

		// �q�b�g�X�g�b�v��L���ɂ���
		HitStop::GetInstance()->SetActive();
		// �G�t�F�N�g���Đ�
		m_effect->SetEffect(EnemyEffect::ENEMY_EFFECT::DAMAGE);

		// ��ʂ�h�炷
		EventMessenger::Execute(EventList::ShakeCamera, &m_shakePower);
	}
}


// --------------------------------
/// <summary>
/// �X�e�[�W�Ƃ̏Փ˔���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// --------------------------------
void Boss::HitStage(InterSectData data)
{
	if (data.objType == ObjectType::Stage && data.colType == CollisionType::Sphere)
	{
		m_pushBackValue = DirectX::SimpleMath::Vector3::Zero;

		// �����߂��ʂ��v�Z
		m_pushBackValue += Math::pushFront_BoundingSphere(*m_bodyCollision.get(), *data.collision);
		// y���W�ɂ͔��f�����ɐݒ�
		m_pushBackValue.y = 0.0f;
		// �G�̈ʒu�������߂�
		m_position += m_pushBackValue;
		m_bodyCollision->Center = m_position;
	}
}

// --------------------------------
/// <summary>
/// ��������
/// </summary>
// --------------------------------
void Boss::CheckAlive()
{
	// HP��0�ȉ��ɂȂ�����
	if (m_hp->GetHP() <= 0)
	{
		// ���S��ԂɕύX
		BossState state = BossState::Dead;
		ChangeState(&state);

		// ���_���\����
		m_cudgel->BossDead();
	}
}

// --------------------------------
/// <summary>
/// ���S���̏���
/// </summary>
// --------------------------------
void Boss::DeadAction()
{
}