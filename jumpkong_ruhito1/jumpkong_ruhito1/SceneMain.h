#pragma once
#include "SceneManager.h"

#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Life.h"

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void End();

	SceneManager::SceneKind Update();
	void Draw();

private:
	// �O���t�B�b�N�n���h��
	int m_lifeHandle;

	// �t�H���g�n���h��
	int m_fontHandle;

	// �J�E���g�_�E���Ɏg�p����t���[��
	int m_countFrame;

	// ���S�Ɏg�p����t���[��
	int m_gameoverFrameCount;

	// ���񂾂ɂȂ�����A1�{�^����������
	bool m_isGameEnd;

	// �t�F�[�h����
	int m_fadeFrameCount;

	Map m_map;
	Player m_player;
	Enemy m_enemy;
	Life m_life[3]; // m_life[0],m_life[1],m_life[2]
};
