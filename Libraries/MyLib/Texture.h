#pragma once

class CommonResources;

namespace mylib
{
	class Texture
	{
	public:

		// ------------------------------------------------
		// �e�N�X�`���̃��[�h�֐�
		// ------------------------------------------------
		// �e�N�X�`�������[�h����
		// device: �f�o�C�X
		// texture: �e�N�X�`��
		// fileName: �t�@�C����
		// ------------------------------------------------
		static void LoadTexture(
			ID3D11Device* device,	// �f�o�C�X
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture,	// �e�N�X�`��
			const wchar_t* fileName										// �t�@�C����
		);

		// ------------------------------------------------
		// �摜�̑傫�������߁A�e�N�X�`���̒��S���W���v�Z����
		// ------------------------------------------------
		// �e�N�X�`���̑傫�������߂�
		// texture: �e�N�X�`��
		// texSize: �e�N�X�`���̑傫��
		// texCenter: �e�N�X�`���̒��S���W
		// ------------------------------------------------
		static void CalculateTextureCenter(
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture,	// �e�N�X�`��
			DirectX::SimpleMath::Vector2& texSize,	// �e�N�X�`���̑傫��
			DirectX::SimpleMath::Vector2& texCenter							// �e�N�X�`���̒��S���W
		);

		// ------------------------------------------------
		// �e�N�X�`����`�悷��
		// ------------------------------------------------
		// spriteBatch: �X�v���C�g�o�b�`
		// position: �ʒu
		// texture: �e�N�X�`��
		// texCenter: �e�N�X�`���̒��S���W
		// scale: �g�嗦
		// rotation: ��]�p�x
		// ------------------------------------------------
		static void DrawTexture(
			DirectX::SpriteBatch* spriteBatch,
			DirectX::SimpleMath::Vector2 position,
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& texture,
			DirectX::SimpleMath::Vector2 texCenter,
			DirectX::SimpleMath::Vector2 scale,
			float rotation
		);
	};
};