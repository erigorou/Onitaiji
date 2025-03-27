// ---------------------------------------------------------
// 
// ���O:    Sound.cpp
// ���e:    �T�E���h�Ǘ��N���X
//          FMOD���g�p���ăT�E���h���Đ�����
// �쐬:    �r�c����
// 
// ---------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/Sound/Sound.h"
#include "Libraries/FMOD/inc/fmod.hpp"
#include "Game/Data/GameData.h"

std::unique_ptr<Sound> Sound::s_sound = nullptr;

// ---------------------------------------------------------
/// <summary>
/// �C���X�^���X��Ԃ��֐�
/// </summary>
/// <returns>Sound�̃C���X�^���X</returns>
// ---------------------------------------------------------
Sound* const Sound::GetInstance()
{
    // �C���X�^���X����������Ă��Ȃ��ꍇ
    if (s_sound == nullptr)
    {
        // ��������
        s_sound.reset(new Sound());
    }

    // �C���X�^���X��Ԃ�
    return s_sound.get();
}

// ---------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
// ---------------------------------------------------------
Sound::Sound()
    : m_system(nullptr),
    m_soundBGM(nullptr),
    m_channelBGM(nullptr),
    m_channelSE(nullptr),
    m_bgmList(),
    m_seList(),
    m_bgmVolume(DEFAULT_BGM_VOLUME),
    m_seVolume(DEFAULT_SE_VOLUME),
    m_fadeValue(FADE_VALUE)
{
    // FMOD�̃V�X�e����������
    InitializeFMOD();
}

// ---------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// ---------------------------------------------------------
Sound::~Sound()
{
    FinalizeFMOD();
}

// ---------------------------------------------------------
/// <summary>
/// �������֐��i�R���X�g���N�^�ŌĂ΂��j
    /// </summary>
/// <param name="filePath">���[�h����BGM�t�@�C���̃p�X</param>
// ---------------------------------------------------------
void Sound::InitializeFMOD()
{
    // �V�X�e�����C���X�^���X������
    FMOD_RESULT result = FMOD::System_Create(&m_system);
    assert(result == FMOD_OK);

    // �V�X�e��������������
    result = m_system->init(32, FMOD_INIT_NORMAL, nullptr);
    assert(result == FMOD_OK);

    // BGM���X�g�𐶐�����
    CreateBGMList();

    // SE���X�g�𐶐�����
    CreateSEList();
}

// ---------------------------------------------------------
/// <summary>
/// BGM���X�g�𐶐�����
/// </summary>
// ---------------------------------------------------------
void Sound::CreateBGMList()
{
    LoadBGM(BGM_TYPE::TITLE, TITLE_BGM_PATH);
    LoadBGM(BGM_TYPE::PLAY, PLAY_BGM_PATH);
    LoadBGM(BGM_TYPE::WIN, WIN_BGM_PATH);
    LoadBGM(BGM_TYPE::LOSE, LOSE_BGM_PATH);

    // �ŏ���BGM���Z�b�g����
    m_soundBGM = m_bgmList[static_cast<size_t>(BGM_TYPE::TITLE)];
}

// ---------------------------------------------------------
/// <summary>
/// SE���X�g�𐶐�����
/// </summary>
// ---------------------------------------------------------
void Sound::CreateSEList()
{
    LoadSE(SE_TYPE::SYSTEM_OK, SYSTEM_OK_PATH);
    LoadSE(SE_TYPE::PLAYER_ATTACK, PLAYER_ATTACK_SE_PATH);
    LoadSE(SE_TYPE::PLAYER_ATTACK2, PLAYER_ATTACK2_SE_PATH);
    LoadSE(SE_TYPE::PLAYER_DAMAGED, PLAYER_DAMAGED_SE_PATH);
    LoadSE(SE_TYPE::BOSS_MOVE, ENEMY_MOVE_SE_PATH);
    LoadSE(SE_TYPE::BOSS_ATTACK, ENEMY_ATTACK_SE_PATH);
    LoadSE(SE_TYPE::BOSS_SWEEP, ENEMY_SWEEP_SE_PATH);
}

// ---------------------------------------------------------
/// <summary>
/// BGM�t�@�C����ǂݍ���
/// </summary>
/// <param name="type">BGM�^�C�v</param>
/// <param name="filePath">BGM�t�@�C���̃p�X</param>
// ---------------------------------------------------------
void Sound::LoadBGM(BGM_TYPE type, const char* filePath)
{
    FMOD::Sound* sound;
    FMOD_RESULT result;

    // ���̃T�E���h���`������
    result = m_system->createSound(filePath, FMOD_LOOP_NORMAL, nullptr, &sound);
    assert(result == FMOD_OK);

    // BGM���X�g�ɒǉ�
    if (m_bgmList.size() != static_cast<size_t>(type))
        assert(!"BGM������ꏊ��enum�������܂���B");

    m_bgmList.push_back(sound);
}

