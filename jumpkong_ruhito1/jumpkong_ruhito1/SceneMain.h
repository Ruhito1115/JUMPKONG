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
	// グラフィックハンドル
	int m_lifeHandle;

	// フォントハンドル
	int m_fontHandle;

	// カウントダウンに使用するフレーム
	int m_countFrame;

	// 死亡に使用するフレーム
	int m_gameoverFrameCount;

	// 死んだになった後、1ボタンを押した
	bool m_isGameEnd;

	// フェード処理
	int m_fadeFrameCount;

	Map m_map;
	Player m_player;
	Enemy m_enemy;
	Life m_life[3]; // m_life[0],m_life[1],m_life[2]
};
