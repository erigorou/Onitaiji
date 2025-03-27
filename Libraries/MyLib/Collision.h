// ---------------------------------------------------------------------------------
//
// ���O:	Collision.cpp
// ���e:	�w�肳�ꂽ���f������L�����E�{�b�N�X�𐶐�
// ����:	�r�c����
//
// ---------------------------------------------------------------------------------
#pragma once
// �C���N���[�h
#include "pch.h"

/// <summary>
/// �Փ˔���N���X
/// </summary>
class Collision
{
	// -----------------------------
	// �����o�֐�(���J)
	// -----------------------------
public:
	// -------------------------------------------------------------------------
	/// <summary>
	/// �w�肳�ꂽ���f����������t�����E�{�b�N�X�iOBB�j���擾
	/// </summary>
	/// <param name="model">���E�{�b�N�X���擾����Ώۂ̃��f��</param>
	/// <returns>�傫�����l������OBB</returns>
	// -------------------------------------------------------------------------
	static DirectX::BoundingOrientedBox Get_BoundingOrientedBox_FromMODEL(DirectX::Model* model)
	{
		// ���f����null�̎��ɒ��f������
		assert(model != nullptr && "model is null.");

		DirectX::BoundingBox initialAABB;
		DirectX::BoundingOrientedBox initialOBB;

		// ���f�����狫�E�{�b�N�X���擾����
		for (auto it = model->meshes.cbegin(); it != model->meshes.cend(); it++)
		{
			if (it == model->meshes.cbegin())
			{
				// �ŏ��̃��b�V���̋��E�{�b�N�X��ݒ肷��
				initialAABB = (*it)->boundingBox;
			}
			else
			{
				// ����ȍ~�̃��b�V���̋��E�{�b�N�X���}�[�W����
				DirectX::BoundingBox::CreateMerged(initialAABB, initialAABB, (*it)->boundingBox);
			}
		}

		// AABB����OBB�𐶐�����
		DirectX::BoundingOrientedBox::CreateFromBoundingBox(initialOBB, initialAABB);

		// obb��Ԃ�
		return initialOBB;
	}
};
