// -------------------------------------------------------
// ���O:	CollisionManager
// ���e:	�Փ˔�����Ǘ�����N���X
//			�I�u�W�F�N�g��Collision��������
//			���̃N���X�ɓo�^����A
//			�����蔻��̍X�V���s��
// �쐬:	�r�c����
// -------------------------------------------------------

// �C���N���[�h
#include "pch.h"
#include "CollisionManager.h"
#include "Interface/IObject.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Game/Messenger/EventMessenger.h"
#include "Libraries/Mylib/DebugDraw.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
	: m_basicEffect(nullptr)
	, m_inputLayout(nullptr)
	, m_primitiveBatch(nullptr)
	, m_obbs()
	, m_spheres()
	, m_drawFlag(false)
{
	// �����Ɠ����ɏ��������s��
	Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
CollisionManager::~CollisionManager()
{
	Clear();
}

/// <summary>
/// ����������
/// </summary>
void CollisionManager::Initialize()
{
	CommonResources* resources = CommonResources::GetInstance();

	auto device = resources->GetDeviceResources()->GetD3DDevice();
	auto context = resources->GetDeviceResources()->GetD3DDeviceContext();

	// �x�[�V�b�N�G�t�F�N�g���쐬����
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(device);
	m_basicEffect->SetVertexColorEnabled(true);

	// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		DirectX::CreateInputLayoutFromEffect<DirectX::VertexPositionColor>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf())
	);

	// �v���~�e�B�u�o�b�`�𐶐�
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(context);

	// �L�[�{�[�h���쐬����
	m_keyboardState = DirectX::Keyboard::Get().GetState();

	// �C�x���g�̓o�^
	AddEventMessenger();
}

/// <summary>
/// �C�x���g�̓o�^
/// </summary>
void CollisionManager::AddEventMessenger()
{
	// OBB�̓o�^�C�x���g
	EventMessenger::Attach(EventList::AddOBBCollision, std::bind(&CollisionManager::AddCollision<DirectX::BoundingOrientedBox>, this, std::placeholders::_1));
	// Sphere�̓o�^�C�x���g
	EventMessenger::Attach(EventList::AddSphereCollision, std::bind(&CollisionManager::AddCollision<DirectX::BoundingSphere>, this, std::placeholders::_1));
	// �Փ˔���̍폜�C�x���g
	EventMessenger::Attach(EventList::DeleteCollision, std::bind(&CollisionManager::DeleteCollision, this, std::placeholders::_1));
}

/// <summary>
/// ���Ƌ��̓����蔻��
/// </summary>
inline void CollisionManager::CheckCollisionSphereToSphere()
{
	// �����m�ɂ�铖���蔻��(���������m�ŏՓ˂��Ȃ��悤��)
	for (int i = 0; i < static_cast<int>(m_spheres.size() - 1); i++)
	{
		for (int j = i + 1; j < static_cast<int>(m_spheres.size()); j++)
		{
			// �����m�̓����蔻��
			if (m_spheres[i].collision->Intersects(*m_spheres[j].collision))
			{
				// �S�u�������m�ƏՓ˂��Ă���ꍇ�͏������s��Ȃ�
				if (IsGoblinCollision(m_spheres[i], m_spheres[j])) continue;

				// �Փ˂����Ƃ��ɑ���ɓn���f�[�^���쐬
				InterSectData sphereData1 = { m_spheres[i].objType, m_spheres[i].colType, m_spheres[i].collision };
				InterSectData sphereData2 = { m_spheres[j].objType, m_spheres[j].colType, m_spheres[j].collision };

				// �Փ˂����Ƃ��̏������Ăяo��
				m_spheres[i].object->HitAction(sphereData2);
				m_spheres[j].object->HitAction(sphereData1);
			}
		}
	}
}

