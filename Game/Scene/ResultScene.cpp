// --------------------------------------------------
// 
// ���O:	ResultScene.h
// ���e:	���U���g�V�[����`�悷��N���X
// �쐬:	�r�c����
// 
// --------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "ResultScene.h"
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "DeviceResources.h"
#include "Game/UI/UserInterface.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/Texture.h"
#include "../Sound/Sound.h"
#include "Game/UI/UIAnchor.h"
#include "Interface/IAction.h"
#include "Game/UI/Action/GoTitleButtonAction.h"
#include "Game/UI/Action/EndGameButtonAction.h"

// ---------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------
ResultScene::ResultScene()
	: 
	m_spriteBatch{},
	m_texture{},
	m_texCenter{},
	m_isChangeScene{},
	m_gameData{},
	m_result{}
{
	// �X�N���[���V���b�g���擾
	m_captureTexture = GameData::GetInstance()->GetScreenShot();
}

// ---------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------
ResultScene::~ResultScene()
{
}

// ---------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------
void ResultScene::Initialize()
{
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �X�v���C�g�o�b�`���쐬����
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(context);
	// �e�N�X�`���̍쐬����уf�[�^�̎擾
	CreateTextures();
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// UI�̍쐬
	CreateUI();

	// BGM�̍Đ�
	Sound::ChangeBGM(Sound::BGM_TYPE::WIN);
}

// ---------------------------------------------
/// <summary>
/// �e�N�X�`�����쐬���A�f�[�^���擾����
/// </summary>
// ---------------------------------------------
void ResultScene::CreateTextures()
{
	// �e�N�X�`���̍쐬
	m_texture = GameResources::GetInstance()->GetTexture("result");

	DirectX::SimpleMath::Vector2 texSize{};

	// �e�N�X�`���̃T�C�Y�ƒ��S�_���v�Z����
	mylib::Texture::CalculateTextureCenter
	(
		m_texture,
		texSize,
		m_texCenter
	);

	// �X�N���[���V���b�g�̃T�C�Y�ƒ��S�_���v�Z����
	mylib::Texture::CalculateTextureCenter
	(
		m_captureTexture,
		texSize,
		m_captureTexCenter
	);
}

// ---------------------------------------------------------
/// <summary>
/// ���[�U�[�C���^�[�t�F�[�X�̒ǉ�
/// </summary>
/// <param name="textureName">�e�N�X�`����</param>
/// <param name="position">�ʒu</param>
/// <param name="scale">�X�P�[��</param>
/// <param name="anchor">�A���J�[</param>
/// <param name="action">�A�N�V����</param>
// ---------------------------------------------------------
void ResultScene::AddUserInterface(
	const std::string textureName,
	DirectX::SimpleMath::Vector2 position,
	DirectX::SimpleMath::Vector2 scale,
	ANCHOR anchor,
	IAction* action
)
{
	// �e�N�X�`���̎擾
	auto texture = GameResources::GetInstance()->GetTexture(textureName);
	// ���[�U�[�C���^�[�t�F�[�X�̐���
	auto ui = std::make_unique<UserInterface>();
	// ���[�U�[�C���^�[�t�F�[�X�̍쐬
	ui->Create(texture, position, scale, anchor, action);
	// ���[�U�[�C���^�[�t�F�[�X�̓o�^
	m_uiList.push_back(std::move(ui));
}

// ---------------------------------------------
/// <summary>
/// UI���쐬����
/// </summary>
// ---------------------------------------------
void ResultScene::CreateUI()
{
	// �^�C�g���ɖ߂�{�^���̒ǉ�
	AddUserInterface(
		"GoTitleUI",
		DirectX::SimpleMath::Vector2{ RETURN_BUTTON_POSITION },
		DirectX::SimpleMath::Vector2{ BUTTON_SIZE },
		ANCHOR::TOP_LEFT,
		new GoTitleButtonAction()
	);

	// �Q�[���I���{�^���̒ǉ�
	AddUserInterface(
		"GameEndUI",
		DirectX::SimpleMath::Vector2{ EXIT_BUTTON_POSITION },
		DirectX::SimpleMath::Vector2{ BUTTON_SIZE },
		ANCHOR::TOP_LEFT,
		new EndGameButtonAction()
	);
}

// ---------------------------------------------
/// <summary>
/// �V�[�����X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------
void ResultScene::Update(float elapsedTime)
{
	// �L�[�{�[�h�X�e�[�g�g���b�J�[���擾����
	const auto& kbTracker = CommonResources::GetInstance()->GetInputManager()->GetKeyboardTracker();

	// �X�y�[�X�L�[�������ꂽ��
	if (kbTracker->pressed.Space){
		m_isChangeScene = true;
	}

	// UI�̍X�V
	for (auto& ui : m_uiList)
	{
		ui->Update(elapsedTime);
	}
}

// ---------------------------------------------
/// <summary>
/// �`�悷��
/// </summary>
// ---------------------------------------------
void ResultScene::Render()
{
	// �R�����X�e�[�g���擾����
	auto states = CommonResources::GetInstance()->GetCommonStates();

	// �X�v���C�g�o�b�`�̊J�n�F�I�v�V�����Ń\�[�g���[�h�A�u�����h�X�e�[�g���w�肷��
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, states->NonPremultiplied());
	// �w�i�̕`��
	DrawBackground();
	// �X�N���[���V���b�g�̕`��
	DrawCaptureTexture();
	// �X�v���C�g�o�b�`�̏I���
	m_spriteBatch->End();

	// UI�̕`��
	for (auto& ui : m_uiList)
	{
		ui->Render();
	}
}

