// -----------------------------------------------------------------
// 
// ���O: Wall.cpp
// ���e: �X�e�[�W�̋��E�ǂ�`�悷��N���X
// �쐬: �r�c����
// 
// -----------------------------------------------------------------

#pragma once
// �C���N���[�h
#include "Interface/IObject.h"

/// <summary>
/// �X�e�[�W�̋��E�ǂ�`�悷��N���X
/// </summary>
class Wall : public IObject
{
	// ------------------------
	// �Œ�l
	// ------------------------
public:
	// �傫���i�Œ�l�j
	static constexpr float WALL_SCALE = 2.0f;
	// �����蔻��̔��a
	static constexpr float COLLISION_RADIUS = 160.0f;
	// �����蔻��̑傫��
	static constexpr float COLLISION_SCALE = 10.0f;
	// ���f�����ړ�������ʒu
	static constexpr DirectX::SimpleMath::Vector3 WALL_POS = { 0.0f, -60.0f, 0.0f };

	// ------------------------
	// �����o�֐�(���J)
	// ------------------------
public:
	// �ǂ̏Փ˔�����擾
	DirectX::BoundingSphere* GetCollision() { return m_collision.get(); }
	// �ǂ̍��W�̎擾
	DirectX::SimpleMath::Vector3 GetPosition() override { return DirectX::SimpleMath::Vector3::Zero; }
	// �R���X�g���N�^
	Wall();
	// �f�X�g���N�^
	~Wall();
	// ������
	void Initialize();
	// �`�揈��
	void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection
	);
	// �I������
	void Finalize();
	// �Փˏ���
	void HitAction(InterSectData data)override;

	// ------------------------
	// �����o�֐�(����J)
	// ------------------------
private:
	// �Փ˔���̐���
	void CreateCollision();
	// ���[���h�s��X�V����
	void UpdateWorldMatrix();

	// ------------------------
	// �����o�ϐ�
	// ------------------------
private:
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// ���f��
	DirectX::Model* m_model;
	// �����蔻��
	std::unique_ptr<DirectX::BoundingSphere> m_collision;
	// �O�̓����蔻��Ɍ����Ă�����
	std::unique_ptr<DirectX::BoundingSphere> m_overCollision;
};