/// <summary>
/// OBB�Ƌ��̓����蔻��
/// </summary>
inline void CollisionManager::CheckCollisionOBBToSphere()
{	
	// OBB�̃v���L�V�Ƌ��̓����蔻��
	for (int i = 0; i < static_cast<int>(m_obbs.size()); i++)
	{
		// OBB�̃v���L�V���̒��S��OBB�̒��S�ɐݒ�
		m_obbProxies[i] = CreateProxySphere(m_obbs[i].collision);

		for (int j = 0; j < static_cast<int>(m_spheres.size()); j++)
		{
			// �v���L�V�ƏՓ˂��Ă��Ȃ���Ύ��̋��Ɉڂ�
			if (!m_obbProxies[i]->Intersects(*m_spheres[j].collision))	continue;

			// OBB�Ƌ��̓����蔻��
			if (m_obbs[i].collision->Intersects(*m_spheres[j].collision))
			{
				// �Փ˂����Ƃ��ɑ���ɓn���f�[�^���쐬
				InterSectData obbData = { m_obbs[i].objType, m_obbs[i].colType,	m_obbProxies[i].get() };
				InterSectData sphereData = { m_spheres[j].objType, m_spheres[i].colType, m_spheres[j].collision };

				// �Փ˂����Ƃ��̏������Ăяo��
				m_obbs[i].object->HitAction(sphereData);
				m_spheres[j].object->HitAction(obbData);
			}
		}
	}
}

/// <summary>
/// �S�u�������m�ƏՓ˂��Ă��邩�����m
/// </summary>
/// <param name="collisionA">�Փ˔���A</param>
/// <param name="collisionB">�Փ˔���B</param>
/// <returns>�S�u�������m�Ɠ������Ă��邩</returns>
bool CollisionManager::IsGoblinCollision(
	CollisionData<DirectX::BoundingSphere> collisionA,
	CollisionData<DirectX::BoundingSphere> collisionB
)
{
	// �S�u�������m�ƏՓ˂��s���Ă��邩
	if (collisionA.objType == ObjectType::Goblin && collisionB.objType == ObjectType::Goblin)
	{
		// �Փ˂����Ƃ��ɑ���ɓn���f�[�^���쐬
		InterSectData goblinData = { collisionA.objType, collisionA.colType, collisionA.collision };
		// �Փ˂����Ƃ��̏������Ăяo��
		collisionB.object->HitAction(goblinData);
		return true;
	}

	return false;
}


