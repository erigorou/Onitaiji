#pragma once

#include "pch.h"

class SkySphere
{
public:
	// �Œ�l
	static const float SKYSPHERE_SCALE;

public:
	// �R���X�g���N�^
	SkySphere();
	// �f�X�g���N�^
	~SkySphere();

	// �X�V����
	void Update();

	// ���f�����擾����
	void LoadSkySphereModel();

	// ���f���̕`��
	void DrawSkySphere(
		DirectX::SimpleMath::Matrix view,
		DirectX::SimpleMath::Matrix projection
	);

private:
	// SkyeSphere�̃��f��
	std::unique_ptr<DirectX::Model> m_skySphereModel;
};
