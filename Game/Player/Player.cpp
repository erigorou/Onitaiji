// --------------------------------------------------
// ���O:	Player.h
// ���e:	�v���C���[�N���X
//			�v���C���[�̃X�e�[�g��Փ˔���A�`���A�j���[�V��������
// �쐬:	�r�c����
// --------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/Math.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Sound/Sound.h"
#include "Libraries/MyLib/KeyboardChacker.h"
#include "Game/GameResources.h"
#include "Game/Player/Player.h"
#include "Game/Weapon/Sword/Sword.h"
#include "Game/Factory/Factory.h"
#include "../Data/HPSystem.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
Player::Player()
	:
	m_elapsedTime{},
	m_tilt{},
	m_model{},
	m_position{ HOME_POSITION },
	m_angle{},
	m_inputVector{},
	m_acceleration{},
	m_pushBackValue{},
	m_worldMatrix{},
	m_currentState{},
	m_particleTime{},
	m_isHit{},
	m_coolTime{},
	m_canHitBoss{ false },
	m_canHitCudgel{ false },
	m_canHitGoblin{ false },
	m_animationRotate{},
	m_isInputMoveKey{ false },
	m_states{}
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
Player::~Player()
{
	Finalize();
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------
void Player::Initialize()
{
	// �`��֘A�̏�����
	InitializeRender();
	// �����蔻��̍쐬
	CreateCollision();
	// �X�e�[�g�̍쐬
	CreateState();
	// HP���Ǘ�����N���X�̐���
	m_hp = std::make_unique<HPSystem>(PLAYER_HP);
	// �C�x���g��o�^
	AttachEvent();
	// ����̐���
	m_sword = Factory::CreateSword(this);
}

// ---------------------------------------------------------
/// <summary>
/// �Փ˔���̓o�^
/// </summary>
// ---------------------------------------------------------
void Player::CreateCollision()
{
	// �̂̓����蔻����쐬
	m_bodyCollision = std::make_unique<DirectX::BoundingSphere>(m_position, PLAYER_SCALE * COLLISION_RADIUS);

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingSphere> data =
	{
		ObjectType::Player,		// �I�u�W�F�N�g�̎��
		CollisionType::Sphere,	// �����蔻��`��̎��
		this,					// �I�u�W�F�N�g�̃A�h���X
		m_bodyCollision.get()	// �����蔻��̃A�h���X
	};
	// �����蔻����L�^����
	EventMessenger::Execute(EventList::AddSphereCollision, &data);
}

// ---------------------------------------------------------
/// <summary>
/// �X�e�[�g�̍쐬�E�������E�o�^
/// </summary>
// ---------------------------------------------------------
void Player::CreateState()
{
	// �ҋ@��Ԃ̍쐬�E�������E�o�^
	m_playerIdling = std::make_unique<PlayerIdling>(this);
	m_playerIdling->Initialize();
	m_states[static_cast<int>(PlayerState::Idling)] = m_playerIdling.get();

	// �����Ԃ̍쐬�E�������E�o�^
	m_playerDodging = std::make_unique<PlayerDodging>(this);
	m_playerDodging->Initialize();
	m_states[static_cast<int>(PlayerState::Dodging)] = m_playerDodging.get();

	// �U����Ԃ̍쐬�E�������E�o�^
	m_playerAttacking1 = std::make_unique<PlayerAttacking1>(this);
	m_playerAttacking1->Initialize();
	m_states[static_cast<int>(PlayerState::Attacking1)] = m_playerAttacking1.get();

	// �U����Ԃ̍쐬�E�������E�o�^
	m_playerAttacking2 = std::make_unique<PlayerAttacking2>(this);
	m_playerAttacking2->Initialize();
	m_states[static_cast<int>(PlayerState::Attacking2)] = m_playerAttacking2.get();

	// �����Ԃ̍쐬�E�������E�o�^
	m_playerNockBacking = std::make_unique<PlayerNockBacking>(this);
	m_playerNockBacking->Initialize();
	m_states[static_cast<int>(PlayerState::NockBacking)] = m_playerNockBacking.get();

	// �ŏ��̃X�e�[�g��ݒ�
	m_currentState = m_playerIdling.get();
}

// ---------------------------------------------------------
/// <summary>
/// �����_�����O�n�̏�����
/// </summary>
// ---------------------------------------------------------
void Player::InitializeRender()
{
	CommonResources* resources = CommonResources::GetInstance();

	auto device = resources->GetDeviceResources()->GetD3DDevice();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();

	// ���f���̎擾
	m_model = GameResources::GetInstance()->GetModel("player");
	// �x�[�V�b�N�G�t�F�N�g���쐬����
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);
	// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf())
	);
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);
}

