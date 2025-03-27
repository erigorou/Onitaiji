// ----------------------------------------------------------
// ���O:	Cudgel
// 
// ���e:	�{�X�S�̕���̋��_�N���X
//			�X�V������`����s��
// 			�X�e�[�g�}�V�[�����g�p
//
// ����:	�r�c����
// ----------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/GameResources.h"
#include "Libraries/MyLib/Collision.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/Boss/Boss.h"
#include "Game/Weapon/Cudgel/Cudgel.h"
#include "header/CudgelIdling.h"
#include "header/CudgelAttacking.h"
#include "header/CudgelSweeping.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="boss"></param>
Cudgel::Cudgel(Boss* boss)
	:
	m_boss(boss),
	m_currentState(),
	m_worldMatrix(DirectX::SimpleMath::Matrix::Identity),
	m_isDead(false)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Cudgel::~Cudgel()
{
}

/// <summary>
/// ����������
/// </summary>
void Cudgel::Initialize()
{
	// ���_�̃|�C���^���擾
	EventMessenger::AttachGetter(GetterList::GetCudgel, std::bind(&Cudgel::GetCudgelObject, this));
	// ���_�̃X�e�[�g��ύX
	EventMessenger::Attach(EventList::ChangeCudgelState, std::bind(&Cudgel::ChangeState, this, std::placeholders::_1));

	// ���f�����擾����
	m_model = GameResources::GetInstance()->GetModel("cudgel");

	// �X�e�[�g�̍쐬
	CreateState();
	// �����蔻��̐���
	CreateCollision();
}

/// <summary>
/// ��Ԃ̐���
/// </summary>
void Cudgel::CreateState()
{
	// �ҋ@�̐����E�������E�o�^
	m_idling = std::make_unique<CudgelIdling>(this);
	m_idling->Initialize();
	m_states.push_back(m_idling.get());

	// �U���̐����E�������E�o�^
	m_attacking = std::make_unique<CudgelAttacking>(this);
	m_attacking->Initialize();
	m_states.push_back(m_attacking.get());

	// �ガ�����̐����E�������E�o�^
	m_sweeping = std::make_unique<CudgelSweeping>(this);
	m_sweeping->Initialize();
	m_states.push_back(m_sweeping.get());

	// ������Ԃ��w��
	m_currentState = m_idling.get();
}

/// <summary>
/// �����蔻�萶���F�o�^
/// </summary>
void Cudgel::CreateCollision()
{
	m_originalBox = Collision::Get_BoundingOrientedBox_FromMODEL(m_model);
	m_collision = std::make_unique<DirectX::BoundingOrientedBox>(m_originalBox);

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingOrientedBox> data =
	{
		ObjectType::Cudgel,		// �I�u�W�F�N�g�̎��
		CollisionType::OBB,		// �����蔻��̎��
		this,					// ���̃N���X�̃|�C���^
		m_collision.get()		// �����蔻��
	};

	// �����蔻����L�^����
	EventMessenger::Execute(EventList::AddOBBCollision, &data);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Cudgel::Update(float elapsedTime)
{
	// ���݂̃X�e�[�g�̍X�V����
	m_currentState->Update(elapsedTime);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
void Cudgel::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// ���S���Ă���Ȃ瑁�����^�[��
	if (m_isDead) return;

	// ���f����`��
	m_model->Draw(context, *states, m_worldMatrix, view, projection);
}

/// <summary>
/// �I������
/// </summary>
void Cudgel::Finalize()
{
}

/// <summary>
/// �X�e�[�g�ύX
/// </summary>
/// <param name="state">�V�����X�e�[�g</param>
void Cudgel::ChangeState(void* state)
{
	int index = *static_cast<int*>(state);

	// �X�e�[�g�̕ύX
	if (m_currentState == m_states[index]) return;

	// �X�e�[�g�̎��㏈��
	m_currentState->PostUpdate();
	// �V�����X�e�[�g�ɐ؂�ւ���
	m_currentState = m_states[index];
	// �V�����X�e�[�g�̎��O�������s��
	m_currentState->PreUpdate();
}

/// <summary>
/// �Փ˃C�x���g
/// </summary>
/// <param name="data">�Փˑ���</param>
void Cudgel::HitAction(InterSectData data)
{
	m_currentState->HitAction(data);
}