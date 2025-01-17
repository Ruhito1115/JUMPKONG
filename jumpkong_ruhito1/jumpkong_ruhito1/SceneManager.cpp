#include "SceneManager.h"
#include <cassert>
#include "DxLib.h"

#include "Pad.h"

// ヘッダーではクラスのプロトタイプ宣言のみを行う
// cppでヘッダーのインクルードを行う
#include "SceneTitle.h"
#include "SceneMain.h"
#include "GameOverScene.h"

SceneManager::SceneManager() :
	m_kind(kSceneTitle),
	m_pSceneTitle(nullptr), // メモリを確保していない状態
	m_pSceneMain(nullptr),   // メモリを確保していない状態
	m_pGameOverScene(nullptr)	//メモリを確保していない状態
{
	// コンストラクタで各メンバのメモリ確保
	// は分かりやすいが必要のない情報をメモリ上に置き続けるので
	// メモリ効率はよろしくない

	// 必要なシーンのみメモリを確保することでメモリを効率よく使用する
	// 
	// 各シーンのメモリ確保
//	m_pSceneTitle = new SceneTitle();
//	m_pSceneMain = new SceneMain();
}

SceneManager::~SceneManager()
{
	// 各シーンのメモリ解放
	if (m_pSceneTitle != nullptr) // 本当はdelete内でチェックしているから不要
	{
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
	}

	if (m_pSceneMain != nullptr)
	{
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
	}

	if (m_pGameOverScene != nullptr)
	{
		delete m_pGameOverScene;
		m_pGameOverScene = nullptr;
	}
}

void SceneManager::Init()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle = new SceneTitle();
		m_pSceneTitle->Init();
		break;
	case SceneManager::kSceneMain:
		m_pSceneMain = new SceneMain();
		m_pSceneMain->Init();
		break;
	case SceneManager::kGameOverScene:
		m_pGameOverScene = new GameOverScene();
		m_pGameOverScene->Init();
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // falseの場合は必ず止まる
		break;
	}
}

void SceneManager::End()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->End();
		delete m_pSceneTitle;
		m_pSceneTitle = nullptr;
		break;
	case SceneManager::kSceneMain:
		m_pSceneMain->End();
		delete m_pSceneMain;
		m_pSceneMain = nullptr;
		break;
	case SceneManager::kGameOverScene:
		m_pGameOverScene->End();
		delete m_pGameOverScene;
		m_pGameOverScene = nullptr;
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // falseの場合は必ず止まる
		break;
	}
}

void SceneManager::Update()
{
	// パッド入力状態の更新
	Pad::Update();

	// 遷移先シーンの番号
	SceneKind nextKind = m_kind;

	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		nextKind = m_pSceneTitle->Update();
		break;
	case SceneManager::kSceneMain:
		nextKind = m_pSceneMain->Update();
		break;
	case SceneManager::kGameOverScene:
		nextKind = m_pGameOverScene->Update();
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // falseの場合は必ず止まる
		break;
	}

	// 現在のシーンと違うシーンへの切り替わりを要求された場合
	// 次のシーンへの遷移を行う
	if (nextKind != m_kind)
	{
		// 現在実行中のシーン(m_kind)の終了処理
		End();

		// 次のシーンに切り替え
		m_kind = nextKind;
		// 切り替え後のシーンの初期化
		Init();
	}
}

void SceneManager::Draw()
{
	switch (m_kind)
	{
	case SceneManager::kSceneTitle:
		m_pSceneTitle->Draw();
		break;
	case SceneManager::kSceneMain:
		m_pSceneMain->Draw();
		break;
	case SceneManager::kGameOverScene:
		m_pGameOverScene->Draw();
		break;
	case SceneManager::kSceneNum:
	default:
		assert(false); // falseの場合は必ず止まる
		break;
	}
}