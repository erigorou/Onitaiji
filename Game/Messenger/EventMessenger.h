// ----------------------------------------------------------
// ���O;	EventMessenger.h
// ���e:	�C�x���g���b�Z���W���[�N���X
//			�I�u�W�F�N�g���Ƃ̕ێ琫�����߂邽��
//			�I�u�U�[�o�[�V�X�e�����̗p
// �쐬:	�r�c����
// ----------------------------------------------------------
#pragma once
#ifndef EVENT_MESSENGER_H
#define EVENT_MESSENGER_H

// �C���N���[�h
#include "pch.h"
#include <unordered_map>
#include <functional>
#include "EventList.h"

/// <summary>
/// �C�x���g���b�Z���W���[�N���X
/// </summary>
class EventMessenger
{
	// ------------------
	// �����o�֐�
	// ------------------
public:
	// �C�x���g��o�^����
	static void Attach(const EventList event, std::function<void(void*)> function);
	// �Q�b�^�[��o�^
	static void AttachGetter(const GetterList event, std::function<void*()> function);
	// �C�x���g�����s����
	static void Execute(const EventList event, void* args);
	// �Q�b�^�[�����s����
	static void* ExecuteGetter(const GetterList event);
	// �C�x���g���폜����
	static void Detach(const EventList event);
	// �C�x���g���X�g���N���A����
	static void ClearEventList();

	// ------------------
	// �����o�ϐ�
	// ------------------
private:
	// �o�^���ꂽ�C�x���g��ۑ�����ϐ�
	static std::unordered_map<EventList, std::function<void(void*)>> s_eventList;
	static std::unordered_map<GetterList, std::function<void*()>> s_getterList;
};

#endif // !MESSENGER_H
