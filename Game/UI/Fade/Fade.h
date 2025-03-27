//--------------------------------------------------------------------------------------
//
// ���O:	Fade.cpp
// �@�\:	�t�F�[�h�C���A�t�F�[�h�A�E�g�̏������s��
// �쐬:	�r�c����
//
//-------------------------------------------------------------------------------------
#ifndef FADE_DEFINED
#define FADE_DEFINED

#pragma once
// �C���N���[�h
#include "pch.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"

// �O���錾
class SceneManager;
class CustomShader;

/// <summary>
///	�t�F�[�h�N���X
/// </summary>
class Fade
{
	// -----------------------------
	// �Œ�l
	// -----------------------------
public:
	// �t�F�[�h�̏��
	enum class FadeType : UINT
	{
		FADE_IN,	// ���@���@��
		FADE_OUT,	// �Á@���@��
		END_DELAY,	// �t�F�[�h�I��
		FADE_NONE,	// �Ȃ�
	};

	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4	time;
	};

	// �C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	// �t�F�[�h�Ɏg�p����p�X
	static constexpr wchar_t VS_PATH[] = L"Resources/cso/FadeVS.cso";
	static constexpr wchar_t GS_PATH[] = L"Resources/cso/FadeGS.cso";
	static constexpr wchar_t PS_PATH[] = L"Resources/cso/FadePS.cso";

	// �}�X�N�Ɏg�p����p�X
	static constexpr wchar_t MASK_VS_PATH[] = L"Resources/cso/MaskVS.cso";
	static constexpr wchar_t MASK_GS_PATH[] = L"Resources/cso/MaskGS.cso";
	static constexpr wchar_t MASK_PS_PATH[] = L"Resources/cso/MaskPS.cso";

	// �t�F�[�h�̒x������
	static constexpr float CHANGE_SCENE_EDLAY = 1.0f;
	// �t�F�[�h�̎���
	static constexpr float FADE_TIME = 1.0f;
	// �t�F�[�h�̏����T�C�Y
	static constexpr float FADE_FIRST_SIZE = 1.25f;
	// �t�F�[�h�̍ő�T�C�Y
	static constexpr float FADE_MAX_SIZE = 6.0f;
	// �t�F�[�h�̂������l
	static constexpr float FADE_THRESHOLD = 0.7f;

	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// �t�F�[�h�C���̊J�n
	void StartFadeIn();
	// �t�F�[�h�A�E�g�̊J�n
	void StartFadeOut();
	// �t�F�[�h�̒�~
	void FadeStop();

	// �R���X�g���N�^
	Fade(SceneManager* scene);
	// �f�X�g���N�^
	~Fade();
	// ����������
	void Initialize();
	// �X�V����
	void Update(float elapsedTime);
	// �`�揈��
	void Render();

	// -----------------------------
	// �����o�֐�(����J)
	// -----------------------------
private:
	// �V�F�[�_�[�̐�������
	void CreateShader();
	// �^�C�}�[�̃J�E���g����
	void CountTimer();
	// �t�F�[�h�C��
	void FadeIn();
	// �t�F�[�h�A�E�g
	void FadeOut();
	// �t�F�[�h�I��
	void FadeEnd();
	// �t�F�[�h�ʂ��v�Z����
	float CalcrateFadeValue(float easing);
	// �^�����摜�̕`�揈��
	void DrawStencilImage();

	// -----------------------------
	// �����o�ϐ�
	// -----------------------------
private:
	// �V�[���}�l�[�W��
	SceneManager* m_scene;
	// 1F�̎���
	float m_elapsedTime;
	// �o�ߎ���
	float m_totalTime;
	// �t�F�[�h����
	float m_delayTime;
	// �t�F�[�h����
	bool m_isFade;
	// �t�F�[�h�I����
	bool m_endFade;
	// �t�F�[�h�̏��
	FadeType m_fadeType;
	// �C�[�W���O�l
	float m_easingValue;
	// �R���X�^���g�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_CBuffer;
	// ���_���
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
	// �J�X�^���V�F�[�_�[
	std::unique_ptr<CustomShader> m_customShader;
	// �}�X�N�V�F�[�_�[
	std::unique_ptr<CustomShader> m_maskShader;
	// ���[�h��ʂƂ��Ďg�p����e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
	// �}�X�N�p�̃e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_stencilImage;
	// �^�����摜�݂̂̕`�挋�ʂ����摜
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_capture;
	// �^�����摜�݂̂̕`�挋�ʂ����摜�̃r���[
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_captureRTV;
	// �^�����摜�݂̂̕`�挋�ʂ����摜�̃V�F�[�_�[���\�[�X�r���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_captureSRV;
};
#endif // !FADE_DEFINED