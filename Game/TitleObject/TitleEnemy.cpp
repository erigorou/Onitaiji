// ---------------------------------------------------------
//
// ���O:	TitleEnemy.cpp
// ���e:	�^�C�g���V�[���̓G���������Ă���
// �쐬;	�r�c����
//
// ---------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include <Model.h>
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "DeviceResources.h"
#include "TitleEnemy.h"
#include "EnemyTitleMoving.h"
#include "EnemyTitleIdling.h"
#include "Interface/IState.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
TitleEnemy::TitleEnemy()
	:
	m_model{},
	m_titleIdling{},
	m_titleMoving{},
	m_states{},
	m_currentState{},
	m_position{},
	m_angle{},
	m_worldMatrix{ DirectX::SimpleMath::Matrix::Identity }
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------

TitleEnemy::~TitleEnemy()
{
	Finalize();
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------

void TitleEnemy::Initialize()
{
	// ���f���̎擾
	m_model = GameResources::GetInstance()->GetModel("titleOni");

	// �X�e�[�g�̍쐬
	CreateState();
}

// ---------------------------------------------------------
/// <summary>
/// �X�e�[�g�̍쐬����
/// </summary>
// ---------------------------------------------------------
void TitleEnemy::CreateState()
{
	// �ҋ@��Ԃ̍쐬�E�������E�ۑ�
	m_titleIdling = std::make_unique<EnemyTitleIdling>(this);
	m_titleIdling->Initialize();
	m_states[static_cast<int>(BossState::IDLING)] = m_titleIdling.get();

	// �ړ���Ԃ̍쐬�E�������E�ۑ�
	m_titleMoving = std::make_unique<EnemyTitleMoving>(this);
	m_titleMoving->Initialize();
	m_states[static_cast<int>(BossState::MOVING)] = m_titleMoving.get();

	// �����̃X�e�[�g��ҋ@��ԂɊ��蓖�Ă�
	m_currentState = m_titleIdling.get();
}

// ---------------------------------------------------------
/// <summary>
/// ��ԑJ�ڏ���
/// </summary>
/// <param name="state">�J�ڐ�̏��</param>
// ---------------------------------------------------------
void TitleEnemy::ChangeState(BossState state)
{
	// �X�e�[�g�̃C���f�b�N�X���擾
	int index = static_cast<int>(state);

	// ����Ȃ��X�e�[�g���X�V���悤�Ƃ�����߂�
	if (m_currentState == m_states[index]) return;
	// �V�K�̏�ԑJ�ڑO�Ɏ���X�V���s��
	m_currentState->PostUpdate();
	// �V�K�̏�Ԃ����݂̏�Ԃɐݒ肷��
	m_currentState = m_states[index];
	// �V�K�̏�ԑJ�ڌ�Ɏ��O�X�V���s��
	m_currentState->PreUpdate();
}


// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------

void TitleEnemy::Update(float elapsedTime)
{
	using namespace DirectX::SimpleMath;

	// ���[���h�s���������
	m_worldMatrix = Matrix::Identity;

	// �X�e�[�^�X���X�V
	m_currentState->Update(elapsedTime);

	// ��]�p�̌v�Z
	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateRotationY(-m_angle + DirectX::XMConvertToRadians(180));

	// �ړ�����
	m_velocity *= TitleEnemy::TITLE_ENEMY_SPEED;
	// �ʒu�̍X�V
	m_position += DirectX::SimpleMath::Vector3::Transform(m_velocity, m_worldMatrix);

	// ���[���h�s��̌v�Z
	m_worldMatrix
		// �T�C�Y�v�Z
		*= DirectX::SimpleMath::Matrix::CreateScale(TITLE_ENEMY_SCALE)
		// �ʒu�̐ݒ�
		*= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
}

// ---------------------------------------------------------
/// <summary>
/// �\������
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
// ---------------------------------------------------------
void TitleEnemy::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	// �f�o�C�X�R���e�L�X�g���擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// �R�����X�e�[�g���擾
	auto states = CommonResources::GetInstance()->GetCommonStates();

	// �[�x�l���Q�Ƃ��ď�������
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	// ���f���̕`��
	m_model->Draw(context, *states, m_worldMatrix, view, projection);

}

// ---------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------------------
void TitleEnemy::Finalize()
{
}