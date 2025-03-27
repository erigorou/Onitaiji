// ---------------------------------------------
// ���O:	EnemyManager.cpp
// ���e:	�S�Ă̓G�̊Ǘ����s���N���X
//			���ׂĂ̓G�̐����A�X�V�A�`��A�폜���s��
// �쐬:	�r�c
// ---------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "Game/Data/GameData.h"
#include "EnemyManager.h"
#include "Game/Messenger/EventMessenger.h"
#include "../Boss/Boss.h"
#include "../Goblin/Goblin.h"
#include "../Factory/Factory.h"
#include "Interface/IEnemy.h"
#include "nlohmann/json.hpp"
#include <fstream>

// --------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="playScene"></param>
// --------------------------------
EnemyManager::EnemyManager()
	: 
	m_targetEnemyIndex(),
	m_elapsedTime(),
	m_currentTime()
{
	// �Z���N�g�N�G�X�g�̃C���f�b�N�X���擾
	m_selectQuestIndex = GameData::GetInstance()->GetSelectStage();

	// Json�t�@�C������G�𐶐�
	GenerateEnemyFromJson();
}

// --------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------
EnemyManager::~EnemyManager()
{
	// �G���ׂĂ̏I������
	for (auto& enemy : m_enemies)
	{
		enemy.data->Finalize();
	}

	// �C�x���g���b�Z���W���[����폜
	EventMessenger::Detach(EventList::EnemyCanHit);
	EventMessenger::Detach(EventList::DeleteAllGoblin);
	EventMessenger::Detach(EventList::DeleteEnemy);

	// �N���A
	m_enemies.clear();
}


// --------------------------------
/// <summary>
/// ����������
/// </summary>
// --------------------------------
void EnemyManager::Initialize()
{
	// �G�ɍU�����ł���C�x���g��o�^
	EventMessenger::Attach(EventList::EnemyCanHit, std::bind(&EnemyManager::AllEnemyCanHit, this, std::placeholders::_1));
	// �S�Ă̏��S���폜����C�x���g��o�^
	EventMessenger::Attach(EventList::DeleteAllGoblin, std::bind(&EnemyManager::AllGoblinHPZero, this));
	// �G1�̂��폜����C�x���g��o�^
	EventMessenger::Attach(EventList::DeleteEnemy, std::bind(&EnemyManager::DeleteEnemy, this, std::placeholders::_1));
	// �J�����̃^�[�Q�b�g�|�C���g����肷��C�x���g��o�^
	EventMessenger::AttachGetter(GetterList::GetTargetPosition, std::bind(&EnemyManager::GetPicupEnemyPosition, this));
}

// --------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// --------------------------------
void EnemyManager::Update(float elapsedTime)
{
	// �o�ߎ��Ԃ�ۑ�
	m_elapsedTime = elapsedTime;

	// �G�����Ȃ��ꍇ�͏����Ȃ�
	if (m_enemies.empty()) return;

	// ���ׂĂ̓G�̍X�V����
	for (auto& enemy : m_enemies)
	{
		if(enemy.data == nullptr) continue;

		enemy.data->Update(elapsedTime);
	}
}

// --------------------------------
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
// --------------------------------
void EnemyManager::Render(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	if (m_enemies.empty()) return;

	// �S�u�����A�{�X�̕`��
	for (auto& enemy : m_enemies)
	{
		enemy.data->Render(view, projection);
	}
}

// --------------------------------
/// <summary>
/// �I������
/// </summary>
// --------------------------------
void EnemyManager::Finalize()
{
	if (m_enemies.empty()) return;

	// �S�u�����A�{�X�̉��
	for (auto& enemy : m_enemies)
	{
		enemy.data->Finalize();
	}
	m_enemies.clear();
}

// --------------------------------
/// <summary>
/// �G�̐�������
/// </summary>
/// <param name="position">���W</param>
/// <param name="type">���</param>
// --------------------------------
void EnemyManager::GenerateEnemy(const DirectX::SimpleMath::Vector3& position, EnemyType type)
{
	// �G�̐���
	switch (type)
	{
	case EnemyType::Goblin:	GenerateGoblin(position);	break;	// �S�u�����̐���
	case EnemyType::Boss:	GenerateBoss(position);		break;	// �{�X�̐���
	}
}

