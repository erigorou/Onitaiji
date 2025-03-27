// -------------------------------------- //
//
// �G�̊獷�� : �ҋ@
//
// -------------------------------------- //

#include "pch.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/GameResources.h"
#include "../../Boss.h"
#include "../Header/BossFaceIdling.h"

// --------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="Boss">�{�X�̃|�C���^</param>
// --------------------------------------------------------
BossFaceIdling::BossFaceIdling(Boss* Boss)
	: m_Boss(Boss)
{
	// ���f���擾
	m_model = GameResources::GetInstance()->GetModel("bossIdlingFace");
}

// --------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------------------------------
BossFaceIdling::~BossFaceIdling()
{
}

// --------------------------------------------------------
/// <summary>
/// �`�揈��
/// </summary>
/// <param name="mat">���[���h�s��</param>
/// <param name="view">�r���[�s��</param>
/// <param name="proj">�v���W�F�N�V�����s��</param>
// --------------------------------------------------------
void BossFaceIdling::DrawFace(
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