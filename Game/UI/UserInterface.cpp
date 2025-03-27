//--------------------------------------------------------------------------------------
// 
// ���O: UserInterface.cpp
// �@�\: UI��\������N���X
// ����: �r�c����
//
//-------------------------------------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "UserInterface.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Interface/IAction.h"

// ---------------------------------------------------------
// �萔
// ---------------------------------------------------------

// �C���v�b�g���C�A�E�g
const std::vector<D3D11_INPUT_ELEMENT_DESC> UserInterface::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
UserInterface::UserInterface()
	:
	m_totalTime{},
	m_windowSize{ WINDOW_SIZE },
	m_textureSize{},
	m_texture{},
	m_scale(DirectX::SimpleMath::Vector2::One),
	m_position(),
	m_alpha(1.0f),
	m_anchor(ANCHOR::TOP_LEFT),
	m_action(nullptr)
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
UserInterface::~UserInterface()
{
}

// ---------------------------------------------------------
/// <summary>
/// �e�N�X�`���T�C�Y�̎擾
/// </summary>
/// <param name="srv">�e�N�X�`��</param>
/// <summary>
// ---------------------------------------------------------
void UserInterface::GetTextureSize(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv) {
	// ID3D11Resource���擾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	srv->GetResource(resource.GetAddressOf());

	// ID3D11Texture2D�ɃL���X�g
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
	if (FAILED(resource.As(&texture))) {
		// �����e�N�X�`���łȂ��ꍇ�̃G���[�n���h�����O
		return;
	}

	// �e�N�X�`���̃f�B�X�N���v�^���擾
	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	// �e�N�X�`���̃T�C�Y���擾
	m_textureSize =
		DirectX::SimpleMath::Vector2(
			static_cast<float>(desc.Width),
			static_cast<float>(desc.Height)
		);
}

// ---------------------------------------------------------
/// <summary>
/// �����֐�
/// </summary>
/// <param name="texture">�e�N�X�`��</param>
/// <param name="position">���W</param>
/// <param name="scale">�g��{��</param>
/// <param name="anchor">�A���J�[�|�C���g</param>
/// <param name="action">�A�j���[�V�����A�N�V����</param>
// ---------------------------------------------------------
void UserInterface::Create(
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture,
	DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale,
	ANCHOR anchor,
	IAction* action)
{
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �������W�̐ݒ�
	m_position = position;
	// �X�P�[���̐ݒ�
	m_scale = scale;
	// �A���J�[�̐ݒ�
	m_anchor = anchor;
	// �A�N�V�����̐ݒ�
	m_action = action;

	//	�V�F�[�_�[�̍쐬
	CreateShader();
	// �e�N�X�`�����擾
	m_texture = texture;
	// �e�N�X�`���̑傫�����擾
	GetTextureSize(texture);

	//	�v���~�e�B�u�o�b�`�̍쐬
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);
	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="time">�o�ߎ���</param>
// ---------------------------------------------------------
void UserInterface::Update(const float time)
{
	//	�o�ߎ��Ԃ����Z
	m_totalTime += time;

	//	�A�N�V����������ꍇ�͎��s����
	if (m_action)
	{
		// �A�N�V�����̃p�����[�^���쐬����
		ActionParams param;
		param.position = m_position;
		param.scale = m_scale;
		param.alpha = 1.0f;

		// �A�N�V���������s����
		param = m_action->Execute(param, m_totalTime);

		// �A�N�V�����̌��ʂ𔽉f����
		m_position = param.position;
		m_scale = param.scale;
		m_alpha = param.alpha;
	}
}

// ---------------------------------------------------------
/// <summary>
/// Shader�쐬�����������������֐�
/// </summary>
// ---------------------------------------------------------
void UserInterface::CreateShader()
{
	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �V�F�[�_�[�̍쐬
	m_shader = std::make_unique<CustomShader>(
		device,
		VS_PATH,
		PS_PATH,
		GS_PATH,
		INPUT_LAYOUT
	);

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	// �f�o�C�X�Ƀo�b�t�@���쐬������
	HRESULT hr = device->CreateBuffer(&bd, nullptr, &m_CBuffer);
	if (FAILED(hr))
	{
		MessageBox(0, L"�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���.", NULL, MB_OK);
	}
}

// ---------------------------------------------------------
/// <summary>
/// �`��֐�
/// </summary>
// ---------------------------------------------------------
void UserInterface::Render()
{
	//	�f�o�C�X�R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// ���_���
	// Position.xy	:�g�k�p�X�P�[��
	// Position.z	:�A���J�[�^�C�v(0�`8)�̐����Ŏw��
	// Color.xy�@	:�A���J�[���W(�s�N�Z���w��:1280 �~720)
	// Color.zw		:�摜�T�C�Y
	// Tex.xy		:�E�B���h�E�T�C�Y�i�o�b�t�@�������B������͖��g�p�j
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture(
			DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(m_anchor)),
			DirectX::SimpleMath::Vector4(m_position.x, m_position.y, m_textureSize.x, m_textureSize.y),
			DirectX::SimpleMath::Vector2(m_windowSize.x, m_windowSize.y))
	};

	//	�V�F�[�_�[�ɓn���ǉ��̃o�b�t�@���쐬����B(ConstBuffer�j
	ConstBuffer cbuff;
	cbuff.windowSize = DirectX::SimpleMath::Vector2(m_windowSize.x, m_windowSize.y);
	cbuff.alpha = m_alpha;
	cbuff.padding = 0.0f;

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	//	�V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	//	�J�����O�͍�����
	context->RSSetState(m_states->CullNone());
	// �V�F�[�_���Z�b�g����
	m_shader->BeginSharder(context);
	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();
	//	�V�F�[�_�[��������
	m_shader->EndSharder(context);
}