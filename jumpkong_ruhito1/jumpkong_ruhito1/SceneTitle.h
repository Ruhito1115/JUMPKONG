#pragma once
#include "SceneManager.h"

class SceneTitle
{
public:
	SceneTitle();
	~SceneTitle();

	void Init();
	void End();

	//	void Update();
		// �V�[���̐؂�ւ����߂�l�Ƃ��ĕԂ�
		// �؂�ւ��Ȃ��ꍇ�͌��݂̃V�[����Ԃ�
	SceneManager::SceneKind Update();

	void Draw();

private:
	// "�{�^���������Ă�������"��_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;
};
