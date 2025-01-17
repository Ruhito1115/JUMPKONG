#pragma once
#include "SceneManager.h"

class GameOverScene
{
public:
	GameOverScene();
	~GameOverScene();

	SceneManager::SceneKind Update();

	void Draw();

	void Init();
	void End();

	// �t�H���g�n���h��
	int m_fontHandle;

	// �Q�[���I�[�o�[�ɂȂ�����A1�{�^����������
	bool m_isGameEnd;

	// �t�F�[�h����
	int m_fadeFrameCount;

private:
	// "�{�^���������Ă�������"��_�ł����邽�߂̃t���[���J�E���g
	int m_blinkFrameCount;
};

