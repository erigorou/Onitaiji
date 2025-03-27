// -----------------------------------------------------------------
// 
// ���O: Wall.cpp
// ���e: �X�e�[�W�̋��E�ǂ�`�悷��N���X
// �쐬: �r�c����
// 
// -----------------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/GameResources.h"
#include "Wall.h"
#include "Game/Messenger/EventMessenger.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
Wall::Wall()
	:
	m_worldMatrix{},
	m_model{}
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
Wall::~Wall()
{
	Finalize();
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------
void Wall::Initialize()
{
	// ���f�����擾����
	m_model = GameResources::GetInstance()->GetModel("wall");

	// �����蔻��̐���
	CreateCollision();
}

// ---------------------------------------------------------
/// <summary>
/// �����蔻��̐���
/// </summary>
// ---------------------------------------------------------
void Wall::CreateCollision()
{
	m_collision = std::make_unique<DirectX::BoundingSphere>(DirectX::SimpleMath::Vector3::Zero, COLLISION_RADIUS);
	m_overCollision = std::make_unique<DirectX::BoundingSphere>(DirectX::SimpleMath::Vector3::Zero, COLLISION_RADIUS * COLLISION_SCALE);

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingSphere>data =
	{
		ObjectType::Stage,		// �I�u�W�F�N�g�̎��
		CollisionType::Sphere,	// �����蔻��̎��
		this,					// ���̃N���X�̃|�C���^
		m_collision.get()		// �����蔻��̃|�C���^
	};

	// �Փ˃f�[�^�̍쐬
	CollisionData<DirectX::BoundingSphere>overData =
	{
		ObjectType::Stage,		// �I�u�W�F�N�g�̎��
		CollisionType::Sphere,	// �����蔻��̎��
		this,					// ���̃N���X�̃|�C���^
		m_overCollision.get()	// �����蔻��̃|�C���^
	};

	// �Փ˔����Manager�ɓo�^
	EventMessenger::Execute(EventList::AddSphereCollision, &data);
	EventMessenger::Execute(EventList::AddSphereCollision, &overData);
}

// ---------------------------------------------------------
/// <summary>
/// ���[���h���W�X�V����
/// </summary>
// ---------------------------------------------------------
void Wall::UpdateWorldMatrix()
{
	// ������
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
	// �傫���̕ύX
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateScale(WALL_SCALE);
	// �ړ�
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(WALL_POS);
}

// ---------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// ---------------------------------------------------------
void Wall::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection)
{
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// ���[���h�s��̍X�V����
	UpdateWorldMatrix();
	// ���f����`�悷��
	m_model->Draw(context, *states, m_worldMatrix, view, projection);
}

// ---------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------------------
void Wall::Finalize()
{
	// �Փ˔����Manager����폜
	EventMessenger::Execute(EventList::DeleteCollision, this);
	EventMessenger::Execute(EventList::DeleteCollision, this);
}

// ---------------------------------------------------------
/// <summary>
/// �Փˏ���
/// </summary>
// ---------------------------------------------------------
void Wall::HitAction(InterSectData data)
{
	UNREFERENCED_PARAMETER(data);
}