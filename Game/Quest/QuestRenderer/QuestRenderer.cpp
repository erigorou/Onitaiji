// ---------------------------------------------------------------------------------------
// ���O:	QuestRenderer.cpp
// ���e:	�`���[�g���A�����̑���ē��̕`����s���N���X
// �쐬:	�r�c����
// ---------------------------------------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "QuestRenderer.h"
#include "../QuestManager.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/UI/UIAnchor.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "CommonStates.h"
#include "Game/GameResources.h"

// -------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="manager">�N�G�X�g�}�l�[�W���[</param>
// -------------------------------------------------------
QuestRenderer::QuestRenderer(QuestManager* manager)
	: 
	m_questManager(manager),
	m_position(INIT_POSITION_X, INIT_POSITION_Y, 0),
	m_angle{},
	m_scale{INIT_SIZE},
	m_alpha{},
	m_dissolve{},
	m_currentTime{},
	m_canChanegQuest(false),
	m_clearFlag(false)
{
}

// -------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// -------------------------------------------------------
QuestRenderer::~QuestRenderer()
{
	Finalize();
}

// -------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
/// <param name="texture">�e�N�X�`��</param>
// -------------------------------------------------------
void QuestRenderer::Initialize(Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture)
{
	// �e�N�X�`����ݒ�
	m_texture = texture;
	// �f�B�]���u�e�N�X�`���̐ݒ�
	m_dissolveTexture = GameResources::GetInstance()->GetTexture("noize");

	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �V�F�[�_�[�̐���
	CreateShader();
	// �R���X�^���g�o�b�t�@�̍쐬
	ConstantBuffer();

	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);
	// �v���~�e�B�u�o�b�`�̐���
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);

	// �X���C�h�A�N�V�����̒ǉ�
	AddSlideAction();
}

// -------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// -------------------------------------------------------
void QuestRenderer::Update(float elapsedTime)
{
	// �o�ߎ��Ԃ̕ۑ�
	m_elapsedTime = elapsedTime;

	// �X���C�h�̍X�V����
	m_currentAction();
}

// -------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// -------------------------------------------------------
void QuestRenderer::Draw()
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
	context->PSSetShaderResources(1, 1, m_dissolveTexture.GetAddressOf());

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
void QuestRenderer::Finalize()
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
/// �J�X�^���V�F�[�_�[�̐���
/// </summary>
// -------------------------------------------------------
void QuestRenderer::CreateShader()
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
void QuestRenderer::ConstantBuffer()
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
void QuestRenderer::UpdateConstantBuffer()
{
	// �R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �萔�o�b�t�@�̐ݒ�
	CBuffer cbuff;
	cbuff.windowSize = DirectX::SimpleMath::Vector4(WINDOW_WIDTH, WINDOW_HEIGHT, 0.0f, 0.0f);
	cbuff.alpha = m_alpha;
	cbuff.dissolve = m_dissolve;
	cbuff.padding = DirectX::SimpleMath::Vector2(0.0f, 0.0f);

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
void QuestRenderer::SetRenderState()
{
	// �R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	ID3D11BlendState* blendstate = m_states->NonPremultiplied(); 	//	�������`��w��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);		// ��������
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);		// �[�x�o�b�t�@�ɏ������ݎQ�Ƃ��Ȃ�
	context->RSSetState(m_states->CullClockwise());					// �J�����O�͍����
}

// -------------------------------------------------------
/// <summary>
/// �X���C�h�A�N�V�����̓o�^
/// </summary>
// -------------------------------------------------------
void QuestRenderer::AddSlideAction()
{
	// �A�N�V�����̒ǉ�
	m_slideActions.push_back([this]() { return NoSlideTexture(); }); // �ҋ@
	m_slideActions.push_back([this]() { return SlideOutTexture(); }); // �X���C�h�A�E�g
	m_slideActions.push_back([this]() { return SlideCoolTime();	 }); // �N�[���^�C��
	m_slideActions.push_back([this]() { return SlideInTexture(); }); // �X���C�h�C��

	// ���݂̃A�N�V������ݒ�
	m_currentAction = m_slideActions[SLIDE_ACTION::SLIDE_IN];

	// �o�ߎ��Ԃ�-����n�߂邱�ƂŒx����ݒ�
	m_currentTime = INITIAL_TIME;
}

// -------------------------------------------------------	
/// <summary>
/// �摜���X���C�h�����Ȃ�
/// </summary>
// -------------------------------------------------------
void QuestRenderer::NoSlideTexture()
{
	// �}�l�[�W���[���N�G�X�g�̕ύX�������Ă��邩
	if (m_clearFlag)
	{
		// �N�G�X�g�̕ύX
		m_currentAction = m_slideActions[SLIDE_ACTION::SLIDE_OUT];
	}
}

// -------------------------------------------------------
/// <summary>
/// �e�N�X�`�����X���C�h�A�E�g������
/// </summary>
// -------------------------------------------------------
void QuestRenderer::SlideOutTexture()
{
	// �o�ߎ��Ԃ̍X�V
	m_currentTime += m_elapsedTime;
	// ���K���������Ԃ̎擾
	float easing = Easing::easeInOutQuad(m_currentTime / FIER_TIME);
	// �f�B�]���u�̐ݒ�
	m_dissolve = easing;

	// �A�j���[�V�������Ԃ��o�߂����ꍇ�A�I��
	if (m_currentTime > FIER_TIME)
	{
		// �X���C�h�A�E�g�I��
		m_currentTime = 0.0f;
		// �X���C�h�A�N�V�����̕ύX
		m_currentAction = m_slideActions[SLIDE_ACTION::COOL_TIME];
		// �N���A�t���O��܂�
		m_clearFlag = false;
		// �N�G�X�g���P�i�߂�
		m_questManager->ChangeNextQuest();
	}
}

// -------------------------------------------------------
/// <summary>
/// �X���C�h�̃N�[���^�C��
/// </summary>
// -------------------------------------------------------
void QuestRenderer::SlideCoolTime()
{
	// �N�[���^�C���̍X�V
	m_currentTime += m_elapsedTime;

	// �N�[���^�C���̏I��
	if (m_currentTime > ANIMATION_WAIT)
	{
		m_currentTime = 0.0f;
		m_currentAction = m_slideActions[SLIDE_ACTION::SLIDE_IN];
	}
}

// -------------------------------------------------------
/// <summary>
/// �e�N�X�`�����X���C�h�C��������
/// </summary>
// -------------------------------------------------------
void QuestRenderer::SlideInTexture()
{
	// �f�B�]���u�̏�����
	m_dissolve = 0.0f;
	// �o�ߎ��Ԃ̍X�V
	m_currentTime += m_elapsedTime;
	// ���K���������Ԃ̎擾
	float t = m_currentTime / ANIMATION_TIME;
	// alpha�l�̐ݒ�
	m_alpha = t;
	// �X���C�h����
	m_position.x = WINDOW_WIDTH - WIDTH * Easing::easeOutExpo(t);
	// �A�j���[�V�������Ԃ��o�߂����ꍇ�A�I��
	if (m_currentTime > ANIMATION_TIME)
	{
		// �X���C�h�C���I��
		m_currentTime = 0.0f;
		m_currentAction = m_slideActions[SLIDE_ACTION::WAIT];
	}
}