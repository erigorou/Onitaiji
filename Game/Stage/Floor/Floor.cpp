// -----------------------------------
// ���O:	Floor.cpp
// ���e:	�~�`�̒n�ʂ̕`��N���X
// �쐬:	�r�c����
// -----------------------------------

// �C���N���[�h
#include "pch.h"
#include "Floor.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/GameResources.h"

// --------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="device">�f�o�C�X�̃|�C���^</param>
/// --------------------------------------------------
Floor::Floor()
{
	CommonResources* resources = CommonResources::GetInstance();
	auto device = resources->GetDeviceResources()->GetD3DDevice();

	// �G�t�F�N�g�̍쐬
	m_BatchEffect = std::make_unique<DirectX::AlphaTestEffect>(device);
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_BatchEffect->SetReferenceAlpha(255);

	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_BatchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(
		DirectX::VertexPositionTexture::InputElements,
		DirectX::VertexPositionTexture::InputElementCount,
		shaderByteCode, static_cast<int>(byteCodeLength), m_inputLayout.GetAddressOf()
	);

	// ���ʃX�e�[�g�̍쐬
	m_states = std::make_unique<DirectX::CommonStates>(device);

	// �e�N�X�`���̓ǂݍ���
	m_texture = GameResources::GetInstance()->GetTexture("floor");
}

// --------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
/// --------------------------------------------------
Floor::~Floor()
{
}

// --------------------------------------------------
/// <summary>
/// �~�̒��_�𐶐�����
/// </summary>
/// <param name="vertices">���_�z��</param>
/// <param name="radius">�~�̔��a</param>
/// <param name="segments">�~�̕�����</param>
/// --------------------------------------------------
void Floor::GenerateCircleVertices(DirectX::VertexPositionTexture* vertices, float radius, int segments)
{
	// �~�̒��_�𐶐�
	for (int i = 0; i < segments; ++i)
	{
		// 1�����̊p�x�����߂�
		float angle = (2.0f * DirectX::XM_PI / segments) * i;
		// ���_���W��ݒ�
		vertices[i].position = DirectX::SimpleMath::Vector3(radius * cosf(angle), 0.0f, radius * sinf(angle));
		// ���K�������e�N�X�`�����W���擾
		float normalizedSin = sin(angle) * NORMALIZE + NORMALIZE;
		float normalizedCos = cos(angle) * NORMALIZE + NORMALIZE;
		// �e�N�X�`�����W��ݒ�
		vertices[i].textureCoordinate = DirectX::SimpleMath::Vector2(normalizedCos, normalizedSin);
	}
}

// --------------------------------------------------
/// <summary>
/// ���̕`����s��
/// </summary>
/// <param name="context">�f�o�C�X�R���e�L�X�g</param>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�v���W�F�N�V�����s��</param>
/// --------------------------------------------------
void Floor::Render(
	DirectX::SimpleMath::Matrix view,
	DirectX::SimpleMath::Matrix proj
)
{
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = resources->GetCommonStates();

	// �v���~�e�B�u�o�b�`�̍쐬
	m_Batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>>(context);

	// ���_���i�~�̒��_�j
	std::vector<DirectX::VertexPositionTexture> vertices(SEGMENTS);
	GenerateCircleVertices(vertices.data(), RADIUS, SEGMENTS);

	// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// �J�����O�͍�����i�����v���j
	context->RSSetState(m_states->CullCounterClockwise());

	// ���S�s�����̂ݕ`�悷��ݒ�
	m_BatchEffect->SetAlphaFunction(D3D11_COMPARISON_NOT_EQUAL);
	m_BatchEffect->SetReferenceAlpha(0);
	m_BatchEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	m_BatchEffect->SetView(view);
	m_BatchEffect->SetProjection(proj);
	m_BatchEffect->SetTexture(m_texture.Get());
	m_BatchEffect->Apply(context);
	context->IASetInputLayout(m_inputLayout.Get());

	// �T���v���[�X�e�[�g�̐ݒ�
	ID3D11SamplerState* sampler[1] = { states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// ������������`��
	m_Batch->Begin();

	// �~��`��
	for (int i = 0; i < SEGMENTS; ++i)
	{
		m_Batch->DrawTriangle(vertices[i], vertices[(i + 1) % SEGMENTS], vertices[0]);
	}

	m_Batch->End();
}

// --------------------------------------------------
/// <summary>
/// �I������
/// </summary>
/// --------------------------------------------------
void Floor::Finalize()
{
}
