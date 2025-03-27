//--------------------------------------------------------------------------------------
// 
// ���O: UserInterface.cpp
// �@�\: UI��\������N���X
// ����: �r�c����
//
//-------------------------------------------------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "DeviceResources.h"
#include "Game/UI/UIAnchor.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Interface/IAction.h"

/// <summary>
/// UI�̕\�����s���N���X
/// </summary>
class UserInterface
{
	// ------------------------------
	// �萔
	// ------------------------------
public:
	//�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector2 windowSize;
		float alpha;
		float padding;
	};
	// �C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// �E�B���h�E�T�C�Y
	static constexpr DirectX::SimpleMath::Vector2 WINDOW_SIZE = DirectX::SimpleMath::Vector2(1280.0f, 720.0f);

	// �V�F�[�_�[�̃t�@�C���p
	static constexpr wchar_t VS_PATH[] = L"Resources/cso/UIVS.cso";
	static constexpr wchar_t PS_PATH[] = L"Resources/cso/UIPS.cso";
	static constexpr wchar_t GS_PATH[] = L"Resources/cso/UIGS.cso";

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	UserInterface();
	// �f�X�g���N�^
	~UserInterface();
	// UI�̐�������
	void Create(
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		ANCHOR anchor,
		IAction* action
	);
	// �X�V����
	void Update(const float time);
	// �`�揈��
	void Render();

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �e�N�X�`���̃T�C�Y���擾
	void GetTextureSize(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv);
	// �V�F�[�_�[�̐���
	void CreateShader();

	// ------------------------------
	// �����o�ϐ�
	// ------------------------------
private:
	// �o�ߎ���
	float m_totalTime;
	// �萔�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	//�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �E�B���h�E�̃T�C�Y
	DirectX::SimpleMath::Vector2 m_windowSize;
	// �e�N�X�`���̃T�C�Y
	DirectX::SimpleMath::Vector2 m_textureSize;
	// �X�P�[��
	DirectX::SimpleMath::Vector2 m_scale;
	// ���W
	DirectX::SimpleMath::Vector2 m_position;
	// �A���t�@�l
	float m_alpha;
	// �V�F�[�_�[
	std::unique_ptr<CustomShader> m_shader;
	// �A���J�[
	ANCHOR m_anchor;
	// �A�N�V����
	IAction* m_action;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};