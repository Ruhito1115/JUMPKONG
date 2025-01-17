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
		// シーンの切り替わり先を戻り値として返す
		// 切り替わらない場合は現在のシーンを返す
	SceneManager::SceneKind Update();

	void Draw();

private:
	// "ボタンを押してください"を点滅させるためのフレームカウント
	int m_blinkFrameCount;
};
