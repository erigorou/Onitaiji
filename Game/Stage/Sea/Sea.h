// -------------------------------------
// 
// ���O;	Sea.h
// ���e:	�C�̕`���S������N���X
// �쐬:	�r�c����
// 
// -------------------------------------

#ifndef SEA_H
#define SEA_H

#pragma once
// �C���N���[�h
#include "pch.h"

// �O���錾
class CustomShader;

/// <summary>
/// �C�̕`���S������N���X
/// </summary>
class Sea
{
	// -----------------------------
	// �萔
	// -----------------------------
public:
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix matWorld;  // ���[���h�s��
		DirectX::SimpleMath::Matrix matView;   // �r���[�s��
		DirectX::SimpleMath::Matrix matProj;   // �v���W�F�N�V�����s��
		DirectX::SimpleMath::Vector4 diffuse;  // �g�U���ːF
		DirectX::SimpleMath::Vector4 easing;   // �C�[�W���O�p�̃p�����[�^
		DirectX::SimpleMath::Vector4 time;     // ���Ԋ֘A�̃p�����[�^
	};

	// ���̓��C�A�E�g�i���_�t�H�[�}�b�g�j��`
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements =
	{
		// ���_�ʒu
		D3D11_INPUT_ELEMENT_DESC{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// ���_�J���[
		D3D11_INPUT_ELEMENT_DESC{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// �e�N�X�`�����W
		D3D11_INPUT_ELEMENT_DESC{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// �V�F�[�_�[�̃t�@�C���p�X
	static constexpr wchar_t VS_PATH[] = L"Resources/cso/VoronoiVS.cso";
	static constexpr wchar_t PS_PATH[] = L"Resources/cso/VoronoiPS.cso";
	static constexpr wchar_t GS_PATH[] = L"Resources/cso/VoronoiGS.cso";

	// -----------------------------
	// ���J�����o�֐�
	// -----------------------------
public:
	// �R���X�g���N�^
	Sea();
	// �f�X�g���N�^
	~Sea();

	// �`�揈��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	// -----------------------------
	// ����J�����o�֐�
	// -----------------------------
private:
	// ���\�[�X�̐�������
	void Create();

	// -----------------------------
	// ����J�����o�ϐ�
	// -----------------------------
private:
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// �X�e�[�g�I�u�W�F�N�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �J�X�^���V�F�[�_�[
	std::unique_ptr<CustomShader> m_customShader;

	// ���v����
	float m_totalTime;
};

#endif // SEA_H
