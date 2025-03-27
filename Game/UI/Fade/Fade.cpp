//--------------------------------------------------------------------------------------
//
// ���O:	Fade.cpp
// �@�\:	�t�F�[�h�C���A�t�F�[�h�A�E�g�̏������s��
// �쐬:	�r�c����
//
//-------------------------------------------------------------------------------------

#include "pch.h"
#include "Fade.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/GameResources.h"
#include "Game/Data/GameData.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Libraries/MyLib/Math.h"

// ----------------------------------
// �Œ�l
// ----------------------------------
const std::vector<D3D11_INPUT_ELEMENT_DESC> Fade::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// ------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ------------------------------------------------------
Fade::Fade(SceneManager* scene)
	:
	m_scene(scene),
	m_easingValue{},
	m_elapsedTime{},
	m_totalTime{},
	m_delayTime{},
	m_isFade(false),
	m_endFade(false),
	m_fadeType(FadeType::FADE_NONE)
{
}

// ------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ------------------------------------------------------
Fade::~Fade()
{
}

// ------------------------------------------------------
/// <summary>
/// �������֐�
/// </summary>
// ------------------------------------------------------
void Fade::Initialize()
{
	// ���\�[�X�̎擾
	auto resources = CommonResources::GetInstance();
	// �f�o�C�X�̎擾
	auto device = resources->GetDeviceResources()->GetD3DDevice();
	// �R���e�L�X�g�̎擾
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();

	// �t�F�[�h�e�N�X�`���̎擾
	m_texture = GameResources::GetInstance()->GetTexture("fade");
	// �^�����e�N�X�`���̎擾
	m_stencilImage = GameResources::GetInstance()->GetTexture("mask");
	// �V�F�[�_�[�̐���
	CreateShader();
	// �v���~�e�B�u�o�b�`�̐���
	m_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(context);
	// �R�����X�e�[�g�̐���
	m_states = std::make_unique<DirectX::CommonStates>(device);
}

