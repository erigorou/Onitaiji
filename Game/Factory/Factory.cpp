// ---------------------------------------------
// ���O:	Factory.cpp
// ���e:	�I�u�W�F�N�g�̐����E���������s���N���X
//			�g�p����L�[�������œo�^����
// �쐬:	�r�c
// ---------------------------------------------


#include "pch.h"
#include "Factory.h"
#include "../Messenger/KeyboardMessenger.h"		// �L�[���̓��b�Z���W���[
#include "../Messenger/EventMessenger.h"		// �C�x���g���b�Z���W���[
#include "../Scene/PlayScene.h"								// �v���C�V�[��
#include "../Camera/Camera.h"								// �J����
#include "Effects/Particle.h"								// �p�[�e�B�N��
#include "../Stage/SkySphere/SkySphere.h"					// �V��
#include "../Stage/Floor/Floor.h"							// ��
#include "../Stage/Sea/Sea.h"								// �C
#include "../Stage/Wall/Wall.h"								// ��
#include "../Player/Player.h"								// �v���C���[
#include "../Boss/Boss.h"									// �S�i�G�j
#include "../Goblin/Goblin.h"								// �S�u����
#include "../Weapon/Sword/Sword.h"							// �v���C���[�̕���
#include "../Weapon/Cudgel/Cudgel.h"						// �S�i�G�j�̕���
#include "Libraries/MyLib/Collision/CollisionManager.h"		// �����蔻�蓝��
#include "../UI/!PlaySceneUIManager/PlaySceneUIManager.h"	// �v���C�V�[����UI
#include "../EnemyManager/EnemyManager.h"					// �G�}�l�[�W���[
#include "../Quest/QuestManager.h"							// �N�G�X�g�}�l�[�W���[

// ---------------------------------------------
/// <summary>
/// �Փ˔���̐����֐�
/// </summary>
/// <returns>�Փ˔���̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<CollisionManager> Factory::CreateCollisionManager()
{
	// �����蔻�蓝����錾����
	std::unique_ptr<CollisionManager> collisionManager;
	collisionManager = std::make_unique<CollisionManager>();
	// �����蔻�蓝���̐ݒ�
	return collisionManager;
}

// ---------------------------------------------
/// <summary>
/// �J�����̐����֐�
/// </summary>
/// <returns>�J�����̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Camera> Factory::CreateCamera()
{
	// �J������錾����
	std::unique_ptr<Camera> camera;
	camera = std::make_unique<Camera>();

	// �J�����̐ݒ�
	return camera;
}

// ---------------------------------------------
/// <summary>
/// �V���̐����֐�
/// </summary>
/// <returns>�V���̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<SkySphere> Factory::CreateSkySphere()
{
	// �V����錾����
	std::unique_ptr<SkySphere> skySphere;
	skySphere = std::make_unique<SkySphere>();
	// ����������
	skySphere->LoadSkySphereModel();
	// �V���̐ݒ�
	return skySphere;
}

// ---------------------------------------------
/// <summary>
/// �p�[�e�B�N���̐����֐�
/// </summary>
/// <returns>�p�[�e�B�N���̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Particle> Factory::CreateParticle()
{
	// �p�[�e�B�N����錾����
	std::unique_ptr<Particle> particle;
	particle = std::make_unique<Particle>();
	// ����������
	particle->Create();
	// �p�[�e�B�N���̐ݒ�
	return particle;
}

// ---------------------------------------------
/// <summary>
/// ���̐����֐�
/// </summary>
/// <returns>���̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Floor> Factory::CreateFloor()
{
	// ����錾����
	std::unique_ptr<Floor> floor;
	floor = std::make_unique<Floor>();
	// ���̐ݒ�
	return floor;
}

// ---------------------------------------------
/// <summary>
/// �C�̐����֐�
/// </summary>
/// <returns>�C�̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Sea> Factory::CreateSea()
{
	std::unique_ptr<Sea> sea;
	sea = std::make_unique<Sea>();
	return sea;
}

// ---------------------------------------------
/// <summary>
/// �ǂ̐����֐�
/// </summary>
/// <returns>�ǂ̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Wall> Factory::CreateWall()
{
	// �ǂ�錾����
	std::unique_ptr<Wall> wall;
	wall = std::make_unique<Wall>();
	// ����������
	wall->Initialize();
	// �ǂ̐ݒ�
	return wall;
}

