#include "SceneTitle.h"
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
	// 1�b�T�C�N���ŕ\���A��\����؂�ւ���
	m_blinkFrameCount++;
	if (m_blinkFrameCount >= kBlinkCycleFrame)
	{
		m_blinkFrameCount = 0;
	}
}
*/

SceneManager::SceneKind SceneTitle::Update()
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
		return SceneManager::SceneKind::kSceneMain;
	}

	// �������Ȃ���΃V�[���͑J�ڂ��Ȃ�(�^�C�g����ʂ̂܂�)
	return SceneManager::SceneKind();
}

void SceneTitle::Draw()
{
	// �^�C�g���\��
	int width = GetDrawStringWidth("JUMPKONG", strlen("JUMPKONG"));
	DrawString(Game::kScreenWidth / 2 - width / 2, kTitleY, "JUMPKONG", GetColor(255, 255, 255));

	// 1�{�^���������Ă�������
	if (m_blinkFrameCount < kBlinkDispFrame)
	{
		width = GetDrawStringWidth("�{�^���������Ă�������", strlen("1�{�^���������Ă�������"));
		DrawString(Game::kScreenWidth / 2 - width / 2, kButtonTextY, "1�{�^���������Ă�������", GetColor(255, 255, 255));
	}
}