// ---------------------------------------------------------
/// <summary>
/// �C�x���g�̓o�^
/// </summary>
// ---------------------------------------------------------
void Player::AttachEvent()
{
	// IObject* �^�̃I�u�W�F�N�g���擾����
	EventMessenger::AttachGetter(GetterList::GetPlayer, std::bind(&Player::GetObject, this));
	// �{�X���v���C���[�ɍU�������Ă��邩
	EventMessenger::Attach(EventList::PlayerCanDamageBoss, std::bind(&Player::CanHitBoss, this, std::placeholders::_1));
	// ���_���v���C���[�ɍU�������Ă��邩
	EventMessenger::Attach(EventList::PlayerCanDamageCudgel, std::bind(&Player::CanHitCudgel, this, std::placeholders::_1));
	// �S�u�������v���C���[�ɍU�������Ă��邩
	EventMessenger::Attach(EventList::PlayerCanDamageGoblin, std::bind(&Player::CanHitGoblin, this, std::placeholders::_1));
}


// ---------------------------------------------------------
/// <summary>
/// �v���C���[�̃X�e�[�g��ύX����
/// </summary>
/// <param name="state">�ύX��̃X�e�[�g</param>
// ---------------------------------------------------------
void Player::ChangeState(PlayerState state)
{
	int stateIndex = static_cast<int>(state);

	// ���݂̃X�e�[�g�Ɠ����Ȃ珈���Ȃ�
	if (m_currentState == m_states[stateIndex]) return;

	// ����X�V�������s��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��ύX����
	m_currentState = m_states[stateIndex];
	// �V�����X�e�[�g�̎��O�X�V���s��
	m_currentState->PreUpdate();
}

// ---------------------------------------------------------
/// <summary>
/// ��莞�ԂŃX�e�[�g��ύX����
/// </summary>
/// <param name="nowTime">���݂̎���</param>
/// <param name="totalTime">�ύX���鎞��</param>
/// <param name="state">�ύX��̃X�e�[�g</param>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void Player::TimeComparison(float& nowTime, const float totalTime, PlayerState state, const float elapsedTime)
{
	// ��߂�ꂽ���ԂɂȂ�����
	if (nowTime >= totalTime)
	{
		// �V�����X�e�[�g�ɕύX����
		ChangeState(state);
		return;
	}
	// ���Ԃ̌v�����s��
	nowTime += elapsedTime;
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void Player::Update(const float elapsedTime)
{
	// �o�ߎ��Ԃ�ۑ�����g
	m_elapsedTime = elapsedTime;
	// �X�e�[�g�̍X�V
	m_currentState->Update(elapsedTime);
	// �v���C���[�̈ړ�
	CalculationMatrix();
	// �����蔻��̍X�V
	m_bodyCollision->Center = m_position;
	m_bodyCollision->Center.y = 0.0f;
	// ����̍X�V����
	m_sword->Update(elapsedTime);
	// �N�[���^�C�����v������
	CalculationCoolTime(elapsedTime);
}

// ---------------------------------------------------------
/// <summary>
/// �N�[���^�C�����v������
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void Player::CalculationCoolTime(const float elapsedTime)
{
	// �N�[���^�C�����N�����ŁA�N�[���^�C�����I����Ă��Ȃ��ꍇ
	if (m_isHit && m_coolTime < COOL_TIME) {
		m_coolTime += elapsedTime;
	}
	// �N�[���^�C���o�ߌ�Ƀ��Z�b�g
	else if (m_coolTime >= COOL_TIME) { 
		m_isHit = false; m_coolTime = 0.0f;
	}
}

// ---------------------------------------------------------
/// <summary>
/// �L�[���͂��擾����(�������u��)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// // ---------------------------------------------------------
void Player::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	// �X�e�[�g�ɂ��L�[���͂�`�B
	m_currentState->OnKeyPressed(key);
}

