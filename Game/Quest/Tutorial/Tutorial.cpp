// ---------------------------------------------------------------------------------------
// ���O:	Tutorial.h
// ���e:	�`���[�g���A�����̌��t�̕�����`�悷��N���X
// �쐬:	�r�c����
// ---------------------------------------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Tutorial.h"
#include "../QuestManager.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/UI/UIAnchor.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "CommonStates.h"

// -------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="manager">�N�G�X�g�}�l�[�W���[</param>
// -------------------------------------------------------
Tutorial::Tutorial(QuestManager* manager)
	: 
	m_questManager{ manager },
	m_position{ INIT_POSITION_X, INIT_POSITION_Y, 0 },
	m_angle{},
	m_scale{ INIT_SIZE },
	m_alpha{ INIT_ALPHA },
	m_currentTime{},
	m_timerPlay{ false },
	m_canUseTimer{ true },
	m_alphaFlag{ false }
{
}

// -------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// -------------------------------------------------------
Tutorial::~Tutorial()
{
	Finalize();
}

// -------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
/// <param name="texture">�e�N�X�`��</param>
// -------------------------------------------------------
void Tutorial::Initialize(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
{
	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �V�F�[�_�[�̐���
	CreateShader();
	// �R���X�^���g�o�b�t�@�̍쐬
	ConstantBuffer();
	// �e�N�X�`���̐ݒ�
	m_texture = texture;
	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);
	// �v���~�e�B�u�o�b�`�̐���
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);
}

// -------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -------------------------------------------------------
void Tutorial::Update(float elapsedTime)
{
	// �^�C�}�[�̍X�V����
	UpdateTimer(elapsedTime);
	// ���l�̍X�V����
	UpdateAlpha(elapsedTime);
}

// -------------------------------------------------------
/// <summary>
/// �^�C�}�[�̍X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -------------------------------------------------------
void Tutorial::UpdateTimer(float elapsedTime)
{
	// �^�C�}�[���N�����łȂ��ƍX�V���Ȃ�
	if (!m_timerPlay) return;

	// ���Ԃ��v��
	m_currentTime = std::max((m_currentTime - elapsedTime), 0.0f);

	// �^�C�}�[��0�ȉ��ɂȂ�����^�C�}�[���~�߂�
	if (m_currentTime <= 0.0f)	m_timerPlay = false;
}

// -------------------------------------------------------	
/// <summary>
/// ���l�̍X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -------------------------------------------------------
void Tutorial::UpdateAlpha(float elapsedTime)
{
	// ���l�����炷�t���O�������Ă��Ȃ��ƍX�V���Ȃ�
	if (!m_alphaFlag) return;

	// ���Ԃ��v��
	m_currentTime = std::max((m_currentTime - elapsedTime), 0.0f);

	// ���Ԃ𐳋K��
	float easing = m_currentTime / ANIMATION_TIME;

	// ���l�̍X�V
	m_alpha = Easing::easeOutQuint(easing);
}

// -------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// -------------------------------------------------------
void Tutorial::Draw()
{
	// �R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// ���_���̐ݒ�
	DirectX::VertexPositionColorTexture vertex[1] =
	{
		DirectX::VertexPositionColorTexture
		(
			DirectX::SimpleMath::Vector3(m_scale.x, m_scale.y, static_cast<float>(ANCHOR::TOP_LEFT))
		,	DirectX::SimpleMath::Vector4(m_position.x, m_position.y, WIDTH, HEIGHT)
		,	DirectX::SimpleMath::Vector2(WINDOW_WIDTH, WINDOW_HEIGHT)
		)
	};

	// �萔�o�b�t�@�̐ݒ�
	UpdateConstantBuffer();

	// �摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	// �����_�[�X�e�[�g�̐ݒ�
	SetRenderState();

	// �V�F�[�_�[�J�n
	m_shader->BeginSharder(context);

	// �e�N�X�`���̐ݒ�
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());

	//	�|���S����`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 1);
	m_batch->End();

	// �V�F�[�_�[�I��
	m_shader->EndSharder(context);
}

// -------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// -------------------------------------------------------
void Tutorial::Finalize()
{
	// �e�N�X�`���̉��
	m_texture.Reset();
	// �V�F�[�_�[�̉��
	m_shader.reset();
	// �R���X�^���g�o�b�t�@�̉��
	m_CBuffer.Reset();
	// �X�e�[�g�̉��
	m_states.reset();
	// �v���~�e�B�u�o�b�`�̉��
	m_batch.reset();
}

// -------------------------------------------------------
/// <summary>
/// �^�C�}�[�̊J�n����
/// </summary>
// -------------------------------------------------------
void Tutorial::StartTimer()
{
	// �^�C�}�[���g�p�\�łȂ��Ə������s��Ȃ�
	if (!m_canUseTimer)	return;

	// �^�C�}�[�N��
	m_timerPlay = true;
	// �^�C�}�[�̐ݒ�
	m_currentTime = ANIMATION_TIME;
	// �^�C�}�[���g�p�s�ɂ���
	m_canUseTimer = false;
}

// -------------------------------------------------------
/// <summary>
/// ���l�̌��Z�����J�n
/// </summary>
// -------------------------------------------------------
void Tutorial::StartAlphaMinus()
{
	if (m_alphaFlag) return;

	m_alphaFlag = true;
	m_currentTime = ANIMATION_TIME;
}

// -------------------------------------------------------
/// <summary>
/// �J�X�^���V�F�[�_�[�̐���
/// </summary>
// -------------------------------------------------------
void Tutorial::CreateShader()
{
	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �V�F�[�_�[�̐���
	m_shader = std::make_unique<CustomShader>
		(
			device,
			VS_PATH,
			PS_PATH,
			GS_PATH,
			InputElements
		);
}

// -------------------------------------------------------
/// <summary>
/// �萔�o�b�t�@�̍쐬
/// </summary>
// -------------------------------------------------------
void Tutorial::ConstantBuffer()
{
	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//	�V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;

	HRESULT hr = device->CreateBuffer(&bd, nullptr, &m_CBuffer);
	if (FAILED(hr)) {
		MessageBox(0, L"�R���X�^���g�o�b�t�@�̐����Ɏ��s���܂���.", NULL, MB_OK);
	}
}

// -------------------------------------------------------
/// <summary>
/// �萔�o�b�t�@�̍X�V����
/// </summary>
// -------------------------------------------------------
void Tutorial::UpdateConstantBuffer()
{
	// �R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �萔�o�b�t�@�̐ݒ�
	CBuffer cbuff;
	cbuff.windowSize = DirectX::SimpleMath::Vector4(WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f);
	cbuff.alpha = m_alpha;
	cbuff.padding = DirectX::SimpleMath::Vector3::Zero;

	// �󂯓n���p�o�b�t�@�̓��e�X�V
	context->UpdateSubresource(m_CBuffer.Get(), 0, nullptr, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);
}

// -------------------------------------------------------
/// <summary>
/// �����_�[�X�e�[�g�̐ݒ菈��
/// </summary>
// -------------------------------------------------------
void Tutorial::SetRenderState()
{
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	ID3D11BlendState* blendstate = m_states->NonPremultiplied(); 	//	�������`��w��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);		// ��������
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);		// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��Ȃ�
	context->RSSetState(m_states->CullClockwise());					// �J�����O�͍����
}