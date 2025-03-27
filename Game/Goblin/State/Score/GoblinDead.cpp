// --------------------------------------------------
//���O:	GoblinDead.cpp
//���e:	�S�u�����̎��S���
//�쐬:	�r�c����
// --------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "../Header/GoblinDead.h"
#include "../../Goblin.h"
#include "Libraries/MyLib/EasingFunctions.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goblin">�S�u�����̃|�C���^</param>
// ---------------------------------------------
GoblinDead::GoblinDead(Goblin* goblin)
	: m_goblin{ goblin }
	, m_totalTime{}
	, m_scale{1.0f}
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
GoblinDead::~GoblinDead()
{
}

// ---------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------
void GoblinDead::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// �������iin�����j
/// </summary>
// ---------------------------------------------
void GoblinDead::PreUpdate()
{
	// �U���t���O�𖳌��ɂ���
	m_goblin->SetIsAttacking(false);
	m_totalTime = 0.0f;
	m_scale = 1.0f;

	// �S�u�����̏�ԊJ�n���̈ʒu���擾
	m_startPos = m_goblin->GetPosition();
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void GoblinDead::Update(const float& elapsedTime)
{
	// ���Ԃ����Z����
	m_totalTime += elapsedTime;

	// �A�j���[�V�������X�V����
	UpdateAnimation();

	// ��莞�Ԍo�߂�����S�u���������ł�����
	if (m_totalTime > DEAD_TIME) m_goblin->DeleteGoblin();
}

// ---------------------------------------------
/// <summary>
/// �A�j���[�V�����X�V����
/// </summary>
// ---------------------------------------------
void GoblinDead::UpdateAnimation()
{
	// �C�[�W���O�A�j���[�V�������g���ăX�P�[����ύX����
	m_scale = 1 - Easing::easeOutBounce(m_totalTime / DEAD_TIME);

	// ���W���A�j���[�V������p���Ȃ���0�ɂ���
	m_startPos.y = m_startPos.y - m_startPos.y * Easing::easeOutBounce(m_totalTime / DEAD_TIME);

	// �S�u�����Ɍv�Z��������^����
	m_goblin->SetScale(DirectX::SimpleMath::Vector3(m_scale, m_scale, m_scale));
	m_goblin->SetPosition(m_startPos);
}

// ---------------------------------------------
/// <summary>
/// �������iout�����j
/// </summary>
// ---------------------------------------------
void GoblinDead::PostUpdate()
{
}

// ---------------------------------------------
/// <summary>
/// �I���������s��
/// </summary>
// ---------------------------------------------
void GoblinDead::Finalize()
{
}