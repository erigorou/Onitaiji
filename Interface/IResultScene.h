#pragma once

#ifndef I_RESULT_SCENE_DEFINED
#define I_RESULT_SCENE_DEFINED

class IResultScene
{
public:
	// �f�X�g���N�^
	virtual ~IResultScene() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(float elapsedTime) = 0;
	// �`�揈��
	virtual void Render() = 0;
};

#endif // I_SCENE_DEFINED