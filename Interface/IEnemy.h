// ----------------------------------
// �u���e�v�G�̃C���^�[�t�F�[�X
// �u����v�S�u�����@�{�X
// �u���t�v12/18
// �u�쐬�ҁv�r�c
// ----------------------------------
#pragma once
#include "pch.h"
#include "IObject.h"
#include "Game/Data/HPSystem.h"

class IEnemy : public IObject
{
public:
	// �f�X�g���N�^
	virtual ~IEnemy() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�揈��
	virtual void Render(
		const DirectX::SimpleMath::Matrix& view,
		const DirectX::SimpleMath::Matrix& projection) = 0;
	// �I������
	virtual void Finalize() = 0;

	// ���������Ƃ���true��ݒ肷��
	virtual void HitAction(InterSectData data) = 0;
	// �ʒu���擾����
	virtual DirectX::SimpleMath::Vector3 GetPosition() = 0;

	// HPSystem��n��
	virtual HPSystem* GetHPSystem() = 0;

	// �q�b�g�̃t���O��ݒ肷��
	virtual void CanHit(bool flag) = 0;
};
