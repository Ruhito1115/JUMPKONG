#pragma once
//#include "SceneTitle.h"
//#include "SceneMain.h"

// クラスのプロトタイプ宣言
// クラスのポインタのみを扱う場合はヘッダーをインクルードせずに
// プロトタイプ宣言のみを行う
class SceneTitle;
class SceneMain;
class GameOverScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();

	void Update();
	void Draw();

public:
	// 列挙型を使用して現在実行中のシーンを管理する
	enum SceneKind
	{
		kSceneTitle,
		kSceneMain,
		kGameOverScene,

		kSceneNum
	};

private:
	// 現在実行中のシーン
	SceneKind m_kind;

	// 各シーンのポインタ
	SceneTitle* m_pSceneTitle;
	SceneMain* m_pSceneMain;
	GameOverScene* m_pGameOverScene;
};
