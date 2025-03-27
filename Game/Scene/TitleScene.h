// --------------------------------------------------
// 
// ���O:	TitleScene.h
// ���e:	�^�C�g���V�[����`�悷��N���X
// �쐬:	�r�c����
// 
// --------------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"
#include "IScene.h"
#include "Interface/IObserver.h"

// �O���錾
class CommonResources;
class Camera;
class Floor;
class Sea;
class TitleEnemy;
class SkySphere;
class Particle;
class CustomShader;
class QuestSelectSceneUIManager;
class UIAnchor;

/// <summary>
/// �^�C�g���V�[���N���X
/// </summary>
class TitleScene final : public IScene, public IObserver
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �^�C�g����ʂ̒x������
	static constexpr float DELAY = 1.5f;
	// �^�C�g����ʂ̃A�j���[�V�����I������
	static constexpr float ANIM_END = 1.5f;
	// �J�����̗h��鋭��
	static constexpr float SHAKE_POWER = 1.0f;

	// �J������fov
	static constexpr float FOV = 40.0f;
	// ������̎�O
	static constexpr float NEAR_Z = 0.1f;
	// ������̉�
	static constexpr float FAR_Z = 100000.0f;

	// �X�e�[�W�Z���N�g��ʂ̒x������
	static constexpr float STAGE_SELECT_DELAY = 2.5f;
	// �X�e�[�W�Z���N�g��ʂ̃A�j���[�V�����I������
	static constexpr float STAGE_SELECT_END = 1.0f;
	// �^�C�g���̒��S���W ��bottom�
	static constexpr float TITLE_LOGO_CENTER_Y = -165.0f;
	// �E�B���h�E�̕�
	static constexpr float WINDOW_WIDTH = 1280.0f;
	// �E�B���h�E�̍���
	static constexpr float WINDOW_HEIGHT = 720.0f;
	// �ő�X�e�[�W�C���f�b�N�X
	static constexpr int MAX_STAGE_INDEX = 1;
	// �ŏ��X�e�[�W�C���f�b�N�X
	static constexpr int MIN_STAGE_INDEX = 0;

	// ���̓��C�A�E�g
	std::vector<D3D11_INPUT_ELEMENT_DESC> InputElements =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// �萔�o�b�t�@
	struct CBuffer
	{
		DirectX::SimpleMath::Vector4	windowSize;	// �E�B���h�E�T�C�Y
		float							alpha;		// �����x
		DirectX::SimpleMath::Vector3	padding;	// ��
	};

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------

public:
	// �R���X�g���N�^
	TitleScene();
	// �f�X�g���N�^
	~TitleScene() override;

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
	// Escape�������ꂽ�Ƃ��̃V�[��ID���擾����
	SceneID GetPrevSceneID() const;

	// �L�[�{�[�h�̓��͂��擾
	void OnKeyPressed(const DirectX::Keyboard::Keys& key) override;
	// �L�[�{�[�h�̓��͂��擾
	void OnKeyDown(const DirectX::Keyboard::Keys& key) override;

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	//�@�g�p����L�[��o�^
	void AttachKeyInput();
	// �ˉe�s��̐���
	void CreateProjection();
	// �I�u�W�F�N�g�X�V����
	void UpdateObject(const float elapsedTime);
	// �I�u�W�F�N�g�𐶐�
	void CreateObjects();

	// space�L�[�������ꂽ�Ƃ��̏���
	void OnSpaceKey();
	// ��L�[�������ꂽ�Ƃ��̏���
	void OnUpKey();
	// ���L�[�������ꂽ�Ƃ��̏���
	void OnDownKey();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_projection;
	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	// �o�ߎ��Ԃ��擾
	float m_totalSeconds;

	//�@�J����
	std::unique_ptr<Camera> m_camera;
	// ��
	std::unique_ptr<Floor> m_floor;
	// �C
	std::unique_ptr<Sea> m_sea;
	// �G
	std::unique_ptr<TitleEnemy> m_enemy;
	// �V��
	std::unique_ptr<SkySphere> m_skySphere;
	// �p�[�e�B�N��
	std::unique_ptr<Particle> m_particle;
	// �I�𒆂̃X�e�[�W�ԍ�
	int m_selectIndex;
	// �J������h�炷��
	float m_shakePower;
	// UI�}�l�[�W���[
	std::unique_ptr<QuestSelectSceneUIManager> m_uiManager;
};