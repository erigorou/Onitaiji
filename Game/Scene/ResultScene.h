// --------------------------------------------------
// 
// ���O:	ResultScene.h
// ���e:	���U���g�V�[����`�悷��N���X
// �쐬:	�r�c����
// 
// --------------------------------------------------
#pragma once
// �C���N���[�h
#include "IScene.h"
#include "Game/Data/GameData.h"
#include "Game/UI/UIAnchor.h"

// �O���錾
class CommonResources;
class UserInterface;
class IAction;

/// <summary>
/// ���U���g�V�[��
/// </summary>
class ResultScene final : public IScene
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �^�C�g���ɖ߂�{�^���̍��W
	static constexpr DirectX::SimpleMath::Vector2 RETURN_BUTTON_POSITION = DirectX::SimpleMath::Vector2(750.0f, 900.0f);
	// �Q�[���I���{�^���̍��W
	static constexpr DirectX::SimpleMath::Vector2 EXIT_BUTTON_POSITION = DirectX::SimpleMath::Vector2(1000.0f, 900.0f);
	// �{�^���̑傫��
	static constexpr DirectX::SimpleMath::Vector2 BUTTON_SIZE = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

	// �X�N�V����`�悷��ʒu
	static constexpr DirectX::SimpleMath::Vector2 CAPTURE_POSITION = DirectX::SimpleMath::Vector2(350.0f, 360.0f);
	// �X�N�V���̌X��
	static constexpr float CAPTURE_ROTATION = DirectX::XMConvertToRadians(-20.0f);
	// �X�N�V���̑傫��
	static constexpr float CAPTURE_SCALE = 0.5f;

	// �w�i��`�悷��ʒu
	static constexpr DirectX::SimpleMath::Vector2 BACKGROUND_POSITION = DirectX::SimpleMath::Vector2(640.0f, 360.0f);
	// �w�i�̌X��
	static constexpr float BACKGROUND_ROTATION = DirectX::XMConvertToRadians(0.0f);
	// �w�i�̑傫��
	static constexpr float BACKGROUND_SCALE = 1.0f;

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �R���X�g���N�^
	ResultScene();
	// �f�X�g���N�^
	~ResultScene() override;
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float elapsedTime)override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;
	// ���̃V�[��ID���擾����
	SceneID GetNextSceneID() const;
	// �O�̃V�[��ID���擾����
	SceneID GetPrevSceneID() const;

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �e�N�X�`���̍쐬
	void CreateTextures();
	// ���[�U�[�C���^�[�t�F�[�X�̒ǉ�
	void AddUserInterface(
		const std::string textureName,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 scale,
		ANCHOR anchor,
		IAction* action
	);
	// ���[�U�[�C���^�[�t�F�[�X�̒ǉ�
	void CreateUI();
	// �X�N�V���̕`��
	void DrawCaptureTexture();
	// �w�i�̕`��
	void DrawBackground();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �X�N���[���V���b�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_captureTexture;

	// �e�N�X�`���̒��S���W
	DirectX::SimpleMath::Vector2 m_texCenter;
	// �X�N�V���e�N�X�`���̒��S���W
	DirectX::SimpleMath::Vector2 m_captureTexCenter;
	// ���[�U�[�C���^�[�t�F�[�X���X�g
	std::vector<std::unique_ptr<UserInterface>> m_uiList;

	// �V�[���J�ڃt���O
	bool m_isChangeScene;
	// �Q�[���f�[�^
	GameData* m_gameData;
	// �퓬����
	GameData::BATTLE_RESULT m_result;
};
