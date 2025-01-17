#include "GameOverScene.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"

namespace
{
	// �����̓_��
	constexpr int kBlinkCycleFrame = 60;
	constexpr int kBlinkDispFrame = 40;

	// �����̕\���ʒu
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
	// 1�b�T�C�N���ŕ\���A��\����؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}

	// 1�{�^������������Main�Ɉڍs����
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		return SceneManager::SceneKind::kSceneTitle;
	}

	// �������Ȃ���΃V�[���͑J�ڂ��Ȃ�(�^�C�g����ʂ̂܂�)
	return SceneManager::kGameOverScene;

	if (m_isGameEnd)
	{
		// test �Q�[���I�[�o�[�ɂȂ�����t�F�[�h�A�E�g������
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::kSceneTitle;
		}
	}
	else
	{
		// �t�F�[�h�C������
		m_fadeFrameCount++;
		if (m_fadeFrameCount > 30)
		{
			m_fadeFrameCount = 30;
		}
	}
}

void GameOverScene::Draw()
{
	// �^�C�g���\��
	int width = GetDrawStringWidth("GameOver", strlen("GameOver"));
	DrawString(Game::kScreenWidth / 2 - width / 2, kTitleY, "GameOver", GetColor(255, 255, 255));

	// 1�{�^���������Ă�������
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		width = GetDrawStringWidth("�{�^���������Ă�������", strlen("1�{�^���������Ă�������"));
		DrawString(Game::kScreenWidth / 2 - width / 2, kButtonTextY, "1�{�^���������Ă�������", GetColor(255, 255, 255));
	}
}

void GameOverScene::Init()
{
}

void GameOverScene::End()
{
}
