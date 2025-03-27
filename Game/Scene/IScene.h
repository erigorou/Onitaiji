// --------------------------------------------
// 
// ���O:	IScene.h
// �T�v:	�V�[���̃C���^�[�t�F�[�X�N���X
// �쐬:	�r�c����
// 
// --------------------------------------------

#pragma once

// �O���錾
class CommonResources;

/// <summary>
/// �V�[���̃C���^�[�t�F�[�X
/// </summary>
class IScene
{
public:
	// �V�[���h�c
	enum class SceneID : unsigned int
	{
		NONE,
		TITLE,
		PLAY,
		RESULT,
		END
	};

	// -----------------------------
	// �������z�֐�
	// -----------------------------
public:
	// �f�X�g���N�^
	virtual ~IScene() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�揈��
	virtual void Render() = 0;
	// �I������
	virtual void Finalize() = 0;

	// ���̃V�[��ID���擾����
	virtual SceneID GetNextSceneID() const = 0;
	// �O�̃V�[��ID���擾����
	virtual SceneID GetPrevSceneID() const = 0;
};
