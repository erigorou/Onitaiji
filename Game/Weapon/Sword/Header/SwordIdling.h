#pragma once
#include "pch.h"
#include "Interface/IWeapon.h"

class Sword;

/// <summary>
/// �����Y�������̑ҋ@���
/// </summary>
class SwordIdling : public IWeapon
{
	// -----------------------
	// �Œ�l
	// -----------------------
public:
	static constexpr float INIT_Y_ROT = DirectX::XMConvertToRadians(-90.0f);
	static constexpr float INIT_Z_ROT = DirectX::XMConvertToRadians(90.0f);

	// -----------------------
	// �����o�֐�(���J)
	// -----------------------
public:
	// �R���X�g���N�^
	SwordIdling(Sword* sword);
	// �f�X�g���N�^
	~SwordIdling();
	// ����������
	void Initialize()override;
	// ���O����
	void PreUpdate()override;
	// �X�V����
	void Update(float elapsedTime)override;
	// ���㏈��
	void PostUpdate()override;
	// �I������
	void Finalize()override;
	// �Փˏ���
	void HitAction(InterSectData data)override;

	// -------------------------
	// �����o�֐�(����J)
	// -------------------------
private:
	// ���[���h�s��̍X�V����
	void UpdateWorldMatrix();

	// -----------------------
	// �����o�ϐ�
	// -----------------------
private:
	// �\�[�h�̌����擾
	Sword* m_sword;
	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;
};