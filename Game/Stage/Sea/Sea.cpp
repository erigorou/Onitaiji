// -------------------------------------
// 
// ���O;	Sea.h
// ���e:	�C�̕`���S������N���X
// �쐬:	�r�c����
// 
// -------------------------------------
// �w�b�_�[�t�@�C��
#include "pch.h"
#include "Sea.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "../../Data/GameData.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
Sea::Sea()
	:
	m_totalTime{}
{
	Create();
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
Sea::~Sea()
{
}

// ---------------------------------------------------------
/// <summary>
/// �������s��
/// </summary>
// ---------------------------------------------------------
void Sea::Create()
{
	CommonResources* resources = CommonResources::GetInstance();
	auto device = resources->GetDeviceResources()->GetD3DDevice();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();

	// �J�X�^���V�F�[�_�[�Q�̐�������
	m_customShader = std::make_unique<CustomShader>
		(device,
			VS_PATH,
			PS_PATH,
			GS_PATH,
			InputElements
		);

	// �v���~�e�B�u�o�b�`�̐���
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	// �G���[�`�F�b�J�[�t��
	HRESULT hr = device->CreateBuffer(&bd, nullptr, &m_CBuffer);
	if (FAILED(hr)) {
		MessageBox(0, L"�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���.", NULL, MB_OK);
	}
}

// ---------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// ---------------------------------------------------------
void Sea::Render(DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix proj)
{
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();

	// ���_���(�|���S���̂S���_�̍��W���j
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(0.0f,  0.0f, 0.0f),
			DirectX::SimpleMath::Vector4(0.0f,0.0f,0.0f,1.0f),
			DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// �n���p�̃f�[�^���쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(DirectX::SimpleMath::Vector3(1000, 1000, 1));
	world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(-90));
	// �o�ߎ��Ԃ̍X�V
	m_totalTime += GameData::GetInstance()->GetElapsedTime();

	// �o�b�t�@�̍쐬
	ConstBuffer cbuff;
	cbuff.matWorld = world.Transpose();
	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.diffuse = DirectX::SimpleMath::Vector4(1, 1, 1, 1);
	cbuff.easing = DirectX::SimpleMath::Vector4(0, 0, 0, 0);
	cbuff.time = DirectX::SimpleMath::Vector4(m_totalTime, 0, 0, 0);

	// �󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	// �������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// �������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	// �J�����O�͍�����
	context->RSSetState(m_states->CullCounterClockwise());
	// �V�F�[�_�[�̓o�^
	m_customShader->BeginSharder(context);

	// �`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	// �V�F�[�_�[�̓o�^������
	m_customShader->EndSharder(context);
}
