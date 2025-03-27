// -----------------------------------------------------
// ���O:	Goblin.cpp
// ���e:	���S����������N���X
//			�X�e�[�g��Փ˔�����Ǘ�
// �쐬:	�r�c����
// -----------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Goblin.h"
#include "Libraries/MyLib/Math.h"
#include "Interface/IState.h"
#include "Game/Data/HPSystem.h"
#include "Game/GameResources.h"
#include "../Boss/Boss.h"
#include "Effects/EnemyEffect/EnemyEffect.h"
#include "Game/HitStop/HitStop.h"
#include "Game/Messenger/EventMessenger.h"
#include "State/Header/GoblinIdling.h"
#include "State/Header/GoblinAttacking.h"
#include "State/Header/GoblinDead.h"
#include "State/Header/GoblinTutorial.h"

// ---------------
// �Œ�l
// ---------------
const float Goblin::GOBLIN_SPEED = Boss::BOSS_SPEED / 2.0f;	// �ړ���
const float Goblin::GOBLIN_SCALE = Boss::BOSS_SCALE / 4.0f;	// �T�C�Y

// -------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// -------------------------------------------------------
Goblin::Goblin()
	:
	m_position{},
	m_velocity{},
	m_angle{},
	m_scale{ 1.0f, 1.0f, 1.0f },
	m_worldMatrix{ DirectX::SimpleMath::Matrix::Identity },
	m_model{ nullptr },
	m_nowAttacking{ false },
	m_pushBackValue{},
	m_isHit{ false },
	m_canHit{ false },
	m_coolTime{}
{
}

// -------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// -------------------------------------------------------
Goblin::~Goblin()
{
}

// -------------------------------------------------------
/// <summary>
/// �������֐�
/// </summary>
// -------------------------------------------------------
void Goblin::Initialize()
{
	// ���f���̓ǂݍ���
	m_model = GameResources::GetInstance()->GetModel("goblin");

	// �X�e�[�g�̍쐬
	CreateState();
	// �����蔻��̐���
	CreateCollision();
	// HP�̐���
	m_hp = std::make_unique<HPSystem>(GOBLIN_HP);
	// �G�t�F�N�g�̐���
	m_enemyEffect = std::make_unique<EnemyEffect>();
}

// -------------------------------------------------------
/// <summary>
/// �X�e�[�g�쐬
/// </summary>
// -------------------------------------------------------
void Goblin::CreateState()
{
	// �ҋ@
	m_idling = std::make_unique<GoblinIdling>(this);
	m_idling->Initialize();
	m_states.push_back(m_idling.get());

	// �U��
	m_attacking = std::make_unique<GoblinAttacking>(this);
	m_attacking->Initialize();
	m_states.push_back(m_attacking.get());

	// ���S
	m_dead = std::make_unique<GoblinDead>(this);
	m_dead->Initialize();
	m_states.push_back(m_dead.get());

	// �`���[�g���A��
	m_tutorial = std::make_unique<GoblinTutorial>(this);
	m_tutorial->Initialize();
	m_states.push_back(m_tutorial.get());

	// �����X�e�[�g��ҋ@��Ԃ�
	m_currentState = m_idling.get();
}

// -------------------------------------------------------
/// <summary>
/// �����蔻��쐬
/// </summary>
// -------------------------------------------------------
void Goblin::CreateCollision()
{
	// �����蔻��̐���
	m_bodyCollision = std::make_unique<DirectX::BoundingSphere>(m_position, GOBLIN_SCALE * COLLISION_RADIUS);

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingSphere> data =
	{
		ObjectType::Goblin,		// �I�u�W�F�N�g�̎��
		CollisionType::Sphere,	// �����蔻��̎��
		this,					// ���̃N���X�̃|�C���^
		m_bodyCollision.get()	// �����蔻��̃|�C���^
	};

	// �Փ˔����Manager�ɓo�^
	EventMessenger::Execute(EventList::AddSphereCollision, &data);
}

