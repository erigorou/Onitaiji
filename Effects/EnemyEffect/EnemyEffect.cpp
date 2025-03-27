// ** ---------------------------------------------------------**
//     �G���f���̎��S���E�_���[�W���̃G�t�F�N�g���Ǘ�����N���X
// ** ---------------------------------------------------------**

#include "pch.h"
#include "EnemyEffect.h"
#include "Libraries/MyLib/CustomShader/CustomShader.h"
#include "Libraries/MyLib/EasingFunctions.h"
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "DeviceResources.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------
EnemyEffect::EnemyEffect()
	:
	m_totalTime{},
	m_deadShader{},
	m_buffer{},
	m_currentEffect{ ENEMY_EFFECT::NONE }
{
	// �V�F�[�_�[�̐���
	CreateShader();

	// �萔�o�b�t�@�̍쐬
	CreateConstBuffer();
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
EnemyEffect::~EnemyEffect()
{
}

// ---------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void EnemyEffect::Update(float elapsedTime)
{
	if (m_currentEffect == ENEMY_EFFECT::DEAD)
	{
		// �o�ߎ��Ԃ̋L�^
		m_totalTime = std::max(0.0f, (m_totalTime - elapsedTime));
	}
	else if (m_currentEffect == ENEMY_EFFECT::DAMAGE)
	{
		// �o�ߎ��Ԃ̋L�^
		m_totalTime = std::max(0.0f, (m_totalTime - elapsedTime));
	}
}

// ---------------------------------------------
/// <summary>
/// �G�̑̃p�[�c�̕`�揈��
/// </summary>
/// <param name="model">�`�悷�郂�f��</param>
/// <param name="world">���[���h�s��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�v���W�F�N�V�����s��</param>
// ---------------------------------------------
void EnemyEffect::DrawWithEffect(
	DirectX::Model* model,
	const DirectX::SimpleMath::Matrix world,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj
)
{
	// �K�v���̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();

	// �萔�o�b�t�@�̍X�V
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	context->Map(m_buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	ConstBuffer* cb = static_cast<ConstBuffer*>(mappedResource.pData);

	// �萔�o�b�t�@�̍X�V����
	UpdateConstBuffer(cb);

	context->Unmap(m_buffer.Get(), 0);

	// �G�t�F�N�g�̐ݒ�
	model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true); // ���C�g�L����
				basicEffect->SetPerPixelLighting(true); // �s�N�Z���P�ʂ̃��C�e�B���O�L����
				basicEffect->SetTextureEnabled(false); // �e�N�X�`���̖�����
				basicEffect->SetVertexColorEnabled(false); // ���_�J���[�̖�����
				basicEffect->SetFogEnabled(false); // �t�H�O�̖�����
			}
		}
	);

	ID3D11SamplerState* sampler[1] = { };
	context->PSSetSamplers(0, 1, sampler);

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture = GameResources::GetInstance()->GetTexture("noize");

	// ���f���̕`��
	model->Draw(context, *states, world, view, proj, false, [&]
		{
			// �V�F�[�_�[�𓖂Ă�Ƃ��͋��ʂ̌v�Z���s��
			if (m_currentEffect != ENEMY_EFFECT::NONE)
			{
				// �萔�o�b�t�@��ݒ�
				ID3D11Buffer* cbuff = { m_buffer.Get() };
				// �V�F�[�_�[�Ƀo�b�t�@��n��
				context->PSSetConstantBuffers(1, 1, &cbuff);
				//	�s�N�Z���V�F�[�_�Ƀe�N�X�`����o�^����B
				context->PSSetShaderResources(0, 1, texture.GetAddressOf());
				// �u�����h�X�e�[�g��ݒ�
				context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xFFFFFFFF);
			}

			// �_���[�W��H��������̃G�t�F�N�g��K�p
			if (m_currentEffect == ENEMY_EFFECT::DAMAGE)
			{
				// �V�F�[�_�[�̊J�n
				m_damageShader->BeginSharder(context);
			}
			// ���S���̃G�t�F�N�g��K�p
			else if (m_currentEffect == ENEMY_EFFECT::DEAD)
			{
				// �V�F�[�_�[�̊J�n
				m_deadShader->BeginSharder(context);
			}
		}
	);
}

// ---------------------------------------------
/// <summary>
/// �V�F�[�_�[�̍쐬
/// </summary>
// ---------------------------------------------
void EnemyEffect::CreateShader()
{
	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// ���S���̃V�F�[�_�[�̍쐬
	m_deadShader = std::make_unique<CustomShader>
		(
			device,			// �f�o�C�X
			DEAD_VS_PATH,	// ���_�V�F�[�_�[
			DEAD_PS_PATH,	// �s�N�Z���V�F�[�_�[
			nullptr,		// �W�I���g���V�F�[�_�[(�g�p����)
			INPUT_LAYOUT	// ���̓��C�A�E�g
		);

	// �_���[�W���̃V�F�[�_�[�̍쐬
	m_damageShader = std::make_unique<CustomShader>
		(
			device,			// �f�o�C�X
			DAMAGE_VS_PATH,	// ���_�V�F�[�_�[
			DAMAGE_PS_PATH,	// �s�N�Z���V�F�[�_�[
			nullptr,		// �W�I���g���V�F�[�_�[(�g�p����)
			INPUT_LAYOUT	// ���̓��C�A�E�g
		);
}

// ---------------------------------------------
/// <summary>
/// �萔�o�b�t�@�̍쐬
/// </summary>
// ---------------------------------------------
void EnemyEffect::CreateConstBuffer()
{
	// �f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// �萔�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc = {};
	desc.ByteWidth = sizeof(ConstBuffer);
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	DX::ThrowIfFailed(
		device->CreateBuffer(&desc, nullptr, m_buffer.GetAddressOf())
	);
}

// ---------------------------------------------
/// <summary>
/// �萔�o�b�t�@�̍X�V����
/// </summary>
/// <param name="cb">�X�V�Ώۂ̒萔�o�b�t�@</param>
// ---------------------------------------------
void EnemyEffect::UpdateConstBuffer(ConstBuffer* cb)
{
	// ���S���̎��Ԍv��
	if (m_currentEffect == ENEMY_EFFECT::DEAD)
	{
		// ���Ԃ̐ݒ�i�C�[�W���O�Ɛ��K�������Ă����Ԃ̂��́j
		cb->Time = Easing::easeInCirc(m_totalTime / DEAD_TIME);
	}
	// �_���[�W���̎��Ԍv��
	else if (m_currentEffect == ENEMY_EFFECT::DAMAGE)
	{
		// ���Ԃ̐ݒ�i�C�[�W���O�Ɛ��K�������Ă����Ԃ̂��́j
		cb->Time = Easing::easeInCirc(m_totalTime / DAMAGE_TIME);
	}

	cb->Padding = DirectX::SimpleMath::Vector3::Zero;
}

// ---------------------------------------------
/// <summary>
/// �G�t�F�N�g�̐ݒ�
/// </summary>
/// <param name="effect">�K�p����G�t�F�N�g</param>
// ---------------------------------------------
void EnemyEffect::SetEffect(ENEMY_EFFECT effect)
{
	// �G�t�F�N�g�̐ݒ�
	m_currentEffect = effect;

	if (m_currentEffect == ENEMY_EFFECT::DEAD)
	{
		// �c�莞�Ԃ����Z�b�g
		m_totalTime = DEAD_TIME;
	}
	else if (m_currentEffect == ENEMY_EFFECT::DAMAGE)
	{
		// �c�莞�Ԃ����Z�b�g
		m_totalTime = DAMAGE_TIME;
	}
}