// ---------------------------------------------------------
/// <summary>
/// SE�t�@�C����ǂݍ���
/// </summary>
/// <param name="type">SE�^�C�v</param>
/// <param name="filePath">SE�t�@�C���̃p�X</param>
// ---------------------------------------------------------
void Sound::LoadSE(SE_TYPE type, const char* filePath)
{
    FMOD::Sound* sound;
    FMOD_RESULT result;

    // ���̃T�E���h���`������
    result = m_system->createSound(filePath, FMOD_DEFAULT, nullptr, &sound);
    assert(result == FMOD_OK);

    // SE���X�g�ɒǉ�
    if (m_seList.size() != static_cast<size_t>(type))
        assert(!"SE������ꏊ��enum�������܂���B");

    m_seList.push_back(sound);
}

// ---------------------------------------------------------
/// <summary>
/// Sound�Đ��̍X�V����
/// </summary>
// ---------------------------------------------------------
void Sound::Update()
{
    FMOD_RESULT result;

    // �t�F�[�h�̒l���擾
    s_sound->m_fadeValue = GameData::GetInstance()->GetFadeValue();

    // ��d�Đ����Ȃ�
    if (s_sound->m_channelBGM == nullptr)
    {
        result = s_sound->m_system->playSound(s_sound->m_soundBGM, nullptr, false, &s_sound->m_channelBGM);
        assert(result == FMOD_OK && "BGM �Đ����s");
    }

    s_sound->SetBGMVolume(s_sound->m_fadeValue);

    // FMOD�̃V�X�e�����X�V
    result = s_sound->m_system->update();
    assert(result == FMOD_OK);
}

// ---------------------------------------------------------
/// <summary>
/// �I������
/// </summary>
// ---------------------------------------------------------
void Sound::FinalizeFMOD()
{
    // Sound�p�̃I�u�W�F�N�g���������
    m_soundBGM->release();
    m_system->release();
}

// ---------------------------------------------------------
/// <summary>
/// BGM�̉��ʒ���
/// </summary>
/// <param name="volume">���ʁi0�`1�j</param>
// ---------------------------------------------------------
void Sound::SetBGMVolume(float volume)
{
    if (m_channelBGM != nullptr)
    {
        m_channelBGM->setVolume(volume);
    }
}

// ---------------------------------------------------------
/// <summary>
/// SE�̉��ʒ���
/// </summary>
/// <param name="volume">���ʁi0�`1�j</param>
// ---------------------------------------------------------
void Sound::SetSEVolume(float volume)
{
    if (m_channelSE != nullptr)
    {
        m_channelSE->setVolume(volume);
    }
}

// ---------------------------------------------------------
/// <summary>
/// BGM��ύX����
/// </summary>
/// <param name="type">�ύX����BGM�^�C�v</param>
// ---------------------------------------------------------
void Sound::ChangeBGM(Sound::BGM_TYPE type)
{
    // ���łɍĐ�����BGM���~����
    if (s_sound->m_channelBGM != nullptr)
    {
        s_sound->m_channelBGM->stop();
    }

    // BGM��ύX����
    s_sound->m_soundBGM = s_sound->m_bgmList[static_cast<size_t>(type)];

    // �V����BGM���Đ�����
    FMOD_RESULT result = s_sound->m_system->playSound(s_sound->m_soundBGM, nullptr, false, &s_sound->m_channelBGM);
    if (result != FMOD_OK)
    {
        std::string errorMsg = "BGM�Đ��Ɏ��s���܂����B\nBGM_TYPE: " + std::to_string(static_cast<int>(type));
        MessageBoxA(nullptr, errorMsg.c_str(), "�G���[", MB_OK | MB_ICONERROR);
        return;
    }

    // ���ʒ������s��
    s_sound->SetBGMVolume(1.0f);
}

// ---------------------------------------------------------
/// <summary>
/// SE���Đ�����
/// </summary>
/// <param name="type">�Đ�����SE�̎��</param>
// ---------------------------------------------------------
void Sound::PlaySE(Sound::SE_TYPE type)
{
    // �Đ�����SE���擾
    FMOD::Sound* seSound = s_sound->m_seList[static_cast<size_t>(type)];

    // SE���Đ�
    FMOD_RESULT result = s_sound->m_system->playSound(seSound, nullptr, false, &s_sound->m_channelSE);
    if (result != FMOD_OK)
    {
        std::string errorMsg = "SE�Đ��Ɏ��s���܂����B\nBGM_TYPE: " + std::to_string(static_cast<int>(type));
        MessageBoxA(nullptr, errorMsg.c_str(), "�G���[", MB_OK | MB_ICONERROR);
        return;
    }

    // ���ʒ������s��
    s_sound->SetSEVolume(1.0f);
}
