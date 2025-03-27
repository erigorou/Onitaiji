//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

// ��include�̒ǋL��
#include "Game/CommonResources.h"
#include "Game/Scene/IScene.h"
#include "Game/Scene/SceneManager.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game final : public DX::IDeviceNotify
{
public:

	Game() noexcept(false);
	~Game() = default;

	Game(Game&&) = default;
	Game& operator= (Game&&) = default;

	Game(Game const&) = delete;
	Game& operator= (Game const&) = delete;

	// Initialization and management
	void Initialize(HWND window, int width, int height);

	// Basic game loop
	void Tick();

	// IDeviceNotify
	void OnDeviceLost() override;
	void OnDeviceRestored() override;

	// Messages
	void OnActivated();
	void OnDeactivated();
	void OnSuspending();
	void OnResuming();
	void OnWindowMoved();
	void OnDisplayChange();
	void OnWindowSizeChanged(int width, int height);

	// Properties
	void GetDefaultSize(int& width, int& height) const noexcept;

	// ��ʃ��[�h��ݒ肷��֐��iTRUE�F�t���X�N���[���j
	void SetFullscreenState(BOOL value)
	{
		m_fullscreen = value;
		m_deviceResources->GetSwapChain()->SetFullscreenState(m_fullscreen, nullptr);
		if (value) m_deviceResources->CreateWindowSizeDependentResources();
	}

private:

	void Update(DX::StepTimer const& timer);
	void Render();

	void Clear();

	void CreateDeviceDependentResources();
	void CreateWindowSizeDependentResources();

	// Device resources.
	std::unique_ptr<DX::DeviceResources>    m_deviceResources;

	// Rendering loop timer.
	DX::StepTimer                           m_timer;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>  m_commonStates;
	// �R�������\�[�X
	CommonResources* m_commonResources;
	// �f�o�b�O�X�g�����O
	std::unique_ptr<mylib::DebugString>     m_debugString;
	// ���̓}�l�[�W��
	std::unique_ptr<mylib::InputManager>    m_inputManager;
	// �V�[���}�l�[�W��
	std::unique_ptr<SceneManager>           m_sceneManager;

	BOOL m_fullscreen;	// ���\�R���X�g���N�^��FALSE�ŏ��������Ă��������B
};
