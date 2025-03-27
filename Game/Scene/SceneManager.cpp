// ---------------------------------------------
// 
// ���O:	SceneManager.cpp
// ���e:	�V�[���}�l�[�W���N���X
// �쐬:	�r�c����
// 
// ---------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "SceneManager.h"
#include "Game/UI/Fade/Fade.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "ResultScene.h"
#include "Game/Data/GameData.h"
#include "Game/GameResources.h"
#include "../Sound/Sound.h"
#include <cassert>
#include "Game/Messenger/KeyboardMessenger.h"

//---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
//---------------------------------------------------------
SceneManager::SceneManager()
	: 
	m_currentScene{},
	m_nextSceneID(IScene::SceneID::NONE),
	m_canChangeScene(false),
	m_isFade(false),
	m_isEscape(false)
{
	m_gameResources = GameResources::GetInstance();
	m_sound = Sound::GetInstance();
}

//---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
//---------------------------------------------------------
SceneManager::~SceneManager()
{
	Finalize();
}

//---------------------------------------------------------
/// <summary>
/// ����������
/// </summary>
//---------------------------------------------------------
void SceneManager::Initialize()
{
	m_fade = std::make_unique<Fade>(this);
	m_fade->Initialize();

// �f�o�b�O�Ȃ炱��
#ifdef _DEBUG
	ChangeScene(IScene::SceneID::TITLE);
#endif // !_DEBUG

// �����[�X�Ȃ炱��
#ifndef _DEBUG
	ChangeScene(IScene::SceneID::TITLE);
#endif // !_DEBUG
}

//---------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
//---------------------------------------------------------
void SceneManager::Update(float elapsedTime)
{
	// �L�[�{�[�h�g�p���m
	UpdateKeyboard();

	// �b���̕ۑ�
	GameData::GetInstance()->SetElapsedTime(elapsedTime);
	// ���ʉ��̍Đ�
	Sound::Update();
	// �e�V�[���̍X�V
	m_currentScene->Update(elapsedTime);
	// �t�F�[�h�̍X�V
	m_fade->Update(elapsedTime);

	// �����p�ϐ��F���̃V�[��
	IScene::SceneID nextSceneID =
		m_isEscape ? m_currentScene->GetPrevSceneID() : m_currentScene->GetNextSceneID();

	// �V�[����ύX���Ȃ��Ƃ�
	if (nextSceneID == IScene::SceneID::NONE && !m_isFade) return;

	// ����Z�b�g�A�b�v
	if (m_nextSceneID == IScene::SceneID::NONE)
	{
		m_nextSceneID = nextSceneID;
		m_isFade = true;
		m_fade->StartFadeOut();
		m_canChangeScene = false;
	}

	// �V�[���ύX�t���O��Fade�N���X������������true�ɂ���
	if (m_canChangeScene)
	{
		// Escape�L�[�̓��͂����Z�b�g
		m_isEscape = false;
		// �t�F�[�h���I��
		m_isFade = false;
		// �V�[����ύX
		ChangeScene(m_nextSceneID);
		// �V�[��ID��������
		m_nextSceneID = IScene::SceneID::NONE;
		// �V�[���ύX���֎~
		m_canChangeScene = false;
	}
}

//---------------------------------------------------------
/// <summary>
/// �`�悷��
/// </summary>
//---------------------------------------------------------
void SceneManager::Render()
{
	// �V�[���̕`��
	m_currentScene->Render();
	// �t�F�[�h�̕`��
	m_fade->Render();
}

//---------------------------------------------------------
/// <summary>
/// ��n������
/// </summary>
//---------------------------------------------------------
void SceneManager::Finalize()
{
	// �V�[�����폜
	DeleteScene();
}

//---------------------------------------------------------
/// <summary>
/// �V�[����ύX����
/// </summary>
//---------------------------------------------------------
void SceneManager::ChangeScene(IScene::SceneID sceneID)
{
	// �V�[�����폜
	DeleteScene();
	// �V�[�����쐬
	CreateScene(sceneID);
	// �t�F�[�h�C��
	m_fade->StartFadeIn();
}