// ---------------------------------------------------------
/// <summary>
/// �L�[���͂��擾����(������Ă����)
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// // ---------------------------------------------------------
void Player::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	// �ړ��x�N�g�������Z�b�g
	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	// ���L�[�̓��͂�����ꍇ
	if (KeyboardChacker::IsInputArrowKey(key))
	{
		if (!m_isInputMoveKey)
		{
			// �ړ��L�[�̓��͂�����ꍇ
			m_isInputMoveKey = true;
			// ���Z�b�g
			m_inputVector = DirectX::SimpleMath::Vector2::Zero;
		}

		// �ړ��L�[�ɉ����ē��̓x�N�g����ݒ肷��
		if (key == DirectX::Keyboard::Up)		m_inputVector += INPUT_FLONT;
		if (key == DirectX::Keyboard::Down)		m_inputVector += INPUT_BACK;
		if (key == DirectX::Keyboard::Left)		m_inputVector += INPUT_LEFT;
		if (key == DirectX::Keyboard::Right)	m_inputVector += INPUT_RIGHT;
	}
	// �X�e�[�g�ɂ��L�[���͂�`�B
	m_currentState->OnKeyDown(key);
}

// ---------------------------------------------------------
/// <summary>
/// �v���C���[�̉�]�̌v�Z���s��
/// </summary>
/// <param name="enemyPos">�^�[�Q�b�g�̍��W</param>
/// <returns>�v�Z����</returns>
// ---------------------------------------------------------
float Player::CalucratePlayerRotation(DirectX::SimpleMath::Vector3 const enemyPos)
{
	// ���͂��Ȃ��ꍇ��0��Ԃ�
	if (m_inputVector.LengthSquared() < FLT_EPSILON)
	{
		return 0.0f;
	}

	// �G�̕������擾�i���W�A���P�ʂŌv�Z�j
	float lookEnemy = Math::CalculationAngle(m_position, enemyPos);

	// ���̓x�N�g���𐳋K��
	Vector2 normalizedInput = m_inputVector;
	normalizedInput.Normalize();

	// atan2�œ��̓x�N�g���̊p�x���v�Z�i���W�A���P�ʁj
	float inputAngle = std::atan2(normalizedInput.x, normalizedInput.y);

	// �G�̕����Ɠ��͕����̍����p�x���v�Z
	float resultAngle = lookEnemy + inputAngle;

	// �K�v�Ȃ�p�x��0�`2�΂͈̔͂ɐ��K��
	while (resultAngle < 0)
	{
		resultAngle += DirectX::XM_2PI; // 2�΂������Đ��͈̔͂�
	}

	while (resultAngle > DirectX::XM_2PI)
	{
		resultAngle -= DirectX::XM_2PI; // 2�΂������Ĕ͈͓���
	}

	return resultAngle; // �v�Z���ʁi���W�A���P�ʁj��Ԃ�
}

