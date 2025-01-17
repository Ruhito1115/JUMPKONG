#include "Player.h"
#include "DxLib.h"
#include "Map.h"
#include <cassert>

#include "Rect.h"
#include "Pad.h"

#include "game.h"
#include<memory>

#ifdef _DEBUG
#define DISP_COLLISION
#endif

// 定数の定義
namespace
{
	// キャラクターグラフィックの幅と高さ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// アニメーションのコマ数
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 6;

	// アニメーション1コマのフレーム数
	constexpr int kSingleAnimFrame = 5;

	// キャラクターの移動速度
	constexpr float kSpeed = 2.0f;

	// 地面の高さ
	constexpr float kFieldHeight = 300.0f + 352.0f;

	// ジャンプ処理
	constexpr float kJumpPower = -13.0f; // ジャンプの加速
	constexpr float kGravity = 0.4f;    // 重力

	// ダメージ食らった後の無敵時間
	constexpr int kDamageBlinkFrame = 30;

	// プレイヤーの初期HP
	constexpr int kMaxHp = 3;

	// 死亡演出
	constexpr int kDeadStopFrame = 30;    // 死んだ瞬間に止まる時間
	constexpr float kDeadJumpSpeed = -4.0f; // 死んだあと飛び上がる初速
}

Player::Player(Map& map) :
	m_handleIdle(-1),
	m_handleRun(-1),
	m_animFrame(0),
	m_isRun(false),
	m_pos(320.0f, kFieldHeight),
	m_isDirLeft(false),
	m_isJump(false),
	m_jumpSpeed(0.0f),
	m_blinkFrameCount(0),
	m_hp(kMaxHp),
	m_deadFrameCount(0),
	m_isLastJumpButton(false),
	m_map(map)
{
}

Player::~Player()
{
}

void Player::Init()
{
	m_handleIdle = LoadGraph("data/image/idle.png");
	assert(m_handleIdle != -1);

	m_handleRun = LoadGraph("data/image/run.png");
	assert(m_handleRun != -1);
}

void Player::End()
{
	// グラフィックの解放
	DeleteGraph(m_handleIdle);
	DeleteGraph(m_handleRun);
}

void Player::Update()
{
	// 生きているときと死んでいるときで処理を切り分ける
	if (m_hp > 0)
	{
		UpdateNormal();
	}
	else
	{
		UpdateDead();
	}
}

void Player::Draw()
{
	// 点滅処理
	if ((m_blinkFrameCount / 2) % 2)
	{
		return;
	}

	int animNo = m_animFrame / kSingleAnimFrame;

	// 移動している場合は   m_isRun = true
	// 移動していない場合は m_isRun = false になっている

	// m_posが足元中央に来るように表示する
	// 左に半キャラ、上に1キャラずらすことで足元中央がm_posになる

	// 使用するグラフィックのハンドルを一旦別のint型変数に格納する
	int useHandle = m_handleIdle;
	if (m_isRun)
	{
		useHandle = m_handleRun;
	}

	// 死んでいたら上下反転
	bool isDead = false;
	if (m_hp <= 0)
	{
		isDead = true;
	}

	DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		useHandle, true, m_isDirLeft, isDead);
	DrawCircle(m_pos.x, m_pos.y, 4, 0xff0000, false);

	//m_posはplayerの足元を指しているためplayerの中央を指すVec2を作成
	Vec2 centerPos = m_pos;
	centerPos.y += kGraphHeight / 2 * -1;
	//playerのposをRectに変換
	Rect playerRect;
	playerRect.SetRect(centerPos, kGraphWidth, kGraphHeight);
	DrawBox(playerRect.left - 2, playerRect.top - 2, playerRect.right + 2, playerRect.bottom + 2, 0xff0000, false);
}

float Player::GetLeft() const
{
	return (m_pos.x - kGraphWidth / 2);
}

float Player::GetTop() const
{
	return (m_pos.y - kGraphHeight);
}

float Player::GetRight() const
{
	return (m_pos.x + kGraphWidth / 2);
}

float Player::GetBottom() const
{
	return m_pos.y;
}

void Player::OnDamage()
{
	// 既にダメージを受けている(無敵時間は)
	// 再度ダメージを受けることは無い
	if (m_blinkFrameCount > 0) return;

	// 無敵時間(点滅する時間)を設定する
	m_blinkFrameCount = kDamageBlinkFrame;

	// ダメージを受ける
	m_hp--;
	// HPが0以下になったら死亡演出を開始する
	if (m_hp <= 0)
	{
		InitDead();
	}
}

