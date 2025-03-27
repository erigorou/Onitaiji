// -------------------------------------------------------
//
// ���O:	CollisionManager
// ���e:	�Փ˔�����Ǘ�����N���X
//			�I�u�W�F�N�g��Collision��������
//			���̃N���X�ɓo�^����A
//			�����蔻��̍X�V���s��
// �쐬:	�r�c����
// 
// -------------------------------------------------------
#pragma once
#ifndef COLLISION_MANAGER
#define COLLISION_MANAGER

// �O���錾
class IObject;

// -------------------------------------------------------
/// <summary>
/// �I�u�W�F�N�g�̎��
/// </summary>
// -------------------------------------------------------
enum class ObjectType : UINT
{
	Player, Boss, Goblin, Sword, Cudgel, Stage
};

// -------------------------------------------------------
/// <summary>
/// �Փ˔���̎��
/// </summary>
// -------------------------------------------------------
enum class CollisionType : UINT
{
	OBB, Sphere
};

/// <summary>
/// �Փ˔�����i�[����\����
/// ObjectType : �I�u�W�F�N�g�̎��
/// CollisionType : �Փ˔���̌`��
/// IObject : ������
/// T : �Փ˔���
/// </summary>
/// <typeparam name="T">�Փ˔���</typeparam>
template<typename T>
struct CollisionData
{
	ObjectType objType;
	CollisionType colType;
	IObject* object;
	T* collision;

	// �R���X�g���N�^
	CollisionData(ObjectType objType, CollisionType collType, IObject* obj, T* collision)
		: objType(objType)
		, colType(collType)
		, object(obj)
		, collision(collision)
	{}
};

/// <summary>
/// �Փ˔�����폜����ۂɎg�p����\����
/// CollisionType : �Փ˔���̌`��
/// IObject : ������
/// </summary>
struct DeleteCollisionData
{
	CollisionType collType;
	IObject* object;
};

/// <summary>
/// �Փˎ��ɑ���ɓn���f�[�^
/// </summary>
struct InterSectData
{
	ObjectType objType;	// �I�u�W�F�N�g�̎��
	CollisionType colType; // �Փ˔���̌`��
	DirectX::BoundingSphere* collision; // �����蔻��̃|�C���^
};


/// <summary>
/// �Փ˔�����Ǘ�����N���X
/// </summary>
class CollisionManager
{
	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	CollisionManager();
	// �f�X�g���N�^
	~CollisionManager();
	// ����������
	void Initialize();
	// �X�V����
	void Update();
	// �`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);
	// �ǉ��֐�
	template<typename T>
	void AddCollision(void* args);
	// �폜�֐�
	void DeleteCollision(void* args);
	// �������֐�
	void Clear();

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �C�x���g�̓o�^
	inline void AddEventMessenger();
	// ���Ƌ��̓����蔻��
	inline void CheckCollisionSphereToSphere();
	// OBB�Ƌ��̓����蔻��
	inline void CheckCollisionOBBToSphere();
	// ���S���m�̏Փ˒ʒm
	inline bool IsGoblinCollision(
		CollisionData<DirectX::BoundingSphere> collisionA,
		CollisionData<DirectX::BoundingSphere> collisionB
	);
	// �Փ˔���̕`��
	inline void DrawCollision(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection
	);
	// �L�����E�{�b�N�X�̃v���L�V���̂𐶐�
	inline std::unique_ptr<DirectX::BoundingSphere> CreateProxySphere(
		const DirectX::BoundingOrientedBox* collision
	);

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �l�p�̓����蔻����i�[
	std::vector<CollisionData<DirectX::BoundingOrientedBox>> m_obbs;
	// ���̂̓����蔻����i�[
	std::vector<CollisionData<DirectX::BoundingSphere>> m_spheres;
	// OBB�Փ˔���̃v���L�V�p���̔�����i�[
	std::vector<std::unique_ptr<DirectX::BoundingSphere>> m_obbProxies;

	// �x�[�V�b�N�G�t�F�N�g
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitiveBatch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �`��t���O
	bool m_drawFlag;
	// �L�[�{�[�h�X�e�[�g
	DirectX::Keyboard::State m_keyboardState;
	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardStateTracker;
};

#endif // !COLLISION_MANAGER
