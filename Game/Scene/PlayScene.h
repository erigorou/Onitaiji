// ------------------------------------------------------------------------------
// 
// ���O:	PlayScene
// ���e:	�v���C�V�[���̃I�u�W�F�N�g�𐶐����A�X�V�A�`����s��
// ����:	�r�c����
// 
// ------------------------------------------------------------------------------
#pragma once
// �C���N���[�h
#include "IScene.h"
#include "Interface/IObserver.h"

// �O���錾
class CommonResources;
class Sound;
class HitStop;
class Player;
class Sword;
class Boss;
class Cudgel;
class Goblin;
class Floor;
class Sea;
class Wall;
class SkySphere;
class PlaySceneUIManager;
class CollisionManager;
class EnemyManager;
class QuestManager;
class Particle;
class Camera;

/// <summary>
/// �v���C�V�[�����X�V�E�`�悷��N���X
/// </summary>
class PlayScene final : public IScene, public IObserver
{
	// --------------------------
	// �Œ�l
	// --------------------------
public:
	// �L�[�{�[�h�̃L�[�̍ő�l
	static constexpr int MAX_KEY = 256;
	// ����p
	static constexpr float FOV = 45.0f;
	// ������
	static constexpr float NEAR_Z = 0.1f;
	static constexpr float FAR_Z = 50000.0f;

	// --------------------------
	// �A�N�Z�T
	// --------------------------
public:
	// �v���C���[���擾
	Player* GetPlayer() { return m_player.get(); }
	// �{�X�S���擾
	Boss* GetBoss();
	// �G�̃}�l�[�W���[���擾
	EnemyManager* GetEnemyManager() { return m_enemyManager.get(); }
	// �N�G�X�g�}�l�[�W���[���擾
	QuestManager* GetQuestManager() { return m_questManager.get(); }
	// �X�N�V�������
	void TakeCapture() { m_isScreenShot = true; }

	// --------------------------
	// �����o�֐�(���J)
	// --------------------------
public:
	// �R���X�g���N�^
	PlayScene();
	// �f�X�g���N�^
	~PlayScene() override;
	// ������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime) override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;
	// ���U���g�V�[���ւ̑J��
	void ChangeResultScene();
	// �L�[�{�[�h�̓��͌��m
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �L�[�{�[�h�̓��͌��m
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;

	// --------------------------
	// �����o�֐�(����J)
	// --------------------------
private:
	// �I�u�W�F�N�g�̐���
	void CreateObjects();
	// ���̃V�[��ID���擾
	SceneID GetNextSceneID()const;
	// �O�̃V�[��ID���擾
	SceneID GetPrevSceneID()const;

	// �I�u�W�F�N�g�̍X�V
	void UpdateObjects(float elapsedTime);
	// �J�����̍X�V
	void UpdateCamera(float elapsedTime);
	// �L�[�{�[�h�̍X�V
	void UpdateKeyboard();

	// �p�[�e�B�N���̕`��
	void DrawParticle(const DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix projection);
	// �Q�[���I�[�o�[����
	void GameOverChacker();

	// �X�N���[���V���b�g�����
	void TakeScreenShot();

	// --------------------------
	// �����o�ϐ�
	// --------------------------
private:
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;
	// �V�[���J�ڃt���O
	bool m_isChangeScene;
	// �T�E���h�}�l�[�W���[
	Sound* m_sound;
	// UI�}�l�[�W���[
	std::unique_ptr<PlaySceneUIManager> m_uiManager;
	// �����蔻��}�l�[�W���[
	std::unique_ptr<CollisionManager> m_collisionManager;
	// �G�}�l�[�W���[
	std::unique_ptr<EnemyManager> m_enemyManager;
	// �q�b�g�X�g�b�v�}�l�[�W���[
	HitStop* m_hitStop;
	// �N�G�X�g�}�l�[�W���[
	std::unique_ptr<QuestManager> m_questManager;
	// �J����
	std::unique_ptr<Camera> m_camera;
	// �V��
	std::unique_ptr<SkySphere> m_skySphere;
	// �p�[�e�B�N��
	std::unique_ptr<Particle> m_particles;
	// �v���C���[
	std::unique_ptr<Player> m_player;
	// ��
	std::unique_ptr<Floor> m_floor;
	// �C
	std::unique_ptr<Sea> m_sea;
	// ��
	std::unique_ptr<Wall> m_wall;
	// �q�b�g�X�g�b�v�̂�����I�u�W�F�N�g�p�̕ϐ�
	float m_smoothDeltaTime;
	// �^�����摜�݂̂̕`�挋�ʂ����摜�̃V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_captureSRV;
	// �X�N�V�������t���O
	bool m_isScreenShot;
};