// ---------------------------------------------------------
/// <summary>
/// �ړ��������v�Z����
/// </summary>
// ---------------------------------------------------------
void Player::MovePlayer()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	// �����p���x
	Vector3 moveVelocity = Vector3::Zero;

	///////////////////// �ړ��L�[�̓��͂��Ȃ��ꍇ�̏��� /////////////////
	if (m_isInputMoveKey == false)
	{
		// ���x�̒������擾����
		float accelerationLength = m_acceleration.Length();
		// 0�̋ߎ��l���傫���ꍇ
		if (accelerationLength >= FLT_EPSILON)
		{
			// �ێ���������x�̐��K���x�N�g�����擾����
			Vector3 accelerationNormal = m_acceleration / accelerationLength;
			// ���C���v�Z
			accelerationLength -= PLAYER_FRICTION;
			// �����x���i�[�j�ɂȂ�Ƃ��Ƀ��Z�b�g����
			if (accelerationLength < 0.0f)	accelerationLength = 0.0f;
			// �����x���Čv�Z����
			m_acceleration = accelerationNormal * accelerationLength;
			// ���x���v�Z����
			moveVelocity += m_acceleration;
		}
	}

	///////////////////// �ړ��L�[�̓��͂��������ꍇ�̏��� /////////////////
	else
	{
		// ���E�L�[���������̂悤�ȏꍇ�́A�����Ȃ�
		if (m_inputVector.Length() <= FLT_EPSILON)
			return;

		// ��{�ړ��ʂ��v�Z����
		moveVelocity += Vector3::Forward * PLAYER_SPEED;
		// �����x�̌v�Z���s��
		m_acceleration += Vector3::Forward * PLAYER_ACCELERATION;

		// 2��ɂ��邱�Ƃŕ������O��
		if (m_acceleration.LengthSquared() > 1.0f){
			// �����1�ɐݒ肷��
			m_acceleration.Normalize();
		}
		// ��{�ړ��ɉ����x����悹����
		moveVelocity += m_acceleration;
		// ���x��ۑ�����
		m_velocity = moveVelocity;
	}

	/////////////////////////// �ړ����� //////////////////////////////////
	// �����x���v�Z����
	moveVelocity *= PLAYER_SPEED;
	// �ړ���̍��W���v�Z����
	m_position += Vector3::Transform(moveVelocity, Matrix::CreateRotationY(-m_angle));

	/////////////////////////// �p�[�e�B�N���̐��� //////////////////////////
	if (moveVelocity != Vector3::Zero)
	{
		// �o�ߎ��Ԃ��L�^
		m_particleTime += m_elapsedTime;
		// ��莞�Ԍo�ߌ�Ƀp�[�e�B�N���𐶐�����
		if (m_particleTime >= PARTICLE_INTERVAL)
		{
			// �p�[�e�B�N���̐����C�x���g
			EventMessenger::Execute(EventList::CreateTrailDust, nullptr);
			// ���Ԃ����Z�b�g
			m_particleTime = 0.0f;
		}
	}
	// �ړ��L�[�̓��͂����Z�b�g����
	m_isInputMoveKey = false;
}

// ---------------------------------------------------------
/// <summary>
/// ���[���h�s��̌v�Z���s��
/// </summary>
// ---------------------------------------------------------
void Player::CalculationMatrix()
{
	using namespace DirectX::SimpleMath;

	// ���[���h�s���������
	m_worldMatrix = Matrix::Identity;
	// �X�P�[���̓K�p
	m_worldMatrix *= Matrix::CreateScale(PLAYER_SCALE);
	// �A�j���[�V������]�̓K�p�i���[�E�s�b�`�E���[���j
	Quaternion animationRotation = Quaternion::CreateFromYawPitchRoll(
		m_animationRotate.y,
		m_animationRotate.x,
		m_animationRotate.z
	);
	// �v���C���[�̕��������i�G�̕����������]�j
	Quaternion directionRotation = Quaternion::CreateFromYawPitchRoll(
		-m_angle + DirectX::XMConvertToRadians(180.0f),
		0.0f,
		0.0f
	);
	// ��]��K�p
	Quaternion totalRotation = animationRotation * directionRotation;
	m_worldMatrix *= Matrix::CreateFromQuaternion(totalRotation);

	// �ʒu��K�p�i�Ō�ɕ��s�ړ��j
	m_worldMatrix *= Matrix::CreateTranslation(m_position);
	// �����߂��ʂ����Z�b�g
	m_pushBackValue = Vector3::Zero;
}