void Player::InitDead()
{
	m_jumpSpeed = kDeadJumpSpeed;
	m_deadFrameCount = 0;
	m_blinkFrameCount = 0;
}

void Player::UpdateNormal()
{
	// 無敵時間の更新
	m_blinkFrameCount--;
	if (m_blinkFrameCount < 0)
	{
		m_blinkFrameCount = 0;
	}

	// アニメーションの更新
	m_animFrame++;

	// 待機中は0~65 移動中は0~71
	// m_animFrame >= 66の時に移動アニメから待機アニメに切り替わると
	// 

	int totalFrame = kIdleAnimNum * kSingleAnimFrame;
	if (m_isRun)
	{
		totalFrame = kRunAnimNum * kSingleAnimFrame;
	}

	// アニメーションの合計フレーム数を超えたら最初に戻す
	if (m_animFrame >= totalFrame)
	{
		m_animFrame = 0;
	}

	bool isLastRun = m_isRun;

	// 左右にキャラクターを動かす
	m_isRun = false;
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// 左キーを押しているときの処理
		m_pos.x -= kSpeed;  // 左方向に位置を変更
		m_isDirLeft = true; // キャラクターが左を向いている
		m_isRun = true;
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// 右キーを押しているときの処理
		m_pos.x += kSpeed;   // 右方向に位置を変更
		m_isDirLeft = false; // キャラクターが右を向いている
		m_isRun = true;
	}

	// 1ボタンを押したときにジャンプする
//	if ((!m_isLastJumpButton) && (pad & PAD_INPUT_1))
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		if (!m_isJump)
		{
			m_isJump = true;
			m_jumpSpeed = kJumpPower;
		}
	}

#ifdef _DEBUG
	// 即死するデバッグ機能 Lボタン(5)に割り当てる
//	if (pad & PAD_INPUT_5)
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		m_hp = 0;
	}
#endif

	if (m_isJump)
	{
		// ジャンプ中は初速が一番早く
		// その後舞フレーム上方向への移動量を少しずつ減らしていく(重力の再現)
		// 上昇が止まったら今度は下方向への移動量を少しずつ増やしていく(重力の再現)
		// 下方向に移動した結果、地面についたらジャンプ終了
		m_pos.y += m_jumpSpeed;
		m_jumpSpeed += kGravity; // 毎フレーム下方向に加速する

		if (m_jumpSpeed > 0.0f)
		{
			if (m_pos.y >= kFieldHeight)
			{
				// ジャンプを終了する
				m_isJump = false;
				m_jumpSpeed = 0.0f;

				// 地面にのめりこむことがあるので地面の高さに位置を補正する
				m_pos.y = kFieldHeight;
			}
		}
	}
	//m_posはplayerの足元を指しているためplayerの中央を指すVec2を作成
	Vec2 centerPos = m_pos;
	centerPos.y += kGraphHeight / 2 * -1;
	//playerのposをRectに変換
	Rect playerRect;
	playerRect.SetRect(centerPos, kGraphWidth, kGraphHeight);
	//当たった場合のchipのRect
	Rect colChipRect;
	//当たったらtrue
	bool isCol;
	//playerとmapの当たり判定を行う
	isCol = m_map.IsCol(playerRect, colChipRect);
	//当たったら
	if (isCol)
	{
		//当たったchipの当たり判定の表示
		DrawBox(colChipRect.left - 2, colChipRect.top - 2, colChipRect.right + 2, colChipRect.bottom + 2, 0xffffff, false);
		//ここに
		//chipに当たった場合
		//playerの位置をchipに当たらなくなるまで戻す処理
		
	}

	// 処理を行った結果、アニメーションが変わっていた場合の処理
	if (m_isRun != isLastRun)
	{
		m_animFrame = 0;
	}

	// 一連の処理を行った後に
	// 次のフレームで必要な情報をメンバ変数に保存しておく
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_isLastJumpButton = true;
	}
	else
	{
		m_isLastJumpButton = false;
	}
}

void Player::UpdateDead()
{
	// 死亡後一瞬止まる
	m_deadFrameCount++;
	if (m_deadFrameCount < kDeadStopFrame)
	{
		return;
	}

	// 画面外に落ちていく演出
	m_pos.y += m_jumpSpeed;
	m_jumpSpeed += kGravity;
}
