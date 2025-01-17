#include "GameOverScene.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"

namespace
{
	// 文字の点滅
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// 文字の表示位置
	constexpr int kTitleY = 200;
	constexpr int kButtonTextY = 280;
}

GameOverScene::GameOverScene() :
	m_blinkFrameCount(0)
{
}

GameOverScene::~GameOverScene()
{
}

SceneManager::SceneKind GameOverScene::Update()
{
	// 1秒サイクルで表示、非表示を切り替える
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// 1ボタンを押したらMainに移行する
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind::kSceneTitle;
	}

	// 何もしなければシーンは遷移しない(タイトル画面のまま)
	return SceneManager::kGameOverScene;

	if (m_isGameEnd)
	{
		// test ゲームオーバーになったらフェードアウトさせる
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::kSceneTitle;
		}
	}
	else
	{
		// フェードイン処理
		m_fadeFrameCount++;
		if (m_fadeFrameCount > 30)
		{
			m_fadeFrameCount = 30;
		}
	}
}

void GameOverScene::Draw()
{
	// タイトル表示
	int width = GetDrawStringWidth("GameOver", strlen("GameOver"));
	DrawString(Game::kScreenWidth / 2 - width / 2, kTitleY, "GameOver", GetColor(255, 255, 255));

	// 1ボタンを押してください
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		width = GetDrawStringWidth("ボタンを押してください", strlen("1ボタンを押してください"));
		DrawString(Game::kScreenWidth / 2 - width / 2, kButtonTextY, "1ボタンを押してください", GetColor(255, 255, 255));
	}
}

void GameOverScene::Init()
{
}

void GameOverScene::End()
{
}