// ---------------------------------------------
/// <summary>
/// �v���C���[�̐����֐�
/// </summary>
/// <returns>�v���C���[�̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Player> Factory::CreatePlayer()
{
	// �v���C���[��錾����
	std::unique_ptr<Player> player;
	// �v���C���[�𐶐�����
	player = std::make_unique<Player>();
	// ����������
	player->Initialize();
	// �L�[��o�^
	KeyboardMessenger::Attach(DirectX::Keyboard::X,			player.get(), KeyboardMessenger::KeyPressType::PRESSED);
	KeyboardMessenger::Attach(DirectX::Keyboard::LeftShift, player.get(), KeyboardMessenger::KeyPressType::PRESSED);
	KeyboardMessenger::Attach(DirectX::Keyboard::Left,		player.get(), KeyboardMessenger::KeyPressType::DOWN);
	KeyboardMessenger::Attach(DirectX::Keyboard::Right,		player.get(), KeyboardMessenger::KeyPressType::DOWN);
	KeyboardMessenger::Attach(DirectX::Keyboard::Up,		player.get(), KeyboardMessenger::KeyPressType::DOWN);
	KeyboardMessenger::Attach(DirectX::Keyboard::Down,		player.get(), KeyboardMessenger::KeyPressType::DOWN);

	return player;
}

// ---------------------------------------------
/// <summary>
/// �S�i�G�j�̐����֐�
/// </summary>
/// <returns>�S�i�G�j�̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Boss> Factory::CreateBoss()
{
	// �S�i�G�j��錾����
	std::unique_ptr<Boss> boss;
	boss = std::make_unique<Boss>();
	// ����������
	boss->Initialize();

	// �S�i�G�j�̐ݒ�
	return boss;
}

// ---------------------------------------------
/// <summary>
/// �S�u�����̐����֐�
/// </summary>
/// <returns>�S�u�����̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Goblin> Factory::CreateGoblin()
{
	// �S�u�����̐錾
	std::unique_ptr<Goblin> goblin;
	goblin = std::make_unique<Goblin>();
	// ����������
	goblin->Initialize();
	// �S�u�����̐ݒ�
	return goblin;
}

// ---------------------------------------------
/// <summary>
/// �v���C���[�̕���̐����֐�
/// </summary>
/// <param name="player">�v���C���[�̃|�C���^</param>
/// <returns>�v���C���[�̕���̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Sword> Factory::CreateSword(Player* player)
{
	// �v���C���[�̕����錾����
	std::unique_ptr<Sword> sword;
	sword = std::make_unique<Sword>(player);
	// ����������
	sword->Initialize();

	// �v���C���[�̕���̃X�e�[�g��ύX
	EventMessenger::Attach(EventList::ChangeSwordState, std::bind(&Sword::ChangeState, sword.get(), std::placeholders::_1));

	// �v���C���[�̕���̐ݒ�
	return sword;
}

// ---------------------------------------------
/// <summary>
/// �S�i�G�j�̕���̐����֐�
/// </summary>
/// <param name="boss">�S�i�G�j�̃|�C���^</param>
/// <returns>�S�i�G�j�̕���̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<Cudgel> Factory::CreateCudgel(Boss* boss)
{
	// �S�i�G�j�̕����錾����
	std::unique_ptr<Cudgel> cudgel;

	cudgel = std::make_unique<Cudgel>(boss);
	// ����������
	cudgel->Initialize();
	// �S�i�G�j�̕���̐ݒ�
	return cudgel;
}

// ---------------------------------------------
/// <summary>
/// �v���C�V�[����UI�̐����֐�
/// </summary>
/// <param name="playScene">�v���C�V�[���̃|�C���^</param>
/// <returns>�v���C�V�[����UI�}�l�[�W���[�̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<PlaySceneUIManager> Factory::CreateUIManager(PlayScene* playScene)
{
	// �v���C�V�[����UI��錾����
	std::unique_ptr<PlaySceneUIManager> uiManager;
	uiManager = std::make_unique<PlaySceneUIManager>(playScene);
	// ����������
	uiManager->Initialize();
	// �v���C�V�[����UI�̐ݒ�
	return uiManager;
}

// ---------------------------------------------
/// <summary>
/// �G�}�l�[�W���[�̐����֐�
/// </summary>
/// <returns>�G�}�l�[�W���[�̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<EnemyManager> Factory::CreateEnemyManager()
{
	// �G�}�l�[�W���[��錾����
	std::unique_ptr<EnemyManager> enemyManager;
	enemyManager = std::make_unique<EnemyManager>();
	// ����������
	enemyManager->Initialize();
	// �G�}�l�[�W���[�̐ݒ�
	return enemyManager;
}

// ---------------------------------------------
/// <summary>
/// �N�G�X�g�}�l�[�W���[�̐����֐�
/// </summary>
/// <param name="playScene">�v���C�V�[���̃|�C���^</param>
/// <returns>�N�G�X�g�}�l�[�W���[�̃|�C���^</returns>
// ---------------------------------------------
std::unique_ptr<QuestManager> Factory::CreateQuestManager(PlayScene* playScene)
{
	// �N�G�X�g�}�l�[�W���[��錾����
	std::unique_ptr<QuestManager> questManager;
	questManager = std::make_unique<QuestManager>(playScene);
	// ����������
	questManager->InitializeQuest();
	// �N�G�X�g�}�l�[�W���[�̐ݒ�
	return questManager;
}