// �v���C���[�i�����Y�j������

#pragma once
#include "Interface/IWeapon.h"
#include "Game/Scene/PlayScene.h"
#include "Interface/IObject.h"
#include "Game/Weapon/WeaponState.h"

class SwordIdling;
class SwordAttacking1;
class SwordAttacking2;
class Player;

class Sword : public IObject
{
	// ------------------------------------
	// �Œ�l
	// ------------------------------------
public:
	// ���̑傫��
	static const float SWORD_SCALE;
	// ���̈ʒu
	static constexpr DirectX::SimpleMath::Vector3 SWORD_DIR_FOR_PLAYER = { -1.5f, 1.0f, -2.0f };
	// ���f���̐�[�̍���
	static constexpr float MODEL_TOP_HEIGHT = 55.0f;
	// ���f���̍��{�̍���
	static constexpr float MODEL_ROOT_HEIGHT = 20.0f;

	// ------------------------------------
	// �A�N�Z�T
	// ------------------------------------
		// �v���C���[�̎擾
	Player* GetPlayer() { return m_player; }
	// ���[���h�s��̐ݒ�
	void SetWorldMatrix(DirectX::SimpleMath::Matrix mat) { m_worldMatrix = mat; }
	// �U���\���ǂ����̐ݒ�
	void SetAttackFlag(bool flag) { m_canAttack = flag; }
	// �U���\���ǂ���
	bool GetAttackFlag() { return m_canAttack; }
	// �ʒu�̃Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }
	// �����蔻��̈ʒu�̐ݒ�
	void SetCollisionPosition(DirectX::SimpleMath::Matrix mat) { m_originalBox.Transform(*m_collision.get(), mat); }

	// ------------------------------------
	// �����o�֐�(���J)
	// ------------------------------------
		// �R���X�g���N�^
	Sword(Player* player);
	// �f�X�g���N�^
	~Sword();
	// ������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);
	// �I������
	void Finalize();

	// �X�e�[�g���X�V����
	void ChangeState(void* state);

	// ���������Ƃ��̏���
	void HitAction(InterSectData data)  override;

	// ------------------------------------
	// �����o�֐�(����J)
	// ------------------------------------
private:
	// �X�e�[�g�𐶐�
	void CreateState();
	void CreateCollision();

	// ------------------------------------
	// �����o�ϐ�
	// ------------------------------------
private:
	// �v���C���[
	Player* m_player;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���f��
	DirectX::Model* m_model;
	// ���̓����蔻��P�i���ۂ̓����蔻��j
	std::unique_ptr<DirectX::BoundingOrientedBox> m_collision;
	// �I���W�i���̓����蔻��i�I���W�i���͐��������邾���̂��́j
	DirectX::BoundingOrientedBox m_originalBox;
	// �U���ł��邩�ǂ���
	bool m_canAttack;

	// ���݂̃X�e�[�g
	IWeapon* m_currentState;
	// �ҋ@���
	std::unique_ptr<SwordIdling> m_idling;
	// �U�����
	std::unique_ptr<SwordAttacking1> m_attacking1;
	// �U�����
	std::unique_ptr<SwordAttacking2> m_attacking2;
	// �ҋ@���[�V�������i�[����z��
	std::vector<IWeapon*> m_states;
};