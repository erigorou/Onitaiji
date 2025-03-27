// ----------------------------------------------
//
//  ���O:  PlaySceneUIManager.h
//  ���e:  �v���C�V�[����UI���Ǘ�����N���X
//  �쐬:  �r�c����
//
// ----------------------------------------------
#ifndef PLAYSCENE_UI_MANAGER
#define PLAYSCENE_UI_MANAGER
#pragma once
// �C���N���[�h
#include "pch.h"

// �O���錾
class IUserInterface;
class PlayScene;
class Player;
class PlayerHPUI;
class EnemyHPUI;
class PlayerWarning;
class Operation;

/// <summary>
/// �v���C�V�[��UI�̃}�l�[�W���[
/// </summary>
class PlaySceneUIManager
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �v���C���[��HPUI�̍��W
	static const DirectX::SimpleMath::Vector2 PLAYER_HP_POSITION;

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	PlaySceneUIManager(PlayScene* playScene);
	// �f�X�g���N�^
	~PlaySceneUIManager();
	// �������֐�
	void Initialize();
	// �X�V�֐�
	void Update(float elapsedTime);
	// �`��֐�
	void Render();
	// �I���֐�
	void Finalize();

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// UI�̐����֐�
	void CreateUI();
	// �v���C���[��HPUI�̐����֐�
	void CreatePlayerHPUI();
	// �G�l�~�[��HPUI�̐����֐�
	void CreateEnemyHPUI();
	// �x��UI�̐����֐�
	void CreateWarning();
	// �������UI�̐����֐�
	void CreateOperation();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �v���C�V�[��
	PlayScene* m_playScene;
	// �v���C���[��HP
	std::unique_ptr<PlayerHPUI> m_playerHP;
	// �G�l�~�[��HP
	std::unique_ptr<EnemyHPUI> m_enemyHP;
	// �x��UI
	std::unique_ptr<PlayerWarning> m_warning;
	// �������UI
	std::unique_ptr<Operation> m_operation;
};

#endif
