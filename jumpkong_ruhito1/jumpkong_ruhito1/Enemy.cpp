#include "Enemy.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>

// 定数の定義
namespace
{
	// キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 52;
	constexpr int kGraphHeight = 34;

	// アニメーションのコマ数
	constexpr int kRunAnimNum = 6;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 7;

	// 初期位置
	constexpr int kDefaultLeft = 0.0f - kGraphWidth / 2;
	constexpr int kDefaultRight = Game::kScreenWidth + kGraphWidth / 2;

	// 地面の高さ
	constexpr float kFieldHeight = 500.0f + 352.0f;

	// スピード
	constexpr float kSpeed = 1.0f;

	// 待ち時間
	constexpr int kWaitFrameMin = 30;    // 最小待ちフレーム数
	constexpr int kWaitFrameRandom = 60; // 待ちフレームランダム幅
}

Enemy::Enemy() :
	m_handle(-1),
	m_animFrameCount(0)
{
	Setting();
	m_pos.y = kFieldHeight;
}

Enemy::~Enemy()
{
}

void Enemy::Init()
{
	m_handle = LoadGraph("data/image/enemy000.png");
	assert(m_handle != -1);
}

void Enemy::End()
{
	DeleteGraph(m_handle);
}

void Enemy::Update()
{
	// 一定時間待つ
	m_waitFrameCount--;
	if (m_waitFrameCount > 0)
	{
		// 関数をここで終わらせる
		return;
	}

	// アニメーション処理
	m_animFrameCount++;
	if (m_animFrameCount >= kRunAnimNum * kSingleAnimFrame)
	{
		m_animFrameCount = 0;
	}

	// 移動
	m_pos.x += m_speed;

	// 画面外に出たら再登場させる
	if ((m_pos.x <= 0.0f - kGraphWidth / 2) &&
		(m_speed < 0.0f))
	{
		// 右方向に移動した結果、左から画面外に出た
		Setting();
	}

	if ((m_pos.x >= Game::kScreenWidth + kGraphWidth / 2) &&
		(m_speed > 0.0f))
	{
		// 左方向に移動した結果、右から画面外に出た
		Setting();
	}
}

void Enemy::Draw()
{
	int animNo = m_animFrameCount / kSingleAnimFrame;

	// 右に移動しているか、左に移動しているかをチェックして
	// 左右反転の設定を行う

	// 左右反転するかしないか
	bool isFlip = false;
	if (m_speed > 0.0f)
	{
		// 右向き　反転する
		isFlip = true;
	}

	DrawRectGraph(m_pos.x - kGraphWidth / 2, m_pos.y - kGraphHeight,
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		m_handle, true, isFlip);

#ifdef _DEBUG
	// 当たり判定のデバッグ表示
	DrawBox(GetLeft(), GetTop(),
		GetRight(), GetBottom(),
		GetColor(255, 0, 0), false);
#endif
}

float Enemy::GetLeft()
{
	return (m_pos.x - kGraphWidth / 2);
}

float Enemy::GetTop()
{
	return (m_pos.y - kGraphHeight);
}

float Enemy::GetRight()
{
	return (m_pos.x + kGraphWidth / 2);
}

float Enemy::GetBottom()
{
	return m_pos.y;
}

void Enemy::Setting()
{
	// 初期位置、移動方向、待ち時間を設定する
	if (GetRand(1) == 1)
	{
		// 右から登場する
		m_pos.x = kDefaultRight;
		m_speed = -kSpeed;
	}
	else
	{
		// 左から登場する
		m_pos.x = kDefaultLeft;
		m_speed = kSpeed;
	}
	m_pos.y = kFieldHeight;

	m_waitFrameCount = GetRand(kWaitFrameRandom) + kWaitFrameMin;
}
