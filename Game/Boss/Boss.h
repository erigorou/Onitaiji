// -----------------------------------------------------
// ���O:	Boss.cpp
// ���e:	�{�X����������N���X
//			�X�e�[�g��Փ˔�����Ǘ�
// �쐬:	�r�c����
// -----------------------------------------------------
#pragma once
// �C���N���[�h
#include "Interface/IState.h"
#include "Interface/IFace.h"
#include "Interface/IEnemy.h"

// �O���錾
class PlayScene;
class EnemyEffect;
class HPSystem;
class Cudgel;
// ��
class BossFaceIdling;
class BossFaceAttacking;
// �X�e�[�g
class BossStarting;
class BossIdling;
class BossAttacking;
class BossSweeping;
class BossDashAttacking;
class BossApproaching;
class BossDead;

// �G�̏��
enum class BossState
{
	Starting = 0,	// �J�n���
	Idling,			// �ҋ@���
	Attacking,		// ���������U��
	Sweeping,		// �ガ�����U��
	DashAttacking,	// �ˌ����
	Approaching,	// �ǔ����
	Dead,			// ���S���
};

// ��̏��
enum class FaceState
{
	Idling = 0,	// �ҋ@
	Attacking,	// �U��
};

/// <summary>
/// �{�X�̃X�e�[�g
/// </summary>
class Boss : public IEnemy
{
	// --------------------------------
	//  �Œ�l
	// --------------------------------
public:
	// ����
	static constexpr float BOSS_SPEED = 0.1f;
	// �傫��
	static constexpr float BOSS_SCALE = 0.6f;
	// �U���̃N�[���^�C��
	static constexpr float COOL_TIME = 0.3f;
	// �Փ˔����Y���W
	static constexpr float COLISION_POS_Y = 10.0f;
	// �ő�HP
	static constexpr float HP = 25.0f;
	// �����蔻��̑傫��
	static constexpr float COLLISION_RADIUS = 20.0f;
	// �{�X�̍���
	static constexpr float BOSS_HEIGHT = 50.0f;

	// �J�����̗h��鋭��
	static constexpr float SHAKE_POWER = 0.25f;

	// --------------------------------
	//  �A�N�Z�T�֐�
	// --------------------------------
public:
	// HP�̎擾�E�ݒ�
	HPSystem* GetBossHP() const { return m_hp.get(); }
	HPSystem* GetHPSystem() override { return m_hp.get(); }

	// ���W�̎擾�E�ݒ�
	DirectX::SimpleMath::Vector3 GetPosition() override { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3 pos) { m_position = pos; }

	// ��]�p�̎擾�E�ݒ�
	float GetAngle() const { return m_angle; }
	void SetAngle(const float angle) { m_angle = angle; }

	// �̂̌X���̎擾�E�ݒ�
	float GetBodyTilt() const { return m_bodyTilt; }
	void SetBodyTilt(const float tilt) { m_bodyTilt = tilt; }

	// �Փˉ\
	void CanHit(bool flag) override { m_canHit = flag; }

public:
	// ���̃_���[�W���󂯂鋖���o��
	void CanHitSword() { m_canHit = true; }
	// ���̃_���[�W���󂯂鋖��������
	void CanNotHitSword() { m_canHit = false; }

	// --------------------------------
	//  �����o�֐�(���J)
	// --------------------------------
public:
	// �R���X�g���N�^
	Boss();
	// �f�X�g���N�^
	~Boss();
	// ����������
	void Initialize();
	// ��Ԃ�ύX����
	void ChangeState(void* state);
	// ���ύX����
	void ChangeFace(void* face);
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	// �I������
	void Finalize();
	// ���S�������s��
	void DeadAction();
	// ���������Ƃ��̏���
	void HitAction(InterSectData data)override;

	// --------------------------------
	//  �����o�֐�(����J)
	// --------------------------------
private:
	// ���[���h�s��̌v�Z
	void CalcrationWorldMatrix();
	// �X�e�[�g�̍쐬����
	void CreateState();
	// ��̍쐬����
	void CreateFace();
	// �����蔻��̐�������
	void CreateCollision();
	// �C�x���g�̓o�^
	void AttachEvent();
	// ���̏Փ˔���
	void HitSword(InterSectData data);
	// �X�e�[�W�̏Փ˔���
	void HitStage(InterSectData data);
	// ���S����
	void CheckAlive();

	// --------------------------------
	//  �����o�ϐ�
	// --------------------------------
private:
	// ����
	std::unique_ptr<Cudgel> m_cudgel;
	// �ʒu
	DirectX::SimpleMath::Vector3 m_position;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// �p�x
	float m_angle;
	// �̂̌X��
	float m_bodyTilt;
	// �G�p�̃��[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// HP
	std::unique_ptr<HPSystem> m_hp;

	// ���݂̃X�e�[�g�i�X�e�[�g�p�^�[���j
	IState* m_currentState;
	// �J�n���
	std::unique_ptr<BossStarting> m_starting;
	// �ҋ@���
	std::unique_ptr<BossIdling> m_idling;
	// �U�����
	std::unique_ptr<BossAttacking> m_attacking;
	// �ガ�������
	std::unique_ptr<BossSweeping> m_sweeping;
	// �ˌ����
	std::unique_ptr<BossDashAttacking> m_dashAttacking;
	// �ǔ����
	std::unique_ptr<BossApproaching> m_approaching;
	// ���S���
	std::unique_ptr<BossDead> m_dead;
	// ��Ԃ̔z��
	std::vector<IState*> m_states;

	// ���݂̊�
	IFace* m_currentFace;
	// �ҋ@��
	std::unique_ptr<BossFaceIdling>	m_faceIdling;
	// �U����
	std::unique_ptr<BossFaceAttacking>	m_faceAttacking;
	// ��̔z��
	std::vector<IFace*> m_faces;

	// �G�̃_���[�W�G�t�F�N�g
	std::unique_ptr<EnemyEffect> m_effect;
	// ���f��
	DirectX::Model* m_model;
	//�@�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �����߂��ʂ̌v�Z
	DirectX::SimpleMath::Vector3 m_pushBackValue;
	// �̂̓����蔻��
	std::unique_ptr<DirectX::BoundingSphere> m_bodyCollision;
	// �Փˉ\��
	bool m_canHit;
	// �J�����̗h�炷������
	float m_shakePower;
};
