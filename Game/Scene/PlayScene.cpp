// ------------------------------------------------------------------------------
// 
// ���O:	PlayScene
// ���e:	�v���C�V�[���̃I�u�W�F�N�g�𐶐����A�X�V�A�`����s��
// ����:	�r�c����
// 
// ------------------------------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "PlayScene.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Factory/Factory.h"
#include "Game/Sound/Sound.h"
#include "Game/HitStop/HitStop.h"
#include "Libraries/MyLib/Collision/CollisionManager.h"
#include "Game/Data/GameData.h"
#include "Game/Messenger/KeyboardMessenger.h"
#include "Game/Quest/QuestManager.h"
#include "Game/Messenger/EventMessenger.h"
#include "Game/EnemyManager/EnemyManager.h"
#include "Game/Player/Player.h"
#include "Game/Boss/Boss.h"
#include "Game/Stage/Floor/Floor.h"
#include "Game/Stage/Sea/Sea.h"
#include "Game/Stage/Wall/Wall.h"
#include "Game/Stage/SkySphere/SkySphere.h"
#include "Game/UI/!PlaySceneUIManager/PlaySceneUIManager.h"
#include "Effects/Particle.h"
#include "Game/Camera/Camera.h"

// ------------------------------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ------------------------------------------------------------------------------
PlayScene::PlayScene()
	: 
	m_projection{},
	m_isChangeScene{ false },
	m_isScreenShot{ false },
	m_smoothDeltaTime{}
{
	GameData::GetInstance()->SetBattleResult(GameData::BATTLE_RESULT::NONE);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ------------------------------------------------------------------------------
PlayScene::~PlayScene()
{
}

// ------------------------------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::Initialize()
{
	// �f�o�b�O�J�������쐬����
	RECT rect{ CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize() };

	// �ˉe�s����쐬����
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(FOV),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		NEAR_Z, FAR_Z);

	// �I�u�W�F�N�g�̐���
	CreateObjects();

	// �C�x���g��o�^���� (�V�[���I��)
	EventMessenger::Attach(EventList::EndPlayScene, std::bind(&PlayScene::ChangeResultScene, this));
	// �C�x���g��o�^���� (�X�N���[���V���b�g)
	EventMessenger::Attach(EventList::TakeCapture, std::bind(&PlayScene::TakeCapture, this));

	// �L�[�{�[�h��o�^����
	KeyboardMessenger::Attach(DirectX::Keyboard::Keys::Space, this, KeyboardMessenger::KeyPressType::PRESSED);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �I�u�W�F�N�g�̐���
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::CreateObjects()
{
	// �΂��ƃX�g�b�v���擾
	m_hitStop = HitStop::GetInstance();
	// �p�[�e�B�N���𐶐�
	m_collisionManager = Factory::CreateCollisionManager();
	// �J�����𐶐�
	m_camera = Factory::CreateCamera();
	// �p�[�e�B�N���𐶐�
	m_particles = Factory::CreateParticle();
	// �V���𐶐�
	m_skySphere = Factory::CreateSkySphere();
	// ���𐶐�
	m_floor = Factory::CreateFloor();
	// �C�𐶐�
	m_sea = Factory::CreateSea();
	// �ǂ𐶐�
	m_wall = Factory::CreateWall();
	// �v���C���[�𐶐�
	m_player = Factory::CreatePlayer();

	// �G�}�l�[�W���[
	m_enemyManager = Factory::CreateEnemyManager();
	// �N�G�X�g�}�l�[�W���[
	m_questManager = Factory::CreateQuestManager(this);

	// UI�}�l�[�W���[�𐶐�
	m_uiManager = Factory::CreateUIManager(this);

	// �J�����̏�Ԃ�ύX
	CameraState state = CameraState::Play;
	EventMessenger::Execute(EventList::ChangeCamera, &state);

	// BGM�ύX
	Sound::GetInstance()->ChangeBGM(Sound::BGM_TYPE::PLAY);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ------------------------------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	// �I�u�W�F�N�g�̍X�V����
	UpdateObjects(elapsedTime);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �I�u�W�F�N�g�̍X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ------------------------------------------------------------------------------
void PlayScene::UpdateObjects(float elapsedTime)
{
	// �q�b�g�X�g�b�v�̍X�V
	m_hitStop->Update(elapsedTime);
	// �q�b�g�X�g�b�v�̎c�莞�Ԃ��擾
	float smoothDeltaTime = m_hitStop->GetSmoothDeltaTime();

	// UI�}�l�W���[�̍X�V
	m_uiManager->Update(elapsedTime);
	// �v���C���[�̍X�V
	m_player->Update(smoothDeltaTime);
	// �G�}�l�[�W���[�̍X�V
	m_enemyManager->Update(smoothDeltaTime);
	// �N�G�X�g�}�l�[�W���[�̍X�V
	m_questManager->Update(elapsedTime);
	// �J�����̍X�V
	UpdateCamera(elapsedTime);

	// �p�[�e�B�N���̍X�V
	m_particles->Update(elapsedTime, m_player->GetPosition(), m_player->GetVelocity());

	// �Փ˔���̍X�V����
	m_collisionManager->Update();
	// �Q�[���I�[�o�[����
	GameOverChacker();
}

// ------------------------------------------------------------------------------
/// <summary>
/// �v���C�V�[���̃I�u�W�F�N�g�̕`�揈��
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::Render()
{
	// �r���[�s����擾����
	const DirectX::SimpleMath::Matrix& view = m_camera->GetViewMatrix();
	// �����蔻���`��
	m_collisionManager->Render(view, m_projection);
	// ��̕`��
	m_skySphere->DrawSkySphere(view, m_projection);
	// �n�ʂ̕`��
	m_floor->Render(view, m_projection);
	// �C�̕`��
	m_sea->Render(view, m_projection);
	// �ǂ̕`��
	m_wall->Render(view, m_projection);
	// �v���C���[�̕`��
	m_player->Render(view, m_projection);
	// �G�i�����j�̕`��
	m_enemyManager->Render(view, m_projection);

	if (m_isScreenShot)
	{
		// �X�N���[���V���b�g�����
		TakeScreenShot();
	}

	// �p�[�e�B�N���̕`��
	DrawParticle(view, m_projection);
	// �N�G�X�g�̕`��
	m_questManager->DrawQuest();
	// UI�̕`��
	m_uiManager->Render();
}

// ------------------------------------------------------------------------------
/// <summary>
/// �p�[�e�B�N���̕`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
// ------------------------------------------------------------------------------
void PlayScene::DrawParticle(const DirectX::SimpleMath::Matrix& view, DirectX::SimpleMath::Matrix projection)
{
	// �r���{�[�h�s��̌v�Z
	m_particles->CreateBillboard(m_camera->GetTargetPosition(), m_camera->GetEyePosition(), DirectX::SimpleMath::Vector3::Up);
	// �p�[�e�B�N���̕`��
	m_particles->Render(view, projection);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �I���֐�
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::Finalize()
{
	// �C�x���g����������
	EventMessenger::Detach(EventList::EndPlayScene);
	EventMessenger::Detach(EventList::TakeCapture);
	// �L�[�{�[�h����������
	KeyboardMessenger::Detach(DirectX::Keyboard::Keys::Space, this, KeyboardMessenger::KeyPressType::PRESSED);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �J�����̍X�V����
/// 
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ------------------------------------------------------------------------------
void PlayScene::UpdateCamera(float elapsedTime)
{
	// �G�^�[�Q�b�g�̍��W���擾
	DirectX::SimpleMath::Vector3 targetPos = 
		*(DirectX::SimpleMath::Vector3*)EventMessenger::ExecuteGetter(GetterList::GetTargetPosition);

	// �J�����̍X�V
	m_camera->Update(m_player->GetPosition(),targetPos, elapsedTime);
}

// ------------------------------------------------------------------------------
/// <summary>
/// �{�X�̃|�C���^���擾
/// </summary>
/// <returns>�{�X�|�C���^</returns>
// ------------------------------------------------------------------------------
Boss* PlayScene::GetBoss()
{
	return m_enemyManager->GetBossEnemy();
}


// ------------------------------------------------------------------------------
/// <summary>
/// ���̃V�[����ID���擾
/// </summary>
/// <returns>�V�[��</returns>
// ------------------------------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		switch (GameData::GetInstance()->GetBattleResult())
		{
			// ���������΂����̓��U���g�ɑJ��
		case GameData::BATTLE_RESULT::WIN:
			return IScene::SceneID::RESULT;
			break;

			// �s�k�����ꍇ�͂��̂܂܃^�C�g���ɑJ��
		case GameData::BATTLE_RESULT::LOSE:
			return IScene::SceneID::TITLE;
			break;
		}
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

// ------------------------------------------------------------------------------
/// <summary>
/// ESCAPE�������ꂽ�Ƃ��̃V�[��ID���擾
/// </summary>
/// <returns>�V�[���ԍ�</returns>
// ------------------------------------------------------------------------------
IScene::SceneID PlayScene::GetPrevSceneID() const
{
	return IScene::SceneID::TITLE;
}

// ------------------------------------------------------------------------------
/// <summary>
/// ���U���g�ɑJ�ڂ���
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::ChangeResultScene()
{
	// ���s��o�^����
	auto data = GameData::GetInstance();
	data->SetBattleResult(GameData::BATTLE_RESULT::WIN);

	// �V�[���J�ڃt���O�𗧂Ă�
	m_isChangeScene = true;
}

// ------------------------------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̓��͌��m���s���i�����ꂽ�u�ԁj
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ------------------------------------------------------------------------------
void PlayScene::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	// Space�L�[�Ń^�[�Q�b�g��ύX
	if (key == DirectX::Keyboard::Keys::Space) m_enemyManager->ChangeCameraTarget();
}

// ------------------------------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̓��͌��m���s���i������Ă���ԁj
/// </summary>
/// <param name="key">�����ꂽ�L�[</param>
// ------------------------------------------------------------------------------
void PlayScene::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}


// ------------------------------------------------------------------------------
/// <summary>
/// �Q�[���I�[�o�[�𔻒肷��
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::GameOverChacker()
{
	// �v���C���[�����S
	if (m_player->GetPlayerHP()->GetHP() <= 0)
	{
		// ���s��o�^����
		auto data = GameData::GetInstance();
		data->SetBattleResult(GameData::BATTLE_RESULT::LOSE);

		// �V�[���J�ڃt���O�𗧂Ă�
		m_isChangeScene = true;
	}
}


// ------------------------------------------------------------------------------
/// <summary>
/// �X�N���[���V���b�g�����(�e�N�X�`���Ƃ��ĕۑ�����)
/// </summary>
// ------------------------------------------------------------------------------
void PlayScene::TakeScreenShot()
{
	// ���łɃX�N���[���V���b�g������Ă���ꍇ�͉������Ȃ�
	if (m_captureSRV != nullptr) return;

	// �f�o�C�X���\�[�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources();
	ID3D11Device* d3dDevice = device->GetD3DDevice();
	ID3D11DeviceContext* context = device->GetD3DDeviceContext();

	// ���݂̃����_�[�^�[�Q�b�g�r���[���擾
	ID3D11RenderTargetView* currentRTV = device->GetRenderTargetView();
	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	currentRTV->GetResource(&backBuffer);

	// �o�b�N�o�b�t�@�e�N�X�`�����擾
	Microsoft::WRL::ComPtr<ID3D11Texture2D> backBufferTex;
	backBuffer.As(&backBufferTex);

	// �o�b�N�o�b�t�@�̃e�N�X�`���ݒ���擾
	D3D11_TEXTURE2D_DESC desc = {};
	backBufferTex->GetDesc(&desc);

	// GPU �p�� DEFAULT �e�N�X�`�����쐬
	desc.Usage = D3D11_USAGE_DEFAULT; // GPU �Ŏg�p�\�ɂ���
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE; // �V�F�[�_�[���\�[�X�Ƃ��ăo�C���h
	desc.CPUAccessFlags = 0; // CPU ����̃A�N�Z�X�͕s�v
	Microsoft::WRL::ComPtr<ID3D11Texture2D> gpuTexture;
	HRESULT hr = d3dDevice->CreateTexture2D(&desc, nullptr, &gpuTexture);
	if (FAILED(hr)) return;

	// CPU �ǂݎ��p�� STAGING �e�N�X�`�����쐬
	desc.Usage = D3D11_USAGE_STAGING; // CPU �ǂݎ���p
	desc.BindFlags = 0; // �o�C���h�s�v
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ; // CPU �œǂݎ��\�ɐݒ�
	Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
	hr = d3dDevice->CreateTexture2D(&desc, nullptr, &stagingTexture);
	if (FAILED(hr)) return;

	// GPU �̃����_�[�^�[�Q�b�g���� STAGING �e�N�X�`���Ƀf�[�^���R�s�[
	context->CopyResource(stagingTexture.Get(), backBufferTex.Get());

	// STAGING �e�N�X�`������ DEFAULT �e�N�X�`���ɍăR�s�[
	context->CopyResource(gpuTexture.Get(), stagingTexture.Get());

	// �V�F�[�_�[���\�[�X�r���[���쐬
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format; // �t�H�[�}�b�g��ݒ�
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; // 2D �e�N�X�`���Ƃ��Đݒ�
	srvDesc.Texture2D.MipLevels = 1; // �~�b�v�}�b�v���x�������w��
	srvDesc.Texture2D.MostDetailedMip = 0; // �ŏ��̃~�b�v�}�b�v���x�����w��

	hr = d3dDevice->CreateShaderResourceView(gpuTexture.Get(), &srvDesc, &m_captureSRV);
	if (FAILED(hr)) return;

	// �X�N���[���V���b�g��ۑ�
	GameData::GetInstance()->SetScreenShot(m_captureSRV);
}
