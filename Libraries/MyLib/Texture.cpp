#include "pch.h"
#include "Texture.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"

// ------------------------------------------------
// �e�N�X�`�������[�h����
// ------------------------------------------------
void mylib::Texture::LoadTexture
(
	ID3D11Device* device,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture,
	const wchar_t* fileName
)
{
	// �摜�����[�h����
	DX::ThrowIfFailed(
		DirectX::CreateWICTextureFromFile(
			device,
			fileName,
			nullptr,
			texture.ReleaseAndGetAddressOf()
		)
	);
}

// ------------------------------------------------
// �摜�̑傫�����擾���A�e�N�X�`���̒��S���W���v�Z����
// ------------------------------------------------
void mylib::Texture::CalculateTextureCenter
(
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture,
	DirectX::SimpleMath::Vector2& texSize,
	DirectX::SimpleMath::Vector2& texCenter
)
{
	Microsoft::WRL::ComPtr<ID3D11Resource> resource{};	// ���\�[�X
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex2D{};	// �e�N�X�`��(2D��)
	D3D11_TEXTURE2D_DESC desc{};						// �e�N�X�`���̏��

	// �e�N�X�`���̃��\�[�X���擾�i�ԊґO�j
	texture->GetResource(resource.GetAddressOf());
	// ID3D11Resource��ID3D11Texture2D�ɕϊ�
	resource.As(&tex2D);
	tex2D->GetDesc(&desc);
	// �e�N�X�`���̑傫�������߂�
	texSize.x = static_cast<float>(desc.Width);
	texSize.y = static_cast<float>(desc.Height);

	// �e�N�X�`���̒��S���W���v�Z����
	texCenter = texSize / 2.0f;
}

// ------------------------------------------------
// �e�N�X�`����`�悷��
// ------------------------------------------------
void mylib::Texture::DrawTexture
(
	DirectX::SpriteBatch* spriteBatch,
	DirectX::SimpleMath::Vector2 position,
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture,
	DirectX::SimpleMath::Vector2 texCenter,
	DirectX::SimpleMath::Vector2 scale,
	float rotation
)
{
	auto common = CommonResources::GetInstance();

	// TRIDENT���S�̕`��ʒu�����߂�
	RECT rect{ common->GetDeviceResources()->GetOutputSize() };

	// ���S���猩�� pos �����炷
	DirectX::SimpleMath::Vector2 pos{ rect.right / 2.0f, rect.bottom / 2.0f };
	DirectX::SimpleMath::Vector2 calPos = pos + position;

	spriteBatch->Draw(
		texture.Get(),			// �e�N�X�`��(SRV)
		calPos,					// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,				// ��`(RECT)
		DirectX::Colors::White,	// �w�i�F
		rotation,				// ��]�p(���W�A��)
		texCenter,				// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		scale					// �X�P�[��(scale)
	);
}