// ------------------------------------------------------
/// <summary>
/// �V�F�[�_�[�쐬�����p�֐�
/// </summary>
// ------------------------------------------------------
void Fade::CreateShader()
{
	// �f�o�C�X�̎擾
	ID3D11Device* device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �J�X�^���V�F�[�_�[�̏�����
	m_customShader = std::make_unique<CustomShader>
		(
			device,
			VS_PATH,
			PS_PATH,
			GS_PATH,
			INPUT_LAYOUT
		);

	// �}�X�N�p�J�X�^���V�F�[�_�[�̏�����
	m_maskShader = std::make_unique<CustomShader>
		(
			device,
			MASK_VS_PATH,
			MASK_PS_PATH,
			MASK_GS_PATH,
			INPUT_LAYOUT
		);

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h�C���̊J�n����
/// </summary>
// ------------------------------------------------------
void Fade::StartFadeIn()
{
	m_isFade = true;
	m_totalTime = 0;
	m_fadeType = FadeType::FADE_IN;
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h�A�E�g�J�n
/// </summary>
// ------------------------------------------------------
void Fade::StartFadeOut()
{
	m_isFade = true;
	m_totalTime = FADE_TIME;
	m_fadeType = FadeType::FADE_OUT;
}

// ------------------------------------------------------
/// <summary>
///  �t�F�[�h�̒�~
/// </summary>
// ------------------------------------------------------
void Fade::FadeStop()
{
	m_isFade = false;
	m_fadeType = FadeType::FADE_NONE;
}

// ------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ------------------------------------------------------
void Fade::Update(float elapsedTime)
{
	// �o�ߎ��Ԃ̕ۑ�
	m_elapsedTime = elapsedTime;

	// �t�F�[�h���łȂ��ꍇ�͉������Ȃ�
	if (!m_isFade) return;

	// �^�C�}�[�̃J�E���g
	CountTimer();
}

// ------------------------------------------------------
/// <summary>
/// �b�����v��
/// �t�F�[�h�̎�ނɂ���Čv��������@��ύX
/// </summary>
// ------------------------------------------------------
void Fade::CountTimer()
{
	// �t�F�[�h�̎�ނɂ���ď�����ύX
	switch (m_fadeType)
	{
	case FadeType::FADE_IN:		FadeIn();	break;
	case FadeType::FADE_OUT:	FadeOut();	break;
	case FadeType::END_DELAY:	FadeEnd();	break;

	default: MessageBox(nullptr, L"�t�F�[�h�̎�ނ��s���ł�", L"�G���[", MB_OK); break;
	}
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h�C���̏���
/// </summary>
// ------------------------------------------------------
void Fade::FadeIn()
{
	// ���Ԃ��v�Z����( 0 �� 1 )
	m_totalTime = std::min(m_totalTime + m_elapsedTime, FADE_TIME);

	if (m_totalTime >= FADE_TIME)
	{
		// �t�F�[�h���ł͂Ȃ�
		m_isFade = false;
	}
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h�A�E�g����
/// </summary>
// ------------------------------------------------------
void Fade::FadeOut()
{
	// ���Ԃ��v�Z����( 1 �� 0 )
	m_totalTime = std::max(m_totalTime - m_elapsedTime, 0.0f);

	if (m_totalTime <= 0.0f)
	{
		// �t�F�[�h���I���������Ƃ�ʒm
		m_endFade = true;
		// �t�F�[�h�I������
		m_fadeType = FadeType::END_DELAY;
		// �f�B���C�J�n
		m_delayTime = CHANGE_SCENE_EDLAY;
	}
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h���I������
/// </summary>
// ------------------------------------------------------
void Fade::FadeEnd()
{
	// ���Ԃ����炷
	m_delayTime -= m_elapsedTime;

	// �x�����݂�0�b�ɂȂ�����
	if (m_delayTime <= 0.0f)
	{
		// �t�F�[�h���ł͂Ȃ�
		m_isFade = false;
		// �t�F�[�h�I��
		m_endFade = false;
		// �V�[���ɕύX�t���O�𗧂Ă�
		m_scene->SetCanChangeScene();
		// �t�F�[�h����
		m_fadeType = FadeType::FADE_NONE;
	}
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h�p�̕Њщ摜��`�悷��
/// </summary>
// ------------------------------------------------------
void Fade::DrawStencilImage()
{
	// �f�o�C�X���\�[�X�̎擾
	auto deviceResources = CommonResources::GetInstance()->GetDeviceResources();
	// �R���e�L�X�g�̎擾
	ID3D11DeviceContext* context = deviceResources->GetD3DDeviceContext();

	//	�`��ɂ��Ă̐ݒ���s��
	D3D11_TEXTURE2D_DESC texDesc;
	deviceResources->GetRenderTarget()->GetDesc(&texDesc);
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	deviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, m_capture.ReleaseAndGetAddressOf());

	//	�����_�[�^�[�Q�b�g�r���[�̐ݒ�
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	//	�����_�[�^�[�Q�b�g�r���[�̐���
	deviceResources->GetD3DDevice()->CreateRenderTargetView(m_capture.Get(), &rtvDesc, &m_captureRTV);

	//	�V�F�[�_���\�[�X�r���[�̐ݒ�
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;

	//	�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�r���[���擾�i��Ō��ɖ߂����߁j
	ID3D11RenderTargetView* defaultRTV = deviceResources->GetRenderTargetView();
	ID3D11DepthStencilView* pDSV = deviceResources->GetDepthStencilView();

	// �w�i�F�̎擾(����)
	float backColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���̐ݒ�
	context->OMSetRenderTargets(1, m_captureRTV.GetAddressOf(), pDSV);
	context->ClearRenderTargetView(m_captureRTV.Get(), backColor);
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);

	// ---�I�u�W�F�N�g�̕`��--- ��

	m_maskShader->BeginSharder(context);

	// �t�F�[�h�̎��Ԃ� 0 ~ 1�Ő��K��������
	float t = m_totalTime / FADE_TIME;

	// �t�F�[�h�̃T�C�Y���v�Z
	float size = CalcrateFadeValue(t);

	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::CreateScale(size, size, 1.0f);

	// �V�F�[�_�[�ɓn�����̔}�̂��쐬����
	ConstBuffer cbuff;

	// �n���f�[�^��o�^����
	cbuff.matView = DirectX::SimpleMath::Matrix::Identity;						// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matProj = DirectX::SimpleMath::Matrix::Identity;						// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = DirectX::SimpleMath::Vector4::One;							// �e�N�X�`���̐F
	cbuff.time = DirectX::SimpleMath::Vector4(0.0f, 0.0f, 0.0f, 0.0f);				// �t�F�[�h�̎��ԁi���v�f�̂ݎg�p�j

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* ccb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, ccb);
	context->GSSetConstantBuffers(0, 1, ccb);
	context->PSSetConstantBuffers(0, 1, ccb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	//	�`�悷��I�u�W�F�N�g�̏���ݒ�
	DirectX::VertexPositionColorTexture vertex[4] =
	{
		DirectX::VertexPositionColorTexture(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f),DirectX::SimpleMath::Vector4::One, DirectX::SimpleMath::Vector2(0.0f, 0.0f)),
	};

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_stencilImage.GetAddressOf());

	// (���ۂɂ͕\�����Ȃ���) �`����s��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	�`�悵����ʂ�captureSRV�ɕۑ�����
	deviceResources->GetD3DDevice()->CreateShaderResourceView
	(
		m_capture.Get(), &srvDesc, m_captureSRV.ReleaseAndGetAddressOf()
	);

	//	�V�F�[�_�̉���
	m_maskShader->EndSharder(context);

	//	�ێ����Ă������f�t�H���g�ݒ�ɖ߂��āA��ʕ`�悪����ɏo����悤�ɂ��Ă���
	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
	// �g�p�����������
	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0.0f, 0);
}

// ------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
// ------------------------------------------------------
void Fade::Render()
{
	// �f�o�C�X���\�[�X�̎擾
	auto deviceResources = CommonResources::GetInstance()->GetDeviceResources();

	using namespace DirectX;

	// �^�����摜�̕`��
	DrawStencilImage();

	float easing = 0.0f;
	easing = std::max(0.0f, 1.0f - (m_totalTime / FADE_TIME));
	easing = std::max(0.0001f, Easing::easeInCubic(easing));
	GameData::GetInstance()->SetFadeValue(1 - easing);

	ID3D11DeviceContext1* context = deviceResources->GetD3DDeviceContext();

	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(SimpleMath::Vector3(0.0f, 0.0f, 0.0f),SimpleMath::Vector4::One, SimpleMath::Vector2(0.0f, 0.0f)),
	};

	// �V�F�[�_�[�ɓn�����̔}�̂��쐬����
	ConstBuffer cbuff;

	// �n���f�[�^��o�^����
	cbuff.matView = SimpleMath::Matrix::Identity;				// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matProj = SimpleMath::Matrix::Identity;				// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.matWorld = SimpleMath::Matrix::Identity;				// �X�N���[�����W�ŕ`�悷�邽�ߕs�v
	cbuff.Diffuse = SimpleMath::Vector4::One;					// �e�N�X�`���̐F
	cbuff.time = SimpleMath::Vector4(easing, 0.0f, 0.0f, 0.0f);	// �t�F�[�h�̎��ԁi���v�f�̂ݎg�p�j

	//	�V�F�[�_�̊J�n
	m_customShader->BeginSharder(context);

	//	�󂯓n���p�o�b�t�@�̓��e�X�V(ConstBuffer����ID3D11Buffer�ւ̕ϊ��j
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);

	// �V�F�[�_�[�Ƀo�b�t�@��n��
	ID3D11Buffer* ccb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, ccb);
	context->GSSetConstantBuffers(0, 1, ccb);
	context->PSSetConstantBuffers(0, 1, ccb);

	//	�摜�p�T���v���[�̓o�^
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);
	//	�������`��w��
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	//	�������菈��
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	//	�[�x�o�b�t�@�ɏ������ݎQ�Ƃ���
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	//	�J�����O�͐��ʂ̂ݍs��
	context->RSSetState(m_states->CullCounterClockwise());

	//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
	// �}�X�N�摜���s�N�Z���V�F�[�_�ɓo�^����
	context->PSSetShaderResources(1, 1, m_captureSRV.GetAddressOf());

	// �|���S���ŕ`��
	m_batch->Begin();
	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &vertex[0], 4);
	m_batch->End();

	//	�V�F�[�_�[�̉���
	m_customShader->EndSharder(context);
}

// ------------------------------------------------------
/// <summary>
/// �t�F�[�h�̎�ނ��v�Z����
/// </summary>
/// <param name="easing">���K����������</param>
/// <returns>�t�F�[�h��</returns>
// ------------------------------------------------------
float Fade::CalcrateFadeValue(float easing)
{
	// �t�F�[�h�C���Ȃ�
	if (FadeType::FADE_IN == m_fadeType) {
		return Easing::easeBetweenIn(easing, FADE_THRESHOLD, FADE_FIRST_SIZE, FADE_MAX_SIZE);
	}
	// �t�F�[�h�A�E�g�Ȃ�
	else if (FadeType::FADE_OUT == m_fadeType) {
		return Easing::easeBetweenOut(easing, FADE_THRESHOLD, FADE_FIRST_SIZE, FADE_MAX_SIZE);
	}
	// ���s�Ȃ�
	else return 0;
}