// --------------------------------------------------
// 
// ���O:	TitleScene.h
// ���e:	�^�C�g���V�[����`�悷��N���X
// �쐬:	�r�c����
// 
// --------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "TitleScene.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "../Factory/Factory.h"
#include "../Sound/Sound.h"
#include "../Data/GameData.h"
#include "Libraries/MyLib/Math.h"
#include "Effects/Particle.h"
#include "Game/UI/SceneUIManager/QuestSelectSceneUIManager.h"
#include "Game/Messenger/EventMessenger.h"
#include "../Camera/Camera.h"
#include "../Stage/Floor/Floor.h"
#include "../Stage/Sea/Sea.h"
#include "../TitleObject/TitleEnemy.h"
#include "../Stage/SkySphere/SkySphere.h"

#include "Game/Messenger/KeyboardMessenger.h"

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_totalSeconds{},
	m_isChangeScene{},
	m_selectIndex{},
	m_shakePower{ SHAKE_POWER }
{
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
TitleScene::~TitleScene()
{
	Finalize();
}

// ---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
// ---------------------------------------------------------
void TitleScene::Initialize()
{
	// �L�[���͂�o�^
	AttachKeyInput();
	// �I�u�W�F�N�g�𐶐�����
	CreateObjects();
	// �ˉe�s��𐶐�����
	CreateProjection();
	// �V�[���ύX�t���O������������
	m_isChangeScene = false;
	// ���y�̕ύX
	Sound::ChangeBGM(Sound::BGM_TYPE::TITLE);
}

// ---------------------------------------------------------
/// <summary>
/// �I�u�W�F�N�g��������
/// </summary>
// ---------------------------------------------------------
void TitleScene::CreateObjects()
{
	// �J�����̐���
	m_camera = Factory::CreateCamera();
	// ���̐���
	m_floor = Factory::CreateFloor();
	// �C�̐���
	m_sea = Factory::CreateSea();
	// �V���̐���
	m_skySphere = Factory::CreateSkySphere();

	// �G�̐���
	m_enemy = std::make_unique<TitleEnemy>();
	m_enemy->Initialize();

	// �p�[�e�B�N���̐���
	m_particle = Factory::CreateParticle();

	// �J�����̏�Ԃ�ύX
	CameraState state = CameraState::Title;
	EventMessenger::Execute(EventList::ChangeCamera, &state);

	// UI�̐���
	m_uiManager = std::make_unique<QuestSelectSceneUIManager>();
	m_uiManager->Initialize();

	// �Q�[���f�[�^�ɃX�e�[�W��ݒ�
	auto gameData = GameData::GetInstance();
	gameData->SetSelectStage(m_selectIndex);
}


void TitleScene::AttachKeyInput()
{
	KeyboardMessenger::Attach(DirectX::Keyboard::Up, this, KeyboardMessenger::KeyPressType::PRESSED);
	KeyboardMessenger::Attach(DirectX::Keyboard::Down, this, KeyboardMessenger::KeyPressType::PRESSED);
	KeyboardMessenger::Attach(DirectX::Keyboard::Space, this, KeyboardMessenger::KeyPressType::PRESSED);
}

// ---------------------------------------------------------
/// <summary>
/// �ˉe�s�񐶐�����
/// </summary>
// ---------------------------------------------------------
void TitleScene::CreateProjection()
{
	// �E�B���h�E�̃T�C�Y���擾����
	RECT rect{ CommonResources::GetInstance()->GetDeviceResources()->GetOutputSize() };

	// �ˉe�s����쐬����
	m_projection = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		DirectX::XMConvertToRadians(FOV),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		NEAR_Z, FAR_Z
	);
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// �b�������Z����
	m_totalSeconds += elapsedTime;

	// �I�u�W�F�N�g�̍X�V
	UpdateObject(elapsedTime);
	// �p�[�e�B�N���̍X�V
	m_particle->Update(elapsedTime, DirectX::SimpleMath::Vector3::Zero, DirectX::SimpleMath::Vector3::Zero);
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void TitleScene::UpdateObject(const float elapsedTime)
{
	// �[���x�N�g��
	DirectX::SimpleMath::Vector3 zeroV = DirectX::SimpleMath::Vector3::Zero;

	// �I�u�W�F�N�g�̍X�V
	m_camera->Shake(elapsedTime);
	m_camera->Update(zeroV, zeroV, elapsedTime);
	m_enemy->Update(elapsedTime);

	// UI�̍X�V
	m_uiManager->Update(elapsedTime);
}

// ---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
// ---------------------------------------------------------
void TitleScene::Render()
{
	// �r���[�s����擾����
	auto view = m_camera->GetViewMatrix();
	// ���̕`��
	m_floor->Render(view, m_projection);
	// �C�̕`��
	m_sea->Render(view, m_projection);
	// �G�̕`��
	m_enemy->Render(view, m_projection);
	// �V���̕`��
	m_skySphere->DrawSkySphere(view, m_projection);
	// �p�[�e�B�N���̕`��
	m_particle->CreateBillboard(m_camera->GetEyePosition(), DirectX::SimpleMath::Vector3::Zero, m_camera->GetUpVector());
	m_particle->Render(view, m_projection);
	// UI�̕`��
	m_uiManager->Render();
}

// ---------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------------------
void TitleScene::Finalize()
{
	// �I�u�W�F�N�g�̏I������
	m_camera.reset();
	m_floor.reset();
	m_sea.reset();
	m_enemy.reset();
	m_skySphere.reset();
	m_particle.reset();
	m_uiManager.reset();
}

// ---------------------------------------------------------
/// <summary>
/// ���̃V�[��ID�擾����
/// </summary>
/// <returns>���̃V�[��ID</returns>
// ---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// �V�[���ύX������ꍇ
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// �V�[���ύX���Ȃ��ꍇ
	return IScene::SceneID::NONE;
}

