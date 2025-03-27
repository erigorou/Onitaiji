// ----------------------------------------------------------
// ���O;	KeyboardMessenger.cpp
// ���e:	�L�[�{�[�h�̓��͂��Ď����A�ʒm����N���X
//			�I�u�U�[�o�[�p�^�[�����̗p
// �쐬:	�r�c����
// ----------------------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "KeyboardMessenger.h"

// �L�[�{�[�h�ώ@�҃��X�g������������
std::vector<std::tuple<DirectX::Keyboard::Keys, IObserver*, KeyboardMessenger::KeyPressType>> KeyboardMessenger::s_observerList;
// �L�[�͈̓��X�g(�L�[�A�J�n�C���f�b�N�X�ƏI���C���f�b�N�X)
std::unordered_map<DirectX::Keyboard::Keys, std::vector<std::pair<int, int>>> KeyboardMessenger::s_keysRangeList;

// -------------------------------------------------------
/// <summary>
///	�g�p����L�[��o�^����
/// </summary>
/// <param name="key">�g�p����L�[</param>
/// <param name="observer">�ʒm����Ώ�</param>
/// <param name="type">�ǂ̂悤�ɉ����ꂽ��</param>
// -------------------------------------------------------
void KeyboardMessenger::Attach(const DirectX::Keyboard::Keys& key, IObserver* observer, const KeyPressType type)
{
	// �ώ@�҃��X�g�Ɋώ@�҂�ǉ�����
	s_observerList.emplace_back(key, observer, type);
}

// -------------------------------------------------------
/// <summary>
/// �o�^���ꂽ������������
/// </summary>
/// <param name="key">��������L�[</param>
/// <param name="observer">�ʒm���Ă����Ώ�</param>
/// <param name="type">�ǂ̂悤�ɉ�����Ă�����</param>
// -------------------------------------------------------
void KeyboardMessenger::Detach(const DirectX::Keyboard::Keys& key, IObserver* observer, const KeyPressType type)
{
	// �ώ@�҃��X�g����ώ@�҂���������
	s_observerList.erase(
		std::remove_if(s_observerList.begin(), s_observerList.end(),
			[key, observer, type](const std::tuple<DirectX::Keyboard::Keys, IObserver*, KeyPressType>& entry)
			{
				// �^�v������v�f�����o��
				auto entryKey = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(entry);
				auto entryObserver = std::get<static_cast<int>(ArrayContentType::P_OBSERVER)>(entry);
				auto entryType = std::get<static_cast<int>(ArrayContentType::TYPE)>(entry);

				// �L�[�Ɗώ@�҂���v���邩�ǂ����m�F
				return entryKey == key && entryObserver == observer && entryType == type;
			}),
		s_observerList.end());
}

// -------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̏�Ԃ�ʒm����
/// </summary>
/// <param name="keyboardTracker">�L�[�{�[�h�g���b�J�[</param>
// -------------------------------------------------------
void KeyboardMessenger::Notify(const DirectX::Keyboard::KeyboardStateTracker& keyboardTracker)
{
	auto keyboardState = keyboardTracker.GetLastState();

	// �ώ@�҃��X�g����ώ@�҂����o��
	for (const auto& keyRange : s_keysRangeList)
	{
		// �ώ@�҂��������ׂ��L�[���ǂ����𒲂ׂ�
		if (keyboardTracker.IsKeyPressed(keyRange.first))
		{
			// �L�[�̊J�n�C���f�b�N�X����I���C���f�b�N�X�܂ł̃C���f�b�N�X�����o��
			for (const auto& range : keyRange.second)
			{
				for (int i = range.first; i <= range.second; ++i)
				{
					// �I�u�U�[�o�[�̒ʒm�֐��ɉ���������ꂽ�L�[��ʒm����
					auto& observer = std::get<static_cast<int>(ArrayContentType::P_OBSERVER)>(s_observerList[i]);
					auto& keyboard = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(s_observerList[i]);

					observer->OnKeyPressed(keyboard);
				}
			}
		}
	}
}

