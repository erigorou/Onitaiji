// ------------------------------------------------
// ���O:	GameData.cpp
// ���e:	�Q�[���f�[�^��n�����߂̃N���X
//			��ɃV�[���Ԃł̃f�[�^�̎󂯓n���Ɏg�p����
// �쐬;	�r�c����
// ------------------------------------------------

// �C���N���[�h
#include "pch.h"
#include "GameData.h"

std::unique_ptr<GameData> GameData::s_data = nullptr;

// ------------------------------------------------
/// <summary>
/// �C���X�^���X�̎擾
/// </summary>
/// <returns>GameData�̃|�C���^</returns>
// ------------------------------------------------
GameData* const GameData::GetInstance()
{
	// �C���X�^���X����������Ă��Ȃ��ꍇ
	if (s_data == nullptr)
	{
		// ��������
		s_data.reset(new GameData());
	}

	// �C���X�^���X��Ԃ�
	return s_data.get();
}

// ------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ------------------------------------------------
GameData::GameData()
	: m_battleResult{ BATTLE_RESULT::WIN }
	, m_questIndex{1}
{
}