// ---------------------------------------------------------
/// <summary>
/// Escape�������ꂽ�ꍇ�̃V�[��ID���擾����
/// </summary>
/// <returns>�ύX��̃V�[��ID</returns>
// ---------------------------------------------------------
IScene::SceneID TitleScene::GetPrevSceneID() const
{
	return IScene::SceneID::END;
}

// ---------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̓��͂��擾
/// </summary>
/// <param name="key">�L�[</param>
// ---------------------------------------------------------
void TitleScene::OnKeyPressed(const DirectX::Keyboard::Keys& key)
{
	// �V�[���ύX���͏������Ȃ�
	if (m_isChangeScene) return;

	// �X�y�[�X�L�[�������ꂽ��
	if (key == DirectX::Keyboard::Space) OnSpaceKey();
	// ��L�[�������ꂽ��
	if (key == DirectX::Keyboard::Up) OnUpKey();
	// ���L�[�������ꂽ��
	if (key == DirectX::Keyboard::Down) OnDownKey();
}

// ---------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̓��͂��擾
/// </summary>
/// <param name="key">�L�[</param>
// ---------------------------------------------------------
void TitleScene::OnKeyDown(const DirectX::Keyboard::Keys& key)
{
	UNREFERENCED_PARAMETER(key);
}


// ---------------------------------------------------------
/// <summary>
/// �X�y�[�X�L�[�������ꂽ�Ƃ��̏���
/// </summary>
// ---------------------------------------------------------
void TitleScene::OnSpaceKey()
{
	// �V�[���ύX�t���O�𗧂Ă�̂Ɖ��y��炷
	m_isChangeScene = true;
	Sound::PlaySE(Sound::SE_TYPE::SYSTEM_OK);

	// �Q�[���f�[�^�ɃX�e�[�W��ݒ�
	auto gameData = GameData::GetInstance();
	gameData->SetSelectStage(m_selectIndex);
}


// ---------------------------------------------------------
/// <summary>
/// ��L�[�������ꂽ�Ƃ��̏���
/// </summary>
// ---------------------------------------------------------
void TitleScene::OnUpKey()
{
	// �I���C���f�b�N�X�����炷
	m_selectIndex = Math::Clamp(m_selectIndex - 1, MIN_STAGE_INDEX, MAX_STAGE_INDEX);

	// �Q�[���f�[�^�ɃX�e�[�W��ݒ�
	auto gameData = GameData::GetInstance();
	gameData->SetSelectStage(m_selectIndex);
}

// ---------------------------------------------------------
/// <summary>
/// ���L�[�������ꂽ�Ƃ��̏���
/// </summary>
// ---------------------------------------------------------
void TitleScene::OnDownKey()
{
	// �I���C���f�b�N�X�𑝂₷
	m_selectIndex = Math::Clamp(m_selectIndex + 1, MIN_STAGE_INDEX, MAX_STAGE_INDEX);

	// �Q�[���f�[�^�ɃX�e�[�W��ݒ�
	auto gameData = GameData::GetInstance();
	gameData->SetSelectStage(m_selectIndex);
}