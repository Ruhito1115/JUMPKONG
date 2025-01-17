#include "SceneTitle.h"
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

SceneTitle::SceneTitle() :
	m_blinkFrameCount(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
}

void SceneTitle::End()
{
}

/*
void SceneTitle::Update()
{
	// 1秒サイクルで表示、非表示を切り替える
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}
}
*/

SceneManager::SceneKind SceneTitle::Update()
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
		return SceneManager::SceneKind::kSceneMain;
	}

	// 何もしなければシーンは遷移しない(タイトル画面のまま)
	return SceneManager::SceneKind();
}

void SceneTitle::Draw()
{
	// タイトル表示
	int width = GetDrawStringWidth("JUMPKONG", strlen("JUMPKONG"));
	DrawString(Game::kScreenWidth / 2 - width / 2, kTitleY, "JUMPKONG", GetColor(255, 255, 255));

	// 1ボタンを押してください
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		width = GetDrawStringWidth("ボタンを押してください", strlen("1ボタンを押してください"));
		DrawString(Game::kScreenWidth / 2 - width / 2, kButtonTextY, "1ボタンを押してください", GetColor(255, 255, 255));
	}
}
