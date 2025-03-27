// ------------------------------------------------------------------
// 
// ���O:	PlayerWarning.h
// �@�\:	HP�����l�ȉ��ɂȂ������Ɍx����\������N���X
// ����:	�r�c����
// 
// ------------------------------------------------------------------
#ifndef PLAYER_WARNING_DEFINED
#define PLAYER_WARNING_DEFINED
#pragma once
// �C���N���[�h
#include "pch.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"

// �O���錾
class HPSystem;

/// <summary>
/// �v���C���[HP�����l�ȉ��ɂȂ������Ɍx����\������N���X
/// </summary>
class PlayerWarning
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
private:
	// �t�@�C���p�X
	static constexpr wchar_t VS_PATH[] = L"Resources/cso/WarningVS.cso";
	static constexpr wchar_t PS_PATH[] = L"Resources/cso/WarningPS.cso";
	static constexpr wchar_t GS_PATH[] = L"Resources/cso/WarningGS.cso";

	// �x����\������HP�̒l
	static constexpr int LOW_HP = 2;
	// �t�F�[�h����
	static constexpr float FADE_TIME = 1.2f;

	// �C���v�b�g���C�A�E�g
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// �萔�o�b�t�@
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	diffuse;
		DirectX::SimpleMath::Vector4	easing;
		DirectX::SimpleMath::Vector4	time;
	};

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	PlayerWarning(HPSystem* hp);
	// �f�X�g���N�^
	~PlayerWarning();
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();
	// �I������
	void Finalize();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// HP�V�X�e��
	HPSystem* m_hp;
	// �V�F�[�_�[
	std::unique_ptr<CustomShader> m_customShader;
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// �X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �t���[������
	float m_elapsedTime;
	// �o�ߎ���
	float m_totalTime;
};

#endif // WARNING_DEFINED
