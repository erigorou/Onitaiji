// ------------------------------------------------------------------
// 
// ���O:	PlayerWarning.cpp
// �@�\:	HP�����l�ȉ��ɂȂ������Ɍx����\������N���X
// ����:	�r�c����
// 
// ------------------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "PlayerWarning.h"
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Game/Data/HPSystem.h"
#include "CommonStates.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="hp">HP�V�X�e��</param>
// ---------------------------------------------------------
PlayerWarning::PlayerWarning(HPSystem* hp)
	:
	m_hp(hp),
	m_customShader{},
	m_CBuffer{},
	m_states{},
	m_batch{},
	m_texture{},
	m_elapsedTime{},
	m_totalTime{}
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
PlayerWarning::~PlayerWarning()
{
	Finalize();
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------
void PlayerWarning::Initialize()
{
	ID3D11Device* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �V�F�[�_�[�̐���
	m_customShader = std::make_unique<CustomShader>
		(
			device,
			VS_PATH,
			PS_PATH,
			GS_PATH,
			InputElements
		);

	// �v���~�e�B�u�o�b�`�̐���
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>
		(
			CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext()
		);

	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);

	// �e�N�X�`�����擾
	m_texture = GameResources::GetInstance()->GetTexture("warning");

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = device->CreateBuffer(&bd, nullptr, &m_CBuffer);
	if (FAILED(hr)) {
		MessageBox(0, L"�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���.", NULL, MB_OK);
	}
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void PlayerWarning::Update(float elapsedTime)
{
	if (m_hp->GetHP() > LOW_HP)
		return;

	// �o�ߎ��Ԃ̉��Z
	m_totalTime += elapsedTime;
}

// ---------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// ---------------------------------------------------------
void PlayerWarning::Render()
{
	using namespace DirectX;
	ID3D11DeviceContext* context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// ���_���
	VertexPositionColorTexture vertex[4] =
	{ VertexPositionColorTexture(SimpleMath::Vector3::Zero,SimpleMath::Vector4::One,XMFLOAT2(0.0f, 0.0f)) };

	// �o�b�t�@�̍쐬
	ConstBuffer cbuff;
	cbuff.matWorld = SimpleMath::Matrix::Identity;
	cbuff.matView = SimpleMath::Matrix::Identity;
	cbuff.matProj = SimpleMath::Matrix::Identity;
	cbuff.diffuse = SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	cbuff.easing = SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	cbuff.time = SimpleMath::Vector4(m_totalTime, 0.0f, 0.0f, 0.0f);

	// �R���X�^���g�o�b�t�@�̐ݒ�
	context->UpdateSubresource(m_CBuffer.Get(), 0, nullptr, &cbuff, 0, 0);

	// �V�F�[�_�[�̊J�n
	m_customShader->BeginSharder(context);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	// �T���v���[�X�e�[�g�̐ݒ�
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// �u�����h�X�e�[�g�̐ݒ�
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	context->RSSetState(m_states->CullNone());

	// �e�N�X�`���̐ݒ�
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	// �`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	// �V�F�[�_�[�̏I��
	m_customShader->EndSharder(context);
}

// ---------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------------------
void PlayerWarning::Finalize()
{
}