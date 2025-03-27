// -------------------------------------- //
//
// ����̋O�ՃG�t�F�N�g�̋������v�Z����N���X
//
// -------------------------------------- //
#include "pch.h"
#include "Effects/Header/SwordTrailParticle.h"


// --------------------------------------------------------
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="vertex">���_���</param>
/// <param name="life">��������</param>
/// <param name="startColor">�����J���[</param>
/// <param name="endColor">�I���J���[</param>
// --------------------------------------------------------
SwordTrailParticle::SwordTrailParticle(
	DirectX::VertexPositionTexture vertex[],
	float life,
	DirectX::SimpleMath::Color startColor, DirectX::SimpleMath::Color endColor
)
	:m_startLife(life)			// ��������
	, m_life(life)				// ���ݎ���
	, m_startColor(startColor)	// �ŏ��̐F
	, m_nowColor(startColor)		// ���݂̐F
	, m_endColor(endColor)		// �I���̐F
{
	// �z��̊e�v�f��������
	for (int i = 0; i < 4; i++)
	{
		m_vertices[i] = vertex[i];
	}
}

// --------------------------------------------------------
/// <summary>
/// �f�X�g���N�^
/// </summary>
// --------------------------------------------------------
SwordTrailParticle::~SwordTrailParticle()
{
}


// --------------------------------------------------------
/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�������Ă��邩</returns>
// --------------------------------------------------------
bool SwordTrailParticle::Update(float elapsedTime)
{
	using namespace DirectX;

	// �F�B���݂̐������Ԃ���A�F��Lerp�ŎZ�o����
	m_nowColor = SimpleMath::Color::Lerp(
		m_startColor,
		DirectX::SimpleMath::Color(m_endColor.R(), m_endColor.G(), m_endColor.B(), 0), // �����x��0�ɐݒ肵�ē����ɂ���
		1.0f - m_life / m_startLife);

	//	���C�t�����炵�Ă���
	m_life -= elapsedTime;
	//	���C�t��0�����Ȃ玩�g�������Ă��炤
	if (m_life < 0.0f)return false;

	return true;
}