// -------------------------------------------------------
/// <summary>
/// �L�[�{�[�h�̏�Ԃ�ʒm����
/// </summary>
/// <param name="keyboardState">�L�[�{�[�h�X�e�[�g</param>
// -------------------------------------------------------
void KeyboardMessenger::Notify(const DirectX::Keyboard::State& keyboardState)
{
	// �ώ@�҃��X�g����ώ@�҂����o��
	for (const auto& keyRange : s_keysRangeList)
	{
		// �ώ@�҂��������ׂ��L�[���ǂ����𒲂ׂ�
		if (keyboardState.IsKeyDown(keyRange.first))
		{
			// �L�[�̊J�n�C���f�b�N�X����I���C���f�b�N�X�܂ł̃C���f�b�N�X�����o��
			for (const auto& range : keyRange.second)
			{
				for (int i = range.first; i <= range.second; ++i)
				{
					// �I�u�U�[�o�[�̒ʒm�֐��ɉ���������ꂽ�L�[��ʒm����
					auto& observer = std::get<static_cast<int>(ArrayContentType::P_OBSERVER)>(s_observerList[i]);
					auto& keyboard = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(s_observerList[i]);

					observer->OnKeyDown(keyboard);
				}
			}
		}
	}
}

// -------------------------------------------------------
/// <summary>
/// �ώ@�҃��X�g���\�[�g����(�����y�ʉ�)
/// </summary>
// -------------------------------------------------------
void KeyboardMessenger::SortObserverList()
{
	// �ώ@�҃��X�g���L�[�iDirectX::Keyboard::Keys�j�Ń\�[�g����
	std::sort(
		s_observerList.begin(),
		s_observerList.end(),
		[](const auto& a, const auto& b)
		{
			// �^�v������L�[�����o��
			const auto& keyA = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(a);
			const auto& keyB = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(b);

			// �L�[�Ń\�[�g����
			return keyA < keyB;
		});
}

// -------------------------------------------------------
/// <summary>
/// �L�[�͈̓��X�g�𐶐�����(�����y�ʉ�)
/// </summary>
// -------------------------------------------------------
void KeyboardMessenger::CreateKeyRangeList()
{
	// �L�[�͈͂��N���A����
	if (!s_keysRangeList.empty()) s_keysRangeList.clear();

	// �ώ@�҃��X�g����Ȃ珈�����I������
	if (s_observerList.empty()) return;

	// �J�n�C���f�b�N�X��ݒ肷��
	int startIndex = 0;
	DirectX::Keyboard::Keys currentKey = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(s_observerList[0]);

	// �ώ@�҃��X�g�����[�v���A�L�[�͈͂��쐬����
	for (int index = 1; index < s_observerList.size(); ++index)
	{
		auto key = std::get<static_cast<int>(ArrayContentType::KEYBOARD)>(s_observerList[index]);

		// ���݂̃L�[�ƈقȂ�ꍇ�A�V�����͈͂�ǉ�����
		if (key != currentKey)
		{
			// �L�[�͈͂̏I���C���f�b�N�X�� (index - 1) �ɂ���
			s_keysRangeList[currentKey].push_back(std::make_pair(startIndex, index - 1));
			// ���̃L�[�͈͂̊J�n�C���f�b�N�X���X�V����
			startIndex = index;
			currentKey = key;
		}
	}

	// �Ō�̃L�[�͈͂�ǉ�����
	s_keysRangeList[currentKey].push_back(std::make_pair(startIndex, static_cast<int>(s_observerList.size() - 1)));
}

// -------------------------------------------------------
/// <summary>
/// �ώ@�҂ƃL�[�͈̓��X�g�N���A����
/// </summary>
// -------------------------------------------------------
void KeyboardMessenger::Clear()
{
	// �ώ@�҃��X�g���N���A����
	s_observerList.clear();
	// �L�[�͈̓��X�g���N���A����
	s_keysRangeList.clear();
}