// --------------------------------
/// <summary>
/// �{�X�̎擾
/// </summary>
/// <returns>�{�X�̃|�C���^</returns>
// --------------------------------
Boss* EnemyManager::GetBossEnemy()
{
	// �{�X��T��
	for (auto& enemy : m_enemies)
	{
		if (enemy.type == EnemyType::Boss)
		{
			return dynamic_cast<Boss*>(enemy.data.get());
		}
	}

	return nullptr;
}

// --------------------------------
/// <summary>
/// �{�X�̍��W���擾
/// </summary>
/// <returns>�{�X�̍��W</returns>
// --------------------------------
DirectX::SimpleMath::Vector3 EnemyManager::GetBossPosition()
{
	// �{�X��T��
	for (auto& enemy : m_enemies)
	{
		if (enemy.type == EnemyType::Boss)
		{
			return enemy.data->GetPosition();
		}
	}
	// �{�X�����Ȃ���Ό��_��Ԃ�
	return DirectX::SimpleMath::Vector3::Zero;
}

// --------------------------------
/// <summary>
/// �^�[�Q�b�g���̍��W���擾
/// </summary>
/// <returns>�^�[�Q�b�g���̍��W</returns>
// --------------------------------
void* EnemyManager::GetPicupEnemyPosition()
{
	// �^�[�Q�b�g�̓G�̍��W���擾(�G�����Ȃ��ꍇ)
	m_targetPosition = DirectX::SimpleMath::Vector3{ 0.0f, 0.0f, 200.0f };
	// �G�����Ȃ��ꍇ�͂��̂܂ܕԂ�
	if (m_enemies.empty()) return &m_targetPosition;
	// �G�̔z����I�[�o�[���Ă���ꍇ��0�Ԃ�����
	if (m_enemies.size() - 1 < m_targetEnemyIndex) m_targetEnemyIndex = 0;
	// �^�[�Q�b�g�̓G�̍��W���擾	
	m_targetPosition = m_enemies[m_targetEnemyIndex].data->GetPosition();
	// ���W��Ԃ�
	return &m_targetPosition;
}

// --------------------------------
/// <summary>
/// �S�S�u������HP��0�ɂ���
/// </summary>
// --------------------------------
void EnemyManager::AllGoblinHPZero()
{
	// �S�u������HP��0�ɂ���
	for (auto& enemy : m_enemies)
	{
		if (enemy.type == EnemyType::Goblin)
		{
			// �ő�HP���̃_���[�W��S�̂ɗ^����
			enemy.data->GetHPSystem()->Damage(enemy.data->GetHPSystem()->GetHP());
		}
	}
}

// ---------------------------------------------
/// <summary>
/// �G1�̂��폜���鏈��
/// </summary>
/// <param name="pointer">�폜����Ώۂ̃|�C���^</param>
// ---------------------------------------------
void EnemyManager::DeleteEnemy(void* pointer)
{
	// �|�C���^��IEnemy�^�ɃL���X�g
	auto enemy = static_cast<IEnemy*>(pointer);

	// �G�̍폜
	m_enemies.erase(
		std::remove_if(m_enemies.begin(), m_enemies.end(),
			[enemy](const EnemyData& data) {
				if (data.data.get() == enemy)
				{
					data.data->Finalize();  // �G�̏I������
					return true;            // �폜�ΏۂƂ���
				}
				return false;               // �폜���Ȃ�
			}),
		m_enemies.end() // �z��̖������폜�͈͂Ƃ��Ďw��
	);
}


// --------------------------------
/// <summary>
/// �J�����̃^�[�Q�b�g��ύX
/// </summary>
// --------------------------------
void EnemyManager::ChangeCameraTarget()
{
	// �^�[�Q�b�g�̃C���f�b�N�X��ύX
	m_targetEnemyIndex++;
	// �C���f�b�N�X���G�̐��𒴂�����
	if (m_targetEnemyIndex >= m_enemies.size())
	{
		// �퓬�ɖ߂�
		m_targetEnemyIndex = 0;
	}
}

