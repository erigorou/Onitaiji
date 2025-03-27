// ----------------
//
// �����Y�̓�
//
// ----------------

#include "pch.h"
#include <Model.h>
#include <cassert>
// �w�b�_�[
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugString.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/Collision.h"
#include "Game/Messenger/EventMessenger.h"
#include "Sword.h"
#include "Game/Player/Player.h"

#include "Game/Weapon/Sword/Header/SwordIdling.h"
#include "Game/Weapon/Sword/Header/SwordAttacking1.h"
#include "Game/Weapon/Sword/Header/SwordAttacking2.h"

// --------------------------------------------
// �Œ�l
// --------------------------------------------
// ���̑傫��
const float Sword::SWORD_SCALE = Player::PLAYER_SCALE * 1.5f;

// --------------------------------------------
// �R���X�g���N�^
// --------------------------------------------
Sword::Sword(Player* player)
	:
	m_player(player),
	m_worldMatrix{ DirectX::SimpleMath::Matrix::Identity },
	m_collision{},
	m_originalBox{},
	m_canAttack{ false }
{
}

// --------------------------------------------
// �f�X�g���N�^
// --------------------------------------------
Sword::~Sword()
{
}

// --------------------------------------------
// ����������
// --------------------------------------------
void Sword::Initialize()
{
	// ���f���̓ǂݍ���
	m_model = GameResources::GetInstance()->GetModel("sword");
	// �X�e�[�g���쐬
	CreateState();
	// �����蔻����쐬
	CreateCollision();
}

// --------------------------------------------
// �V�[���𐶐�����
// --------------------------------------------
void Sword::CreateState()
{
	// �ҋ@�X�e�[�g�𐶐�
	m_idling = std::make_unique<SwordIdling>(this);
	// ����������
	m_idling->Initialize();
	// �ҋ@�X�e�[�g���i�[
	m_states.push_back(m_idling.get());

	// �U���X�e�[�g�𐶐�
	m_attacking1 = std::make_unique<SwordAttacking1>(this);
	// ����������
	m_attacking1->Initialize();
	// �U���X�e�[�g���i�[
	m_states.push_back(m_attacking1.get());

	// �U���X�e�[�g�𐶐�
	m_attacking2 = std::make_unique<SwordAttacking2>(this);
	// ����������
	m_attacking2->Initialize();
	// �U���X�e�[�g���i�[
	m_states.push_back(m_attacking2.get());

	// ���݂̃X�e�[�g��ݒ�
	m_currentState = m_idling.get();
}

// --------------------------------------------
// �Փ˔���̐���
// --------------------------------------------
void Sword::CreateCollision()
{
	// ���f���̑傫������Փ˔�����擾����
	m_originalBox = Collision::Get_BoundingOrientedBox_FromMODEL(m_model);
	m_collision = std::make_unique<DirectX::BoundingOrientedBox>(m_originalBox);

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingOrientedBox> data =
	{
		ObjectType::Sword,		// �I�u�W�F�N�g�̎��
		CollisionType::OBB,		// �����蔻��̎��
		this,					// ���̃N���X�̃|�C���^
		m_collision.get()		// �����蔻��
	};

	// �Փ˔����Manager�ɓo�^
	EventMessenger::Execute(EventList::AddOBBCollision, &data);
}

// --------------------------------------------
// �X�V����
// --------------------------------------------
void Sword::Update(float elapsedTime)
{
	// ���݂̃X�e�[�g�̍X�V����
	m_currentState->Update(elapsedTime);
}

// --------------------------------------------
// �`�揈��
// --------------------------------------------
void Sword::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	// ���\�[�X�̎擾
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// ���f����`�悷��
	m_model->Draw(context, *states, m_worldMatrix, view, projection);
}

// --------------------------------------------
// �I������
// --------------------------------------------
void Sword::Finalize()
{
}

// --------------------------------------------
// �X�e�[�g�̕ύX
// --------------------------------------------
void Sword::ChangeState(void* state)
{
	// index���擾
	int index = *static_cast<int*>(state);
	// ���݂Ɠ����X�e�[�g�ɂ͕ύX���Ȃ�
	if (m_currentState == m_states[index])return;
	// �X�e�[�g�̎��㏈��
	m_currentState->PostUpdate();
	// �V�����X�e�[�g�ɐ؂�ւ���
	m_currentState = m_states[index];
	// �V�����X�e�[�g�̎��O�������s��
	m_currentState->PreUpdate();
}

// --------------------------------------------
// ���������Ƃ��̏���
// --------------------------------------------
void Sword::HitAction(InterSectData data)
{
	m_currentState->HitAction(data);
}