#include "pch.h"
#include "GameResources.h"
#include <fstream>
#include "nlohmann/json.hpp"
#include "CommonResources.h"
#include "DeviceResources.h"

// ���j�[�N�|�C���^
std::unique_ptr<GameResources> GameResources::m_resources = nullptr;

// ���f����Json�t�@�C��
const wchar_t* GameResources::MODEL_JSON = L"Resources/Jsons/ModelData.Json";
// �e�N�X�`����Json�t�@�C��
const wchar_t* GameResources::TEXTURE_JSON = L"Resources/Jsons/TextureData.Json";

// ���f���̃x�[�X�p�X
const wchar_t* GameResources::MODEL_BASE_PATH = L"Resources/Models/";
// �e�N�X�`���̃x�[�X�p�X
const wchar_t* GameResources::TEXTURE_BASE_PATH = L"Resources/Textures/";

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
GameResources::GameResources()
{
	// Json�t�@�C����ǂݍ���Ń��f���𐶐�����
	LoadModelFromJson();
	// �e�N�X�`����ǂݍ���
	LoadTexture();
}

//---------------------------------------------------------
// �C���X�^���X���擾
//---------------------------------------------------------
GameResources* const GameResources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// GameResources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new GameResources());
	}
	// GameResources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

// --------------------------------------------------------
// Json�t�@�C����ǂݍ���Ń��f���𐶐�����
// --------------------------------------------------------
void GameResources::LoadModelFromJson()
{
	// Json�t�@�C�����J��
	std::ifstream ifs(MODEL_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "Json�t�@�C����������܂���", "�G���[", MB_OK);
		return; // �������I��
	}

	// �f�o�C�X���擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// Json�t�@�C����ǂݍ���
	nlohmann::json json = nlohmann::json::parse(ifs);

	// Json�f�[�^�����ɏ���
	for (auto it = json.begin(); it != json.end(); ++it)
	{
		// �L�[�ƒl���擾
		std::string key = it.key();
		std::string pathStr = it.value();

		// std::string��std::wstring�ɕϊ�
		std::wstring path = MODEL_BASE_PATH + std::wstring(pathStr.begin(), pathStr.end());

		// ���f���t�@�N�g���̐���
		std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
		fx->SetDirectory(L"Resources/Models");

		// ���f���𐶐�
		auto model = DirectX::Model::CreateFromCMO(device, path.c_str(), *fx);

		// ���f�������X�g�ɒǉ�
		m_modelList[key] = std::move(model);
	}
}

// --------------------------------------------------------
// Json�t�@�C����ǂݍ���Ńe�N�X�`���𐶐�����
// --------------------------------------------------------
void GameResources::LoadTexture()
{
	// Json�t�@�C�����J��
	std::ifstream ifs(TEXTURE_JSON);
	if (!ifs)
	{
		MessageBoxA(nullptr, "Json�t�@�C����������܂���", "�G���[", MB_OK);
		return; // �������I��
	}

	// �f�o�C�X���擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	// Json�t�@�C����ǂݍ���
	nlohmann::json json = nlohmann::json::parse(ifs);

	// Json�f�[�^�����ɏ���
	for (auto it = json.begin(); it != json.end(); ++it)
	{
		// �L�[�ƒl���擾
		std::string key = it.key();
		std::string pathStr = it.value();

		// std::string��std::wstring�ɕϊ�
		std::wstring path = TEXTURE_BASE_PATH + std::wstring(pathStr.begin(), pathStr.end());

		// �e�N�X�`���𐶐�
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;

		DirectX::CreateWICTextureFromFile(
			device,
			path.c_str(),
			nullptr,
			texture.GetAddressOf()
		);

		// �e�N�X�`�������X�g�ɒǉ�
		m_textureList[key] = texture;
	}
}

DirectX::Model* GameResources::GetModel(std::string key) const
{
	// �L�[������
	auto it = m_modelList.find(key);
	if (it != m_modelList.end())
	{
		// ���f����Ԃ�
		return it->second.get();
	}
	else
	{
		// �G���[���b�Z�[�W��\��
		MessageBoxA(nullptr, "���f����������܂���", "�G���[", MB_OK);
		return nullptr;
	}
}

//---------------------------------------------------------
// �e�N�X�`�����擾����
//---------------------------------------------------------
ID3D11ShaderResourceView* GameResources::GetTexture(std::string key) const
{
	// �L�[������
	auto it = m_textureList.find(key);
	if (it != m_textureList.end())
	{
		// �e�N�X�`����Ԃ�
		return it->second.Get();
	}
	else
	{
		// �G���[���b�Z�[�W��\��
		MessageBoxA(nullptr, "�e�N�X�`����������܂���", "�G���[", MB_OK);
		return nullptr;
	}
}