//---------------------------------------------------------
/// <summary>
/// �V�[�����쐬����
/// </summary>
//---------------------------------------------------------
void SceneManager::CreateScene(IScene::SceneID sceneID)
{
	// �V�[�����쐬
	switch (sceneID)
	{
		// �^�C�g��
	case IScene::SceneID::TITLE:
		m_currentScene = std::make_unique<TitleScene>();
		break;

		// �v���C
	case IScene::SceneID::PLAY:
		m_currentScene = std::make_unique<PlayScene>();
		break;

		// ���U���g
	case IScene::SceneID::RESULT:
		m_currentScene = std::make_unique<ResultScene>();
		break;

		// �Q�[���I��
	case IScene::SceneID::END:
		PostQuitMessage(0);
		return;

	default:
		assert(!"SceneManager::CreateScene::�V�[���������݂��܂���I");
		// no break
	}

	// �ώ@�҃��X�g������������
	KeyboardMessenger::Clear();
	// �V�[����������
	m_currentScene->Initialize();
	// �ώ@�҃��X�g���\�[�g����
	KeyboardMessenger::SortObserverList();
	// �L�[�͈̓��X�g�𐶐�����
	KeyboardMessenger::CreateKeyRangeList();
}

//---------------------------------------------------------
/// <summary>
/// �V�[�����폜����
/// </summary>
//---------------------------------------------------------
void SceneManager::DeleteScene()
{
	// �V�[�������݂���ꍇ�@���@���̃V�[�������݂���ꍇ
	if (m_currentScene && m_nextSceneID != IScene::SceneID::END)
	{
		m_currentScene.reset();
	}
}

// ------------------------------------------------------------------------------
/// <summary>
/// �L�[�������ꂽ���ǂ����𔻒肷��
/// </summary>
/// <param name="stateTracker">�L�[�{�[�h�g���b�J�[</param>
/// <returns>�����ꂽ���̃t���O</returns>
// ------------------------------------------------------------------------------
inline bool IsKeyPress(DirectX::Keyboard::KeyboardStateTracker& stateTracker)
{
	// ���ׂẴL�[�������ꂽ���ǂ������`�F�b�N
	for (int key = 0; key < PlayScene::MAX_KEY; key++)
	{
		// ����̃L�[��������Ă��邩���m�F
		if (stateTracker.IsKeyPressed(static_cast<DirectX::Keyboard::Keys>(key)))
		{
			return true; // �����ꂽ�L�[������� true ��Ԃ�
		}
	}
	// �ǂ̃L�[��������Ă��Ȃ��ꍇ
	return false;
}

// ------------------------------------------------------------------------------
/// <summary>
/// �L�[��������Ă��邩�ǂ����𔻒肷��
/// </summary>
/// <param name="state">�L�[�{�[�h�X�e�[�g</param>
/// <returns>������Ă��邩�̃t���O</returns>
// ------------------------------------------------------------------------------
inline bool IsKeyDown(DirectX::Keyboard::State& state)
{
	// �L�[�{�[�h�X�e�[�g�ւ̃|�C���^���擾����
	auto ptr = reinterpret_cast<uint32_t*>(&state);
	for (int key = 0; key < 0xff; key++)
	{
		const unsigned int buffer = 1u << (key & 0x1f);
		// �L�[����������ꂽ���ǂ����𒲂ׂ�
		if (ptr[(key >> 5)] && buffer)	 return true;
	}
	// �L�[�͉��������Ă��Ȃ�
	return false;
}

// ------------------------------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̓��͂��X�V����
/// </summary>
// ------------------------------------------------------------------------------
void SceneManager::UpdateKeyboard()
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	m_keyboardState = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�X�e�[�g�g���b�J�[���X�V����
	m_keyboardStateTracker.Update(m_keyboardState);

	// �L�[�{�[�h����������ꂽ���ǂ����𔻒肷��
	if (IsKeyDown(m_keyboardState))			KeyboardMessenger::Notify(m_keyboardState);
	if (IsKeyPress(m_keyboardStateTracker))	KeyboardMessenger::Notify(m_keyboardStateTracker);

	// ESCAPE�L�[�������ꂽ�ꍇ
	if (m_keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::Keys::Escape)){
		OnEscapeKeyEvent();
	}
}

// ------------------------------------------------------------------------------
/// <summary>
/// Escape�������ꂽ�Ƃ��̃C�x���g
/// </summary>
// ------------------------------------------------------------------------------
void SceneManager::OnEscapeKeyEvent()
{
	m_isEscape = true;
}
