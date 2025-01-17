#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include <cassert>

namespace
{
	// ゲームオーバーの文字が表示されるまでのフレーム数
	constexpr int kGameoverFadeFrame = 60;
}

SceneMain::SceneMain() :
	m_lifeHandle(-1),
	m_fontHandle(-1),
	m_countFrame(60 * 3 - 1),
	m_gameoverFrameCount(0),
	m_isGameEnd(false),
	m_fadeFrameCount(0),
	m_player(m_map)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// フォントの生成
	m_fontHandle = CreateFontToHandle("Broadway", 64, -1, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);

	m_lifeHandle = LoadGraph("data/image/life.png");
	assert(m_lifeHandle != -1);

	m_player.Init();
	m_map.Init(&m_player);
	m_enemy.Init();

	for (int i = 0; i < 3; i++)
	{
		m_life[i].Init();
		m_life[i].SetHandle(m_lifeHandle);
		m_life[i].SetIndex(i);
	}
}

void SceneMain::End()
{
	m_map.End();
	m_player.End();
	m_enemy.End();

	//	m_life.End();
	for (int i = 0; i < 3; i++)
	{
		m_life[i].End();
	}
	// グラフィックの削除
	DeleteGraph(m_lifeHandle);

	DeleteFontToHandle(m_fontHandle);
}

SceneManager::SceneKind SceneMain::Update()
{
	if (m_isGameEnd)
	{
		// test ゲームオーバーになったらフェードアウトさせる
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::kGameOverScene;
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

	m_countFrame--;

	m_map.Update();
	m_player.Update();

	//	m_life.Update();
	for (int i = 0; i < 3; i++)
	{
		m_life[i].Update();
	}

	// カウントダウン中はゲームが進行しない
	if (m_countFrame > 0)
	{
		return SceneManager::SceneKind::kSceneMain;
	}

	// ゲームオーバー演出
	if (m_player.GetHp() <= 0)
	{
		m_gameoverFrameCount++;
		if (m_gameoverFrameCount > kGameoverFadeFrame)
		{
			m_gameoverFrameCount = kGameoverFadeFrame;

			// ゲームオーバーのも火が表示され切った後に
			// 1ボタンを押したらタイトルに戻る
			if (Pad::IsTrigger(PAD_INPUT_1))
			{
				m_isGameEnd = true;
			}
		}
	}

	// 以降はカウントダウン終了後に実行する処理
	m_enemy.Update();

	// プレイヤーの当たり判定
	// 最初は一旦当たっている状態、ということにする
	bool isCol = true;

	// 絶対に当たらないパターンの場合は
	// bool isCol = false として当たっていない状態にする
	if (m_player.GetLeft() > m_enemy.GetRight())
	{
		// 敵が完全にプレイヤーの左にいるので当たっていない
		isCol = false;
	}

	if (m_player.GetTop() > m_enemy.GetBottom())
	{
		// 敵が完全にプレイヤーの上にいるので当たっていない
		isCol = false;
	}

	if (m_player.GetRight() < m_enemy.GetLeft())
	{
		// 敵が完全にプレイヤーの右にいるので当たっていない
		isCol = false;
	}

	if (m_player.GetBottom() < m_enemy.GetTop())
	{
		// 敵が完全にプレイヤーの下にいるので当たっていない
		isCol = false;
	}

	// ここに到達したとき,
	// isCol = true なら当たっている　falseなら当たっていない
	if (isCol)
	{
		//printfDx("当たった\n");
		m_player.OnDamage();
	}

	// 何もしなければ遷移しない
	return SceneManager::SceneKind::kSceneMain;
}

void SceneMain::Draw()
{
	m_map.Draw();
	m_player.Draw();
	m_enemy.Draw();

	//	m_life.Draw();
	for (int i = 0; i < m_player.GetHp(); i++)
	{
		m_life[i].Draw();
	}

	// カウントダウンの表示
	if (m_countFrame > 0)
	{
		int width = GetDrawFormatStringWidthToHandle(m_fontHandle, "%d", m_countFrame / 60 + 1);
		DrawFormatStringToHandle(Game::kScreenWidth / 2 - width / 2, Game::kScreenHeight / 2 - 64 / 2,
			GetColor(255, 0, 0), m_fontHandle, "%d", m_countFrame / 60 + 1);
	}

	// ゲームオーバーの表示
	if (m_player.GetHp() <= 0)
	{
		// 0~60の間で変化するm_gameoverFrameCountを
		// 0~255の値に変換する必要がある

		// 割合を使用して変換を行う
		// m_gameoverFrameCountを進行割合に変換する
		float progressRate = static_cast<float>(m_gameoverFrameCount) / kGameoverFadeFrame;
		//	printfDx("%f %%\n", progressRate);

			// 割合を実際の透明度に変換する
		int alpha = static_cast<int>(255 * progressRate);

		// ここ以降呼ばれるDraw関数の描画方法を変更する
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		int width = GetDrawStringWidthToHandle("GAME OVER", strlen("GAME OVER"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, Game::kScreenHeight / 2 - 64 / 2,
			"GAME OVER", GetColor(255, 0, 0), m_fontHandle);

		// 以降の表示がおかしくならないように元の設定に戻しておく
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// フェード処理
	int fadeAlpha = 0; // 0~255

	// m_fadeFrameCount =  0のときfadeAlpha = 255 真っ黒
	// m_fadeFrameCount = 30のときfadeAlpha = 0   画面が映る

	// 割合を利用してm_fadeFrameCountをfadeAlphaに変換する

	// 30フレームかけて数値を0~255に変化させたい
	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
