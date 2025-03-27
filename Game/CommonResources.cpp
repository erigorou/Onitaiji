/*
	@file	CommonResources.cpp
	@brief	�V�[���֓n���A�Q�[�����Ŏg�p���鋤�ʃ��\�[�X
*/
#include "pch.h"
#include "CommonResources.h"
#include <cassert>

std::unique_ptr<CommonResources> CommonResources::m_resources = nullptr;

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
CommonResources* const CommonResources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// CommonResources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new CommonResources());
	}
	// CommonResources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
CommonResources::CommonResources()
	:
	m_stepTimer{},
	m_deviceResources{},
	m_commonStates{},
	m_debugString{},
	m_inputManager{}
{
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void CommonResources::Initialize(
	DX::StepTimer* timer,
	DX::DeviceResources* dr,
	DirectX::CommonStates* commonStates,
	mylib::DebugString* debugString,
	mylib::InputManager* inputManager
)
{
	assert(timer);
	assert(dr);
	assert(commonStates);
	assert(debugString);
	assert(inputManager);

	m_stepTimer = timer;
	m_deviceResources = dr;
	m_commonStates = commonStates;
	m_debugString = debugString;
	m_inputManager = inputManager;
}