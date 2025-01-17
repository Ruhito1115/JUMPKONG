#pragma once
#include "Vec2.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();

	// 敵キャラクターの情報を取得する
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();

	// 敵キャラクターの初期設定
	void Setting();

private:
	// グラフィックのハンドル
	int m_handle;

	// アニメーション関連
	int m_animFrameCount;

	// 移動情報
	Vec2 m_pos;

	// 移動方向
	// 左に移動しているときは0より小さく
	// 右に移動しているときは0より大きい
	float m_speed;

	// 待機フレーム
	int m_waitFrameCount;

};