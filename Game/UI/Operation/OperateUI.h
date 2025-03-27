// --------------------------------------------
// ���O:	OperateUI.cpp
// �@�\:	�������UI�̃N���X
// ����:	�r�c����
// --------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "Interface/IObject.h"
#include "Interface/IObserver.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"


class OperateUI : public IObserver, public IObject
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �V�F�[�_�[�t�@�C���̃p�X
	static constexpr wchar_t VS_PATH[] = L"Resources/cso/OperationVS.cso";
	static constexpr wchar_t PS_PATH[] = L"Resources/cso/OperationPS.cso";
	static constexpr wchar_t GS_PATH[] = L"Resources/cso/OperationGS.cso";

	// �t�F�[�h����
	static constexpr float DOWN_FADE_TIME = 0.01667f * 10.0f;

	// �C���v�b�g���C�A�E�g
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// �t�F�[�h�̎���
	static constexpr float FADE_TIME = 1.2f;

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
	OperateUI(std::string_view key);
	// �f�X�g���N�^
	~OperateUI();
	// ����������
	void Initialize();
	// �`�揈��
	void Render();
	// �I������
	void Finalize();
	// �ǂ̃L�[�������ꂽ��
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �ǂ̃L�[��������Ă��邩
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;
	// �Փ˔���
	void HitAction(InterSectData data) override;
	// ���W�擾
	DirectX::SimpleMath::Vector3 GetPosition() override;

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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �t���[������
	float m_elapsedTime;
	// �o�ߎ���
	float m_totalTime;
	// �L�[�������ꂽ��
	bool m_downKey;
};