/// <summary>
/// �X�V����
/// �����ŏՓ˂̌��m���s��
/// </summary>
void CollisionManager::Update()
{
	// OBB�Ƌ��̓����蔻��
	CheckCollisionOBBToSphere();
	// ���Ƌ��̓����蔻��
	CheckCollisionSphereToSphere();

#ifdef _DEBUG
	// �L�[�{�[�h�̏�Ԃ��擾����
	m_keyboardState = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�X�e�[�g�g���b�J�[���X�V����
	m_keyboardStateTracker.Update(m_keyboardState);

	// F5�L�[�������ꂽ��A�`��t���O��؂�ւ���
	if (m_keyboardStateTracker.IsKeyPressed(DirectX::Keyboard::F5))
	{
		m_drawFlag = !m_drawFlag;
	}
#endif // !_DEBUG
}

/// <summary>
/// �`�揈��
/// �f�o�b�O���̓����蔻��̕`����s��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
void CollisionManager::Render
(
	const DirectX::SimpleMath::Matrix& view,
	const DirectX::SimpleMath::Matrix& projection
)
{
	if (!m_drawFlag) return;

	// �Փ˔���̕`��
	DrawCollision(view, projection);
}

/// <summary>
/// �o�^���ꂽ�����N���A����
/// </summary>
void CollisionManager::Clear()
{
	m_obbs.clear();
	m_spheres.clear();
}


/// <summary>
/// �Փ˔����o�^����
/// </summary>
/// <typeparam name="T">�Փ˔���̌`��@���F�L�����E�{�b�N�X</typeparam>
/// <param name="args">CollisionData�^</param>
template<typename T>
void CollisionManager::AddCollision(void* args)
{
	// ���������҂���^�ɃL���X�g
	auto* collisionData = static_cast<CollisionData<T>*>(args);

	if (!collisionData) return; // �s���Ȉ����̏ꍇ�͏I��

	// �Փ˔���f�[�^��Ή�����R���e�i�ɒǉ�
	if constexpr (std::is_same_v<T, DirectX::BoundingOrientedBox>)
	{
		// OBB��ۑ�
		m_obbs.push_back(*collisionData);
		// OBB�̃v���L�V���𐶐�
		m_obbProxies.push_back(CreateProxySphere(static_cast<const DirectX::BoundingOrientedBox*>(collisionData->collision)));
	}
	else if constexpr (std::is_same_v<T, DirectX::BoundingSphere>)
	{
		// Sphere��ۑ�
		m_spheres.push_back(*collisionData);
	}
}

/// <summary>
/// �L�����E�{�b�N�X�̏������y�����邽�߂̃v���L�V�����쐬
/// </summary>
/// <param name="collision">�L�����E�{�b�N�X</param>
/// <returns>�v���L�V��</returns>
inline std::unique_ptr<DirectX::BoundingSphere> CollisionManager::CreateProxySphere(const DirectX::BoundingOrientedBox* collision)
{
	// BoundingSphere��OBB�̒��S�ƍő唼�a�ō쐬
	float radius = sqrtf(
		collision->Extents.x * collision->Extents.x +
		collision->Extents.y * collision->Extents.y +
		collision->Extents.z * collision->Extents.z
	);

	std::unique_ptr<DirectX::BoundingSphere> proxy = std::make_unique<DirectX::BoundingSphere>(collision->Center, radius);

	return std::move(proxy);
}

/// <summary>
/// �o�^���ꂽ�Փ˔������������
/// </summary>
/// <param name="args">DeleteCollisionData�^</param>
void CollisionManager::DeleteCollision(void* args)
{
	// args��DeleteCollisionData�\���̂ւ̃|�C���^
	auto* deleteData = static_cast<DeleteCollisionData*>(args);

	// �s���Ȉ����̏ꍇ�͏I��
	if (!deleteData) return;

	// OBB�̏ꍇ��OBB�ƃv���L�V���̗������폜
	if (deleteData->collType == CollisionType::OBB)
	{
		// �Ή�����I�u�W�F�N�g���폜���郉���_��
		auto EraseMatchingObject = [object = deleteData->object](auto& container)
			{
				container.erase(std::remove_if(container.begin(), container.end(), [object](const auto& collision)
					{
						return collision.object == object;	// �I�u�W�F�N�g����v���邩����
					}),
					container.end());
			};

		// OBB�̃R���e�i����폜
		EraseMatchingObject(m_obbs);
	}

	// Sphere�̏ꍇ��Sphere�̂ݍ폜
	else if (deleteData->collType == CollisionType::Sphere)
	{
		// �Ή�����I�u�W�F�N�g���폜���郉���_��
		auto EraseMatchingObject = [object = deleteData->object](auto& container)
			{
				container.erase(std::remove_if(container.begin(), container.end(), [object](const auto& collision)
					{
						return collision.object == object;
					}),
					container.end());
			};

		// Sphere�̃R���e�i����폜
		EraseMatchingObject(m_spheres);
	}
}

/// <summary>
/// �Փ˔���̕`����s��
/// �f�o�b�O���̂ݗL��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�v���W�F�N�V�����s��</param>
inline void CollisionManager::DrawCollision(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = CommonResources::GetInstance()->GetCommonStates();

	// �`��ݒ���s��
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(states->DepthDefault(), 0);
	context->RSSetState(states->CullNone());
	context->IASetInputLayout(m_inputLayout.Get());
	// �r���[�s��Ǝˉe�s���ݒ�
	m_basicEffect->SetView(view);
	m_basicEffect->SetProjection(projection);
	m_basicEffect->Apply(context);
	// �`��J�n
	m_primitiveBatch->Begin();

	// Collision���ɔ����`��

	// OBB�̕`��
	for (const auto& obb : m_obbs){
		DX::Draw(m_primitiveBatch.get(), *obb.collision, DirectX::Colors::Red);
	}

	// Sphere�̕`��
	for (const auto& sphere : m_spheres){
		DX::Draw(m_primitiveBatch.get(), *sphere.collision, DirectX::Colors::Blue);
	}

	// OBB�̃v���L�V���̕`��
	for (auto& sphere : m_obbProxies){
		DX::Draw(m_primitiveBatch.get(), *sphere, DirectX::Colors::LimeGreen);
	}
	// �`��I��
	m_primitiveBatch->End();
}