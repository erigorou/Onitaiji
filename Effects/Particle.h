// --------------------------------------------------------------------
// �p�[�e�B�N�����ꊇ�Ǘ�����N���X
// --------------------------------------------------------------------
#pragma once

#include "pch.h"
#include <list>

class CustomShader;
class DustTrailParticle;
class SwordTrailParticle;

class Particle
{
	// ----------------------------
	// �\����
	// ----------------------------
public:
	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};

	//	���_���̓��C�A�E�g
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// ----------------------------
	// �萔
	// ----------------------------
private:
	// �e�N�X�`����
	static constexpr const wchar_t* TEXTURE_NAME = L"dust.png";

	// �O�ՃV�F�[�_�[
	static constexpr  wchar_t SWORD_VS[] = L"Resources/cso/SwordTrailVS.cso";
	static constexpr  wchar_t SWORD_PS[] = L"Resources/cso/SwordTrailPS.cso";

	// �y���V�F�[�_�[
	static constexpr  wchar_t DUST_VS[] = L"Resources/cso/DustVS.cso";
	static constexpr  wchar_t DUST_PS[] = L"Resources/cso/DustPS.cso";
	static constexpr  wchar_t DUST_GS[] = L"Resources/cso/DustGS.cso";

	// �p�[�e�B�N���̍ő吔
	static constexpr int	MAX_SMASH_ATTACK_DUST = 25;
	// �y����Y���̍ŏ����x
	static constexpr float	MIN_SMASH_DUST_SPEED_Y = 1.0f;
	// �y����Y���̍ő呬�x
	static constexpr float	MAX_SMASH_DUST_SPEED_Y = 5.0f;
	// �y���̍ŏ����a
	static constexpr float  SMASH_DUST_RADIUS = 1.0f;

	// ----------------------------
	// �����o�֐��i���J�j
	// ----------------------------
public:
	// �R���X�g���N�^
	Particle();
	// �f�X�g���N�^
	~Particle();
	// �p�[�e�B�N���̐������s��
	void Create();
	// �p�[�e�B�N���̍X�V����
	void Update(float elapsedTimer, const DirectX::SimpleMath::Vector3 playerPosition, const DirectX::SimpleMath::Vector3 playerVelocity);
	// �p�[�e�B�N���̕`�揈��
	void Render(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix proj);
	// �r���{�[�h�s��̍쐬
	void CreateBillboard(
		DirectX::SimpleMath::Vector3 target,
		DirectX::SimpleMath::Vector3 eye,
		DirectX::SimpleMath::Vector3 up);
	// �O�Ղ̓y���𐶐����鏈��
	void CreateTrailDust();
	// ���̋O�Ղ𐶐����鏈��
	void CreateSwordTrail(void* ver);
	// ���������̉��p�[�e�B�N���̐���
	void CreateBashDust(void* center);

	// ----------------------------
	// �����o�֐��i����J�j
	// ----------------------------
private:
	// ���p�[�e�B�N���̕`��ݒ�
	void DrawSwordParticle(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	// ���p�[�e�B�N���̕`��ݒ�
	void DrawDustParticle(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::SimpleMath::Vector3 cameraDir);
	// �V�F�[�_�[�̍쐬
	inline void CreateShader();

	// ----------------------------
	// �����o�ϐ�
	// ----------------------------
private:
	// �o�b�t�@�[
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	//	�v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	//	�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �V�F�[�_�[
	std::unique_ptr<CustomShader> m_swordShader;
	std::unique_ptr<CustomShader> m_dustShader;
	// �r���{�[�h�s��
	DirectX::SimpleMath::Matrix m_billboard;
	// ���_�J���[�e�N�X�`���[
	std::vector<DirectX::VertexPositionColorTexture> m_dustVertices;
	// �J�����̍��W
	DirectX::SimpleMath::Vector3 m_cameraPosition;
	// �œ_
	DirectX::SimpleMath::Vector3 m_cameraTarget;
	// �O�Ճ_�X�g
	std::list<DustTrailParticle> m_dustTrail;
	// �O�Ճ_�X�g�̎���
	float m_timerDustTrail;
	// ���̋O�Ճp�[�e�B�N��
	std::list<SwordTrailParticle> m_swordTrail;
	// ���̋O�Ղ̎���
	float m_timerSwordTrail;
	// �v���C���[�̍��W
	DirectX::SimpleMath::Vector3 m_playerPosition;
	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_playerVelocity;
};