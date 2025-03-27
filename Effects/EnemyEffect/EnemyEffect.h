// ** ---------------------------------------------------------**
//     �G���f���̎��S���E�_���[�W���̃G�t�F�N�g���Ǘ�����N���X
// ** ---------------------------------------------------------**
#pragma once
#include "pch.h"

class CustomShader;

class EnemyEffect
{
	// ----------------------------
	// �萔��\����
	// ----------------------------
public:
	// ���S���̃G�t�F�N�g�̎���
	static constexpr float DEAD_TIME = 2.5f;
	// �_���[�W���̃G�t�F�N�g�̎���
	static constexpr float DAMAGE_TIME = 0.5f;
	// ���S���̃V�F�[�_�[�p�X
	static constexpr wchar_t DEAD_PS_PATH[] = L"Resources/cso/DeadEffectPS.cso";
	static constexpr wchar_t DEAD_VS_PATH[] = L"Resources/cso/DeadEffectVS.cso";
	// �_���[�W�̃V�F�[�_�[�p�X
	static constexpr wchar_t DAMAGE_PS_PATH[] = L"Resources/cso/DamageEffectPS.cso";
	static constexpr wchar_t DAMAGE_VS_PATH[] = L"Resources/cso/DamageEffectVS.cso";
	// ���_���̓��C�A�E�g
	std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// �萔�o�b�t�@
	struct ConstBuffer
	{
		float Time; // ����
		DirectX::SimpleMath::Vector3 Padding;
	};

	enum class ENEMY_EFFECT
	{
		NONE,
		DAMAGE,
		DEAD
	};

	// ----------------------------
	// �A�N�Z�T
	// ----------------------------
public:
	// �ǂ̃G�t�F�N�g��K�p���邩
	void SetEffect(ENEMY_EFFECT effect);

	// ----------------------------
	// �����o�֐��i���J�j
	// ----------------------------
public:
	// �R���X�g���N�^
	EnemyEffect();
	// �f�X�g���N�^
	~EnemyEffect();
	// �X�V����
	void Update(float elapsedTime);
	// �̃p�[�c�̕`��
	void DrawWithEffect(
		DirectX::Model* model,
		const DirectX::SimpleMath::Matrix world,
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& proj
	);

	// ----------------------------
	// �����o�֐��i����J�j
	// ----------------------------
private:
	// �V�F�[�_�[�̐���
	void CreateShader();
	// �萔�o�b�t�@�̍쐬
	void CreateConstBuffer();
	// �萔�o�b�t�@�̍X�V����
	void UpdateConstBuffer(ConstBuffer* cb);

	// ----------------------------
	// �����o�ϐ�
	// ----------------------------
private:
	// �o�ߎ���
	float m_totalTime;
	// ���S���̃V�F�[�_�[
	std::unique_ptr<CustomShader> m_deadShader;
	// �_���[�W���̃V�F�[�_�[
	std::unique_ptr<CustomShader> m_damageShader;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer;
	// ���݂̃G�t�F�N�g
	ENEMY_EFFECT m_currentEffect;
};