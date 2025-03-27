#pragma once

// --------------------------------
/// <summary>
/// �C�x���g���X�g
/// </summary>
// --------------------------------
enum class EventList
{
	// �{�X���v���C���[�ɍU�����Ă��邩
	PlayerCanDamageBoss,
	// ���_���v���C���[�ɍU�����Ă��邩
	PlayerCanDamageCudgel,
	// �S�u�������v���C���[�ɍU�����Ă��邩
	PlayerCanDamageGoblin,
	// �G�ɍU�����ł��邩
	EnemyCanHit,
	// ���̃X�e�[�g��ύX����
	ChangeSwordState,
	// ���_�̃X�e�[�g��ύX����
	ChangeCudgelState,
	// �{�X�̃X�e�[�g��ύX����
	ChangeBossState,
	// �{�X�̊��ύX����
	ChangeBossFace,
	// �G���P�̍폜
	DeleteEnemy,
	// �S�u������S�ē|��
	DeleteAllGoblin,
	// OBB�Փ˔����o�^����
	AddOBBCollision,
	// ���Փ˔����o�^����
	AddSphereCollision,
	// �Փ˔���̓o�^����������
	DeleteCollision,
	// �ړ��p�[�e�B�N���̍쐬
	CreateTrailDust,
	// �y���p�[�e�B�N���̍쐬
	CreateBashDust,
	// ����̋O�Ճp�[�e�B�N���̍쐬
	CreateWeaponTrail,
	// �J������h�炷
	ShakeCamera,
	// �J�����̃X�e�[�g��ύX����
	ChangeCamera,
	// �v���C�V�[���I��
	EndPlayScene,
	// �X�N���[���V���b�g���B��
	TakeCapture
};

// --------------------------------
/// <summary>
/// �Q�b�^�[���X�g
/// </summary>
// --------------------------------
enum class GetterList
{
	// �v���C���[�̃|�C���^���擾����
	GetPlayer,
	// �{�X�̃|�C���^���擾����
	GetBoss,
	// ���̃|�C���^���擾����
	GetSword,
	// ���_�̃|�C���^���擾����
	GetCudgel,
	// �J�����̃^�[�Q�b�g�̍��W���擾����
	GetTargetPosition,
};