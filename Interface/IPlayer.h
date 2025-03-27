#pragma once
#ifndef IPLAYER
#define IPLAYER

#include "pch.h"
#include "Interface/IState.h"

class IPlayer : public IState
{
public:
	// �f�X�g���N�^
	virtual ~IPlayer() = default;
	// ����������
	virtual void Initialize() = 0;
	// ���O�X�V����
	virtual void PreUpdate() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;

	// �L�[���͂��������u�ԂɌĂяo�����
	virtual void OnKeyPressed(const DirectX::Keyboard::Keys& key) = 0;
	// �L�[�����������Ă���Ăяo�����
	virtual void OnKeyDown(const DirectX::Keyboard::Keys& key) = 0;
	// ����X�V����
	virtual void PostUpdate() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};

#endif // !1
