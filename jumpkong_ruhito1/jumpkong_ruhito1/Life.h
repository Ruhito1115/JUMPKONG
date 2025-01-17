#pragma once

// プレイヤーの残りライフを表示するUI
class Life
{
public:
	Life();
	~Life();

	void Init();
	void End();
	void Update();
	void Draw();

	// データ設定
	void SetHandle(int handle) { m_handle = handle; };
	void SetIndex(int index) { m_index = index; };

private:
	// グラフィックのハンドル
	int m_handle;

	// アニメーションの進行管理
	int m_animFrameCount;

	// 通し番号
	int m_index;
};
