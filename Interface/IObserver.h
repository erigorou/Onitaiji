#pragma once
#ifndef OBSERVER
#define OBSERVER

#include "pch.h"

class IObserver
{
public:
	// �L�[����������ꂽ�玞�ɌĂяo�����
	virtual void OnKeyPressed(const DirectX::Keyboard::Keys& key) = 0;

	// �L�[�����������Ă���Ăяo�����
	virtual void OnKeyDown(const DirectX::Keyboard::Keys& key) = 0;
};

#endif // !OBSERVER