// ---------------------------------------------
/// <summary>
/// �X�N���[���V���b�g��`�悷��
/// </summary>
// ---------------------------------------------
void ResultScene::DrawCaptureTexture()
{

	// �w�i�O�ʂɃQ�[���f�[�^�����X�N�V����`��
	if (GameData::GetInstance()->GetScreenShot())
	{
		m_spriteBatch->Draw(
			m_captureTexture.Get(),		// �e�N�X�`��(SRV)
			CAPTURE_POSITION,			// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
			nullptr,					// ��`(RECT)
			DirectX::Colors::White,		// �w�i�F
			CAPTURE_ROTATION,			// ��]�p(���W�A��)
			m_captureTexCenter,			// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
			CAPTURE_SCALE,				// �X�P�[��(scale)
			DirectX::SpriteEffects_None,// �G�t�F�N�g(effects)
			0.0f						// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
		);
	}
}

// ---------------------------------------------
/// <summary>
/// �w�i��`�悷��
/// </summary>
// ---------------------------------------------
void ResultScene::DrawBackground()
{
	m_spriteBatch->Draw(
		m_texture.Get(),			// �e�N�X�`��(SRV)
		BACKGROUND_POSITION,		// �X�N���[���̕\���ʒu(origin�̕`��ʒu)
		nullptr,					// ��`(RECT)
		DirectX::Colors::White,		// �w�i�F
		BACKGROUND_ROTATION,		// ��]�p(���W�A��)
		m_texCenter,				// �e�N�X�`���̊�ɂȂ�\���ʒu(�`�撆�S)(origin)
		BACKGROUND_SCALE,			// �X�P�[��(scale)
		DirectX::SpriteEffects_None,// �G�t�F�N�g(effects)
		0.0f						// ���C���[�x(�摜�̃\�[�g�ŕK�v)(layerDepth)
	);
}


// ---------------------------------------------
/// <summary>
/// ��n������
/// </summary>
// ---------------------------------------------
void ResultScene::Finalize()
{
}

// ---------------------------------------------
/// <summary>
/// ���̃V�[��ID���擾����
/// </summary>
/// <returns>���̃V�[��ID</returns>
// ---------------------------------------------
IScene::SceneID ResultScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::TITLE;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

// ---------------------------------------------
/// <summary>
/// Escape�������ꂽ�Ƃ��̃V�[��ID���擾����
/// </summary>
/// <returns>���̃V�[��ID</returns>
// ---------------------------------------------
IScene::SceneID ResultScene::GetPrevSceneID() const
{
	return IScene::SceneID::TITLE;
}
