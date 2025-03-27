// --------------------------------------------------
//���O:	GoblinTutorial.cpp
//���e:	�`���[�g���A�����̃S�u�����X�e�[�g
//�쐬:	�r�c����
// --------------------------------------------------
#include "pch.h"
#include "../Header/GoblinTutorial.h"
#include "../../Goblin.h"
#include "Game/Messenger/EventMessenger.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="goblin">�S�u�����̃|�C���^</param>
// ---------------------------------------------
GoblinTutorial::GoblinTutorial(Goblin* goblin)
	: 
	m_goblin{ goblin },
	m_TotalTime{}
{
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
GoblinTutorial::~GoblinTutorial()
{
}

// ---------------------------------------------
/// <summary>
/// ������
/// </summary>
// ---------------------------------------------
void GoblinTutorial::Initialize()
{
}

// ---------------------------------------------
/// <summary>
/// ������(in)
/// </summary>
// ----------------------------------------------
void GoblinTutorial::PreUpdate()
{
	m_goblin->SetIsAttacking(false);
	m_TotalTime = 0.0f;
}

// ---------------------------------------------
/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void GoblinTutorial::Update(const float& elapsedTime)
{
	// ���Ԃ����Z����
	m_TotalTime += elapsedTime;

	if (m_TotalTime >= SCREENSHOT_TIME)
	{
		EventMessenger::Execute(EventList::TakeCapture, nullptr);
	}
}

// ---------------------------------------------
/// <summary>
/// ������(out)
/// </summary>
// ---------------------------------------------
void GoblinTutorial::PostUpdate()
{
}

// ---------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------
void GoblinTutorial::Finalize()
{
}