#pragma once
#include <unordered_map>

class GameResources
{
	// ------------------------
	// �t�@�C���p�X
	// ------------------------
public:
	// ���f����Json�t�@�C��
	static const wchar_t* MODEL_JSON;
	// �e�N�X�`����Json�t�@�C��
	static const wchar_t* TEXTURE_JSON;

	static const wchar_t* MODEL_BASE_PATH;
	static const wchar_t* TEXTURE_BASE_PATH;

	// ------------------------
	// �A�N�Z�T
	// ------------------------
public:

	// Resouces�N���X�̃C���X�^���X���擾����
	static GameResources* const GetInstance();
	// ���f�����擾����
	DirectX::Model* GetModel(std::string key) const;
	// �e�N�X�`�����擾����
	ID3D11ShaderResourceView* GetTexture(std::string key) const;

	// ------------------------
	// ���J�֐�
	// ------------------------
public:
	// �R���X�g���N�^
	GameResources();
	// �f�X�g���N�^
	~GameResources() = default;

	// ------------------------
	// �����֐�
	// ------------------------
private:
	// Json�t�@�C����ǂݍ���Ń��f���𐶐�����
	void LoadModelFromJson();

	// �e�N�X�`����ǂݍ���
	void LoadTexture();

	// ------------------------
	// �����ϐ�
	// ------------------------
private:

	// ���\�[�X
	static std::unique_ptr<GameResources> m_resources;

	// ���f�����X�g
	std::unordered_map<std::string, std::unique_ptr<DirectX::Model>> m_modelList;

	// �e�N�X�`�����X�g
	std::unordered_map<std::string, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> m_textureList;
};