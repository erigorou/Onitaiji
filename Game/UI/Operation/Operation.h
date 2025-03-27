// --------------------------------------------
// 
// ���O:	Operation.h
// �@�\:	�������UI�̃N���X
//			�}�l�[�W���[�I�Ȗ���������
// ����:	�r�c����
// 
// --------------------------------------------
#ifndef OPERATION_DEFINED
#define OPERATION_DEFINED
#pragma once
// �C���N���[�h
#include "pch.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "OperateUI.h"
#include "../UI.h"

/// <summary>
/// �������UI�N���X
/// </summary>
class Operation
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
private:
	// HP�̍Œ�l
	static constexpr int LOW_HP = 2;
	// �t�F�[�h����
	static constexpr float FADE_TIME = 1.2f;
	// �L�[�p�X�̔z��
	static constexpr std::string_view keys[] = {
		"X_KEY",
		"SHIFT_KEY",
		"UP_KEY",
		"DOWN_KEY",
		"LEFT_KEY",
		"RIGHT_KEY"
	};

	// �e�L�X�g�̃e�N�X�`���L�[
	static constexpr std::string_view TEXT_KEY[] = { "TEXT_KEY" };

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
	Operation();
	// �f�X�g���N�^
	~Operation();
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
	// �V�F�[�_�[
	std::unique_ptr<CustomShader> m_customShader;
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// �X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// �e�N�X�`��
	std::vector<Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_texture;
	// �t���[������
	float m_elapsedTime;
	// �o�ߎ���
	float m_totalTime;
	// ����UI�z��
	std::vector<std::unique_ptr<OperateUI>> m_operateUIs;
	// UI
	std::unique_ptr<UI> m_textUI;
};

#endif // Operation_DEFINED