// ---------------------------------------------------------
/// <summary>
/// ���f����`�悷��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
// ---------------------------------------------------------
void Player::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// ���f���̃G�t�F�N�g�����X�V����
	m_model->UpdateEffects([](DirectX::IEffect* effect)
		{
			// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
			DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				// ���C�g��L��������
				basicEffect->SetLightingEnabled(true);
				// �A���r�G���g���C�g�̐ݒ�
				basicEffect->SetAmbientLightColor(DirectX::Colors::Gray); // �K�؂ȃA���r�G���g�F��ݒ�
				// �K�v�ɉ����ă��C�g�̐ݒ���s��
				basicEffect->SetLightEnabled(0, true);
				basicEffect->SetLightDiffuseColor(0, DirectX::Colors::White);  // �f�B�t���[�Y�F��ݒ�
				basicEffect->SetLightSpecularColor(0, DirectX::Colors::White); // �X�y�L�����[�F��ݒ�

				basicEffect->SetLightEnabled(1, false); // �ǉ��̃��C�g���s�v�Ȃ疳����
				basicEffect->SetLightEnabled(2, false); // �ǉ��̃��C�g���s�v�Ȃ疳����
				// ���f���̎������F�����ɐݒ肵�Ė�����
				basicEffect->SetEmissiveColor(DirectX::Colors::Black);
			}
		}
	);

	// ���f����`�悷��
	m_model->Draw(context, *states, m_worldMatrix, view, projection);

	// �����`�悷��
	m_sword->Render(view, projection);
}

// ---------------------------------------------------------
/// <summary>
/// �I���������s��
/// </summary>
// ---------------------------------------------------------
void Player::Finalize()
{
	// �Փ˔�����폜���邽�߂̍\����
	DeleteCollisionData data = { CollisionType::Sphere, this };
	// �����蔻��̍폜
	EventMessenger::Execute(EventList::DeleteCollision, &data);

	// �X�e�[�g�z��̉��
	for (int i = 0; i < STATE_MAX; i++)
	{
		m_states[i]->Finalize();
		m_states[i] = nullptr;
	}
}

// ---------------------------------------------------------
/// <summary>
/// �Փ˂����Ƃ��̃C�x���g
/// </summary>
/// <param name="data">����̃f�[�^</param>
// ---------------------------------------------------------
void Player::HitAction(InterSectData data)
{
	// �{�X�S�Ƃ̓����蔻��
	HitBossBody(data);
	// ����Ƃ̓����蔻��
	HitCudgel(data);
	// �X�e�[�W�Ƃ̓����蔻��
	HitStage(data);
	// ���S�Ƃ̓����蔻��
	HitGoblin(data);
}

// ---------------------------------------------------------
/// <summary>
/// �_���[�W����
/// </summary>
/// <param name="damage">�󂯂��_���[�W��</param>
// ---------------------------------------------------------
void Player::Damage(float damage)
{
	// HP�����炷
	m_hp->Damage(damage);
	m_isHit = true;
	m_canHitBoss = false;
	m_canHitCudgel = false;
	m_canHitGoblin = false;
	// �m�b�N�o�b�N������
	ChangeState(PlayerState::NockBacking);
	// ���ʉ���炷
	Sound::GetInstance()->PlaySE(Sound::SE_TYPE::PLAYER_DAMAGED);
}

// ---------------------------------------------------------
/// <summary>
/// �{�X�Ƃ̏Փ˃C�x���g
/// </summary>
/// <param name="data">�Փˑ���̃f�[�^</param>
// ---------------------------------------------------------
void Player::HitBossBody(InterSectData data)
{
	if (data.objType == ObjectType::Boss && data.colType == CollisionType::Sphere)
	{
		// �G�̃X�e�[�g���_�b�V���U���̏ꍇ�ő��肪�U�����̏ꍇ
		if (! m_isHit && m_canHitBoss){
			Damage(BOSS_ATTACK_POWER);
		}

		// �Փ˂����I�u�W�F�N�g�̏����擾
		DirectX::BoundingSphere playerCollision = *m_bodyCollision.get();
		DirectX::BoundingSphere enemyCollision  = *data.collision;

		// �����߂��ʂ��v�Z
		m_pushBackValue += Math::pushBack_BoundingSphere(playerCollision, enemyCollision);
		// y���W�ɂ͔��f�����ɐݒ�
		m_pushBackValue.y = 0.0f;
		// �v���C���[�̈ʒu�������߂�
		m_position += m_pushBackValue;
		m_bodyCollision->Center = m_position;
	}
}

