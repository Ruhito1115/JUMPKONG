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

	// フォントハンドル
	int m_fontHandle;

	// ゲームオーバーになった後、1ボタンを押した
	bool m_isGameEnd;

	// フェード処理
	int m_fadeFrameCount;

private:
	// "ボタンを押してください"を点滅させるためのフレームカウント
	int m_blinkFrameCount;
};

