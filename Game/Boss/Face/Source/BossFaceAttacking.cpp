// ---------------------------------------------
// ���O:	BossFaceAttacking.cpp
// ���e:	�{�X�̍U�����̊�N���X
// �쐬:	�r�c����
// ---------------------------------------------
// �C���N���[�h
#include "pch.h"
#include "Game/CommonResources.h"
#include "Game/GameResources.h"
#include "DeviceResources.h"
#include "../../Boss.h"
#include "../Header/BossFaceAttacking.h"

// --------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="Boss">�{�X�̃|�C���^</param>
// --------------------------------------------------------
BossFaceAttacking::BossFaceAttacking(Boss* Boss)
	: m_Boss(Boss)
{
	// ���f���擾
	m_model = GameResources::GetInstance()->GetModel("bossAttackingFace");
}

// --------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------------------------------
BossFaceAttacking::~BossFaceAttacking()
{
}

// --------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
/// ]]param name="mat">���[���h�s��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�v���W�F�N�V�����s��</param>
// --------------------------------------------------------
void BossFaceAttacking::DrawFace(
	const DirectX::SimpleMath::Matrix mat,
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& proj
)
{
	// ���\�[�X�̎擾
	CommonResources* resources = CommonResources::GetInstance();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();

	// ���f���̕`��
	m_model->Draw(context, *resources->GetCommonStates(), mat, view, proj);
}