// ---------------------------------------------------------
/// <summary>
/// ���S�̏Փ˃C�x���g
/// </summary>
/// <param name="data">�Փˑ���̃f�[�^</param>
// ---------------------------------------------------------
void Player::HitGoblin(InterSectData data)
{
	if (data.objType == ObjectType::Goblin && data.colType == CollisionType::Sphere)
	{
		// �G�̃X�e�[�g���_�b�V���U���̏ꍇ�ő��肪�U�����̏ꍇ
		if (!m_isHit && m_canHitGoblin) {
			Damage(GOBLIN_ATTACK_POWER);
		}

		// �Փ˂����I�u�W�F�N�g�̏����擾
		DirectX::BoundingSphere playerCollision = *m_bodyCollision.get();
		DirectX::BoundingSphere goblinCollision = *data.collision;

		// �����߂��ʂ��v�Z
		m_pushBackValue += Math::pushBack_BoundingSphere(playerCollision, goblinCollision);
		// y���W�ɂ͔��f�����ɐݒ�
		m_pushBackValue.y = 0.0f;
		// �v���C���[�̈ʒu�������߂�
		m_position += m_pushBackValue;
		m_bodyCollision->Center = m_position;
	}
}
// ---------------------------------------------------------
/// <summary>
/// �{�X�̕���(���_)�̏Փ˃C�x���g
/// </summary>
/// <param name="data">�Փˑ���̃f�[�^</param>
// ---------------------------------------------------------
void Player::HitCudgel(InterSectData data)
{
	// ���_���U����Ԃ��A�N�[���^�C�����łȂ��ꍇ
	if (!m_isHit &&
		m_canHitCudgel &&
		data.objType == ObjectType::Cudgel &&
		data.colType == CollisionType::OBB &&
		m_currentState != m_playerDodging.get()
		)
	{
		Damage(BOSS_CUDGEL_POWER);
	}
}

// ---------------------------------------------------------
/// <summary>
/// �X�e�[�W�Ƃ̏Փ˃C�x���g
/// </summary>
/// <param name="data">�Փˑ���̃f�[�^</param>
// ---------------------------------------------------------
void Player::HitStage(InterSectData data)
{
	if (data.objType == ObjectType::Stage && data.colType == CollisionType::Sphere)
	{
		// �Փ˂����I�u�W�F�N�g�̏����擾
		DirectX::BoundingSphere stageCollision = *data.collision;
		// �����߂��ʂ��v�Z
		m_pushBackValue += Math::pushFront_BoundingSphere(*m_bodyCollision.get(), stageCollision);
		// y���W�ɂ͔��f�����ɐݒ�
		m_pushBackValue.y = 0.0f;
		// �v���C���[�̈ʒu�������߂�
		m_position += m_pushBackValue;
		m_bodyCollision->Center = m_position;
	}
}

// ---------------------------------------------------------
/// <summary>
/// �{�X���v���C���[�ɑ΂��čU�����ł���̂�
/// </summary>
/// <param name="flag">�t���O</param>
// ---------------------------------------------------------
void Player::CanHitBoss(void* flag)
{
	m_canHitBoss = *(bool*)flag;
}

// ---------------------------------------------------------
/// <summary>
/// �{�X�̕���(���_)���v���C���[�ɑ΂��čU�����ł���̂�
/// </summary>
/// <param name="flag">�t���O</param>
// ---------------------------------------------------------
void Player::CanHitCudgel(void* flag)
{
	m_canHitCudgel = *(bool*)flag;
}

// ---------------------------------------------------------
/// <summary>
/// ���S���v���C���[�ɑ΂��čU�����ł���̂�
/// </summary>
/// <param name="flag">�t���O</param>
// ---------------------------------------------------------
void Player::CanHitGoblin(void* flag)
{
	m_canHitCudgel = *(bool*)flag;
}