// --------------------------------
/// <summary>
/// �G���������Ă��邩�̔���
/// </summary>
/// <returns>�����Ftrue</returns>
// --------------------------------
bool EnemyManager::IsEnemysAlive()
{
	// �G�����Ȃ��ꍇ�N���A
	if (m_enemies.empty()) return false;

	// �{�X������ꍇ
	if (GetBossEnemy() != nullptr)
	{
		// �{�X��HP��0�ȉ��̏ꍇ
		if (GetBossEnemy()->GetHPSystem()->GetHP() <= 0)
		{
			// �o�ߎ��Ԃ����Z
			m_currentTime += m_elapsedTime;

			// �{�X������ł���̎��Ԃ���莞�Ԍo�߂�����false(���S)��Ԃ�
			return (m_currentTime <= BOSS_DEAD_DELAY);
		}
	}

	// �b�������Z�b�g
	m_currentTime = 0.0f;
	// ������
	return true;
}

// --------------------------------
/// <summary>
/// �S�G�ɍU���\�t���O��ݒ�
/// </summary>
/// <param name="flag">�ݒ肷��t���O</param>
// --------------------------------
void EnemyManager::AllEnemyCanHit(void* flag)
{
	// �S�G��T��
	for (auto& enemy : m_enemies)
	{
		enemy.data->CanHit(*static_cast<bool*>(flag));
	}
}

// --------------------------------
/// <summary>
/// �S�u�����̐���
/// </summary>
/// <param name="position">���W</param>
// --------------------------------
void EnemyManager::GenerateGoblin(const DirectX::SimpleMath::Vector3& position)
{
	// �S�u�����̐���
	auto goblin = Factory::CreateGoblin();
	// �ʒu�̐ݒ�
	goblin->SetPosition(position);
	// �z��Ɋi�[
	m_enemies.push_back(EnemyData{ EnemyType::Goblin, std::move(goblin) });
}

// --------------------------------
/// <summary>
/// �{�X�̐���
/// </summary>
/// <param name="position">���W</param>
// --------------------------------
void EnemyManager::GenerateBoss(const DirectX::SimpleMath::Vector3& position)
{
	// �{�X�̐���
	auto boss = Factory::CreateBoss();
	// �ʒu�̐ݒ�
	boss->SetPosition(position);
	// �z��Ɋi�[
	m_enemies.push_back(EnemyData{ EnemyType::Boss, std::move(boss) });
}

// --------------------------------
/// <summary>
/// Json�t�@�C���f�[�^�œG�𐶐�
/// </summary>
// --------------------------------
void EnemyManager::GenerateEnemyFromJson()
{
	// json�t�@�C����ǂݍ���
	std::ifstream file(ENEMY_JSON_PATH);

	// �f�[�^��o�^
	auto jsonFile = nlohmann::json::parse(file);

	// �X�e�[�W�̔ԍ����擾
	std::string stageKey = "stage" + std::to_string(m_selectQuestIndex);

	// �X�e�[�W�L�[�����݂��Ȃ��ꍇ
	if (!jsonFile.contains(stageKey))
	{
		MessageBoxA(nullptr, ("�w�肳�ꂽ�X�e�[�W�f�[�^��������܂���: " + stageKey).c_str(), "�G���[", MB_OK);
		return;
	}

	for (const auto& enemyData : jsonFile[stageKey])
	{
		// �G�̃^�C�v���擾
		std::string type = enemyData["type"];
		EnemyType enemyType = (type == "Goblin") ? EnemyType::Goblin : EnemyType::Boss;

		// ���W���擾
		float x = enemyData["position"]["x"];
		float y = enemyData["position"]["y"];
		float z = enemyData["position"]["z"];
		DirectX::SimpleMath::Vector3 position(x, y, z);

		// �G�̐���
		GenerateEnemy(position, enemyType);
	}

	if (m_selectQuestIndex == 0)
	{
		// �`���[�g���A���p�ɃX�e�[�g��ύX����
		auto goblin = dynamic_cast<Goblin*>(m_enemies[0].data.get());
		goblin->ChangeState(GoblinState::TUTORIAL);

		// �`���[�g���A���p�ɃX�e�[�g��ύX����
		goblin = dynamic_cast<Goblin*>(m_enemies[1].data.get());
		goblin->ChangeState(GoblinState::TUTORIAL);
	}
}