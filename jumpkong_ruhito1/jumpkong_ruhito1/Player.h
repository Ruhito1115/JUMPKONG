#pragma once
#include<memory>
#include "Rect.h"

class Map;
class Player
{
public:
	Player(Map& map);
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	// プレイヤーの情報を取得する
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;

	int GetHp() const { return m_hp; };

	// プレイヤーと敵がぶつかった
	void OnDamage();

	// クラスの外から呼び出さないメンバ関数はprivateに
private:
	// 状態変化するときの処理
	// 死亡演出の初期化
	void InitDead();

	// 各状態毎のUpdate処理
	void UpdateNormal(); // ゲーム中のUpdate
	void UpdateDead();   // 死亡後のUpdate

private:
	// グラフィックハンドル
	int m_handleIdle;
	int m_handleRun;

	// アニメーション関連
	int m_animFrame; // フレーム数を数える
	// 現在再生中のアニメーション
	// true:走っている false:待機
	bool m_isRun;

	// プレイヤーの表示位置
	Vec2 m_pos;

	// プレイヤーが左方向を向いているか
	// true:左向き false:右向き
	bool m_isDirLeft;

	// ジャンプ処理
	bool m_isJump;
	float m_jumpSpeed;

	// 点滅
	int m_blinkFrameCount;

	// プレイヤーのHP
	int m_hp;

	// 死亡演出
	int m_deadFrameCount;
	// 上下移動の演出はm_jumpSpeedを使いまわす

// ジャンプボタンのトリガー判定
// 1つ前のフレームにジャンプボタンが押されていたかどうか
// を覚えておく
	bool m_isLastJumpButton;

	Map& m_map;
};
