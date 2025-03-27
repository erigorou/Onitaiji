// ---------------------------------------------
// ���O:	Factory.cpp
// ���e:	�I�u�W�F�N�g�̐����E���������s���N���X
//			�g�p����L�[�������œo�^����
// �쐬:	�r�c
// ---------------------------------------------
#pragma once
#ifndef FACTORY
#define FACTORY
// �C���N���[�h
#include "pch.h"

// �O���錾
class PlayScene;
class IObserver;
class CollisionManager;
class Sound;
class Camera;
class SkySphere;
class Particle;
class Floor;
class Sea;
class Wall;
class Player;
class Boss;
class Goblin;
class Sword;
class Cudgel;
class Warning;
class PlaySceneUIManager;
class EnemyManager;
class QuestManager;

/// <summary>
/// �I�u�W�F�N�g�̐����N���X
/// </summary>
class Factory
{
// ------------------------------------------------
// �����o�֐�(���J)
// ------------------------------------------------
public:
	// �J�����̐���
	static std::unique_ptr<Camera> CreateCamera();
	// �p�[�e�B�N���̐���
	static std::unique_ptr<Particle> CreateParticle();
	// �V���̐���
	static std::unique_ptr<SkySphere> CreateSkySphere();
	// ���̐���
	static std::unique_ptr<Floor> CreateFloor();
	// �C�̐���
	static std::unique_ptr<Sea> CreateSea();
	// �ǂ̐���
	static std::unique_ptr<Wall> CreateWall();

	// �v���C���[�̐���
	static std::unique_ptr<Player> CreatePlayer();
	// �{�X�̐���
	static std::unique_ptr<Boss> CreateBoss();
	// ���S�̐���
	static std::unique_ptr<Goblin> CreateGoblin();
	// ���̐���
	static std::unique_ptr<Sword> CreateSword(Player* player);
	// ���_�̐���
	static std::unique_ptr<Cudgel> CreateCudgel(Boss* boss);

	// �Փ˔���}�l�[�W���[�̍쐬
	static std::unique_ptr<CollisionManager> CreateCollisionManager();
	// UI�}�l�[�W���[�̍쐬
	static std::unique_ptr<PlaySceneUIManager> CreateUIManager(PlayScene* playScene);
	// �G�}�l�[�W���[�̍쐬
	static std::unique_ptr<EnemyManager>		CreateEnemyManager();
	// �N�G�X�g�}�l�[�W���[�̍쐬
	static std::unique_ptr<QuestManager>		CreateQuestManager(PlayScene* playScene);
};

#endif // !FACTORY