// -------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -------------------------------------------------------
void Goblin::Update(const float elapsedTime)
{
	// ���[���h�s��̏�����
	CalcWorldMatrix();
	// �G�t�F�N�g�̍X�V
	m_enemyEffect->Update(elapsedTime);
	// �Փ˔���̈ړ�
	MoveCollision();
	// �N�[���^�C���̃J�E���g
	CountCoolTime(elapsedTime);
	// �����m�F
	CheckAlive();

	// �X�e�[�g�̍X�V����
	m_currentState->Update(elapsedTime);
}

// -------------------------------------------------------
/// <summary>
/// ���[���h�s��̌v�Z
/// </summary>
// -------------------------------------------------------
void Goblin::CalcWorldMatrix()
{
	// ��]�̍쐬
	Quaternion rotation = Quaternion::CreateFromYawPitchRoll(
		m_angle,
		0.0f,
		0.0f
	);

	// ��]�s��̍쐬
	m_worldMatrix = Matrix::CreateFromQuaternion(rotation);

	// �X�P�[���ƕ��s�ړ���K�p
	m_worldMatrix *= Matrix::CreateScale(GOBLIN_SCALE * m_scale);	// �X�P�[���K�p
	m_worldMatrix *= Matrix::CreateTranslation(m_position);		// �ʒu�K�p
}

// -------------------------------------------------------
/// <summary>
/// �Փ˔���̈ړ�
/// </summary>
// -------------------------------------------------------
void Goblin::MoveCollision()
{
	// �Փ˔���̍��W�𓮂������W�ɍ��킹��
	DirectX::SimpleMath::Vector3 pos = m_position;
	pos.y = COLLISION_POS_Y;
	m_bodyCollision->Center = pos;
}

// -------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
// -------------------------------------------------------
void Goblin::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_enemyEffect->DrawWithEffect(m_model, m_worldMatrix, view, projection);
}

// -------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// -------------------------------------------------------
void Goblin::Finalize()
{
	m_idling->Finalize();
	m_attacking->Finalize();
	m_dead->Finalize();

	// �폜�p�Փ˔���̃f�[�^���쐬
	DeleteCollisionData data = { CollisionType::Sphere, this };

	// �폜�C�x���g�����s
	EventMessenger::Execute(EventList::DeleteCollision, &data);
}

// -------------------------------------------------------
/// <summary>
/// ���������Ƃ��̏���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// -------------------------------------------------------
void Goblin::HitAction(InterSectData data)
{
	switch (data.objType)
	{
	case ObjectType::Player:	HitPlayer(data);	break;
	case ObjectType::Goblin:	HitGoblin(data);	break;
	case ObjectType::Boss:		HitBoss(data);		break;
	case ObjectType::Stage:		HitStage(data);		break;
	case ObjectType::Sword:		HitSword(data);		break;
	}
}

// -------------------------------------------------------
/// <summary>
/// �v���C���[�ɓ��������Ƃ��̏���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// -------------------------------------------------------
void Goblin::HitPlayer(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}

// -------------------------------------------------------
/// <summary>
/// ���S�ɓ��������Ƃ��̏���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// -------------------------------------------------------
void Goblin::HitGoblin(InterSectData data)
{
	// �Փ˂����I�u�W�F�N�g�̏����擾
	auto goblinCollision = *m_bodyCollision.get();
	auto goblinCollision2 = *data.collision;

	// �����߂��ʂ��v�Z
	m_pushBackValue = Math::pushBack_BoundingSphere(goblinCollision, goblinCollision2) / 2.0f;
	m_pushBackValue.y = 0.0f;
	// �v���C���[�̈ʒu�������߂�
	m_position += m_pushBackValue;
	m_bodyCollision->Center = m_position;
}

// -------------------------------------------------------
/// <summary>
/// �G�ɓ��������Ƃ��̏���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// -------------------------------------------------------
void Goblin::HitBoss(InterSectData data)
{
	m_pushBackValue = DirectX::SimpleMath::Vector3::Zero;

	// �Փ˂����I�u�W�F�N�g�̏����擾
	auto goblinCollision = *m_bodyCollision.get();
	auto enemyCollision = *data.collision;

	// �����߂��ʂ��v�Z
	m_pushBackValue += Math::pushBack_BoundingSphere(goblinCollision, enemyCollision);
	m_pushBackValue.y = 0.0f;

	m_position += m_pushBackValue;
	m_bodyCollision->Center = m_position;
}

// -------------------------------------------------------
/// <summary>
/// �X�e�[�W�ɓ��������Ƃ��̏���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// -------------------------------------------------------
void Goblin::HitStage(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}

// -------------------------------------------------------
/// <summary>
/// ���ɓ��������Ƃ��̏���
/// </summary>
/// <param name="data">�Փ˃f�[�^</param>
// -------------------------------------------------------
void Goblin::HitSword(InterSectData data)
{
	// �Փˉ\�łȂ��ꍇ�͏������s��Ȃ�
	if (!m_canHit) return;
	m_canHit = false;

	UNREFERENCED_PARAMETER(data);
	Damaged(1);
}

// -------------------------------------------------------
/// <summary>
/// �X�e�[�g�̕ύX
/// </summary>
/// <param name="state">�ύX����X�e�[�g</param>
// -------------------------------------------------------
void Goblin::ChangeState(GoblinState state)
{
	// ��������X�e�[�g�̃C���f�b�N�X���擾
	int index = static_cast<int>(state);

	// �X�e�[�g�����݂��Ȃ��ꍇ�͏������s��Ȃ�
	if (m_currentState == m_states[index]) return;

	// �X�e�[�g�̏I������
	m_currentState->PostUpdate();
	// �X�e�[�g�̕ύX
	m_currentState = m_states[index];
	// �X�e�[�g�̏�����
	m_currentState->PreUpdate();
}

// -------------------------------------------------------
/// <summary>
/// �_���[�W���󂯂��Ƃ��̏���
/// </summary>
/// <param name="damage">�󂯂�_���[�W��</param>
// -------------------------------------------------------
void Goblin::Damaged(float damage)
{
	// ���łɃ_���[�W���󂯂Ă���ꍇ�͏������s��Ȃ�
	if (m_isHit)return;
	// HP�����炷
	m_hp->Damage(damage);
	// �q�b�g�X�g�b�v��L���ɂ���
	HitStop::GetInstance()->SetActive();
	// �G�t�F�N�g���Đ�
	m_enemyEffect->SetEffect(EnemyEffect::ENEMY_EFFECT::DAMAGE);

	// ��ʂ�h�炷
	float shakePower = 0.25f;
	EventMessenger::Execute(EventList::ShakeCamera, &shakePower);

	// �N�[���^�C����L���ɂ���
	m_isHit = true;
}

// -------------------------------------------------------
/// <summary>
/// �N�[���^�C���̃J�E���g
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -------------------------------------------------------
void Goblin::CountCoolTime(float elapsedTime)
{
	// �ߋ��ɍU�����󂯂Ă��Ȃ��ꍇ�͏������s��Ȃ�
	if (!m_isHit)return;

	// �N�[���^�C�����J�E���g
	m_coolTime += elapsedTime;

	if (m_coolTime > COOL_TIME)
	{
		m_isHit = false;
		m_coolTime = 0.0f;
	}
}

// -------------------------------------------------------
/// <summary>
/// �����m�F
/// </summary>
// -------------------------------------------------------
void Goblin::CheckAlive()
{
	// ���S���Ă���ꍇ�͏������s��Ȃ�
	if (m_currentState == m_dead.get()) return;

	if (m_hp->GetHP() <= 0)
	{
		// �X�e�[�g��ύX
		ChangeState(GoblinState::DEAD);
		// ���S�G�t�F�N�g���Đ�
		m_enemyEffect->SetEffect(EnemyEffect::ENEMY_EFFECT::DEAD);
	}
}

// -------------------------------------------------------
/// <summary>
/// �S�u����������
/// </summary>
// -------------------------------------------------------
void Goblin::DeleteGoblin()
{
	EventMessenger::Execute(EventList::DeleteEnemy, this);
}