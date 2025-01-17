#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"
#include "Pad.h"
#include <cassert>

namespace
{
	// �Q�[���I�[�o�[�̕������\�������܂ł̃t���[����
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
	// �t�H���g�̐���
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
	// �O���t�B�b�N�̍폜
	DeleteGraph(m_lifeHandle);

	DeleteFontToHandle(m_fontHandle);
}

SceneManager::SceneKind SceneMain::Update()
{
	if (m_isGameEnd)
	{
		// test �Q�[���I�[�o�[�ɂȂ�����t�F�[�h�A�E�g������
		m_fadeFrameCount--;
		if (m_fadeFrameCount < 0)
		{
			m_fadeFrameCount = 0;
			return SceneManager::kGameOverScene;
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

	m_countFrame--;

	m_map.Update();
	m_player.Update();

	//	m_life.Update();
	for (int i = 0; i < 3; i++)
	{
		m_life[i].Update();
	}

	// �J�E���g�_�E�����̓Q�[�����i�s���Ȃ�
	if (m_countFrame > 0)
	{
		return SceneManager::SceneKind::kSceneMain;
	}

	// �Q�[���I�[�o�[���o
	if (m_player.GetHp() <= 0)
	{
		m_gameoverFrameCount++;
		if (m_gameoverFrameCount > kGameoverFadeFrame)
		{
			m_gameoverFrameCount = kGameoverFadeFrame;

			// �Q�[���I�[�o�[�̂��΂��\������؂������
			// 1�{�^������������^�C�g���ɖ߂�
			if (Pad::IsTrigger(PAD_INPUT_1))
			{
				m_isGameEnd = true;
			}
		}
	}

	// �ȍ~�̓J�E���g�_�E���I����Ɏ��s���鏈��
	m_enemy.Update();

	// �v���C���[�̓����蔻��
	// �ŏ��͈�U�������Ă����ԁA�Ƃ������Ƃɂ���
	bool isCol = true;

	// ��΂ɓ�����Ȃ��p�^�[���̏ꍇ��
	// bool isCol = false �Ƃ��ē������Ă��Ȃ���Ԃɂ���
	if (m_player.GetLeft() > m_enemy.GetRight())
	{
		// �G�����S�Ƀv���C���[�̍��ɂ���̂œ������Ă��Ȃ�
		isCol = false;
	}

	if (m_player.GetTop() > m_enemy.GetBottom())
	{
		// �G�����S�Ƀv���C���[�̏�ɂ���̂œ������Ă��Ȃ�
		isCol = false;
	}

	if (m_player.GetRight() < m_enemy.GetLeft())
	{
		// �G�����S�Ƀv���C���[�̉E�ɂ���̂œ������Ă��Ȃ�
		isCol = false;
	}

	if (m_player.GetBottom() < m_enemy.GetTop())
	{
		// �G�����S�Ƀv���C���[�̉��ɂ���̂œ������Ă��Ȃ�
		isCol = false;
	}

	// �����ɓ��B�����Ƃ�,
	// isCol = true �Ȃ瓖�����Ă���@false�Ȃ瓖�����Ă��Ȃ�
	if (isCol)
	{
		//printfDx("��������\n");
		m_player.OnDamage();
	}

	// �������Ȃ���ΑJ�ڂ��Ȃ�
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

	// �J�E���g�_�E���̕\��
	if (m_countFrame > 0)
	{
		int width = GetDrawFormatStringWidthToHandle(m_fontHandle, "%d", m_countFrame / 60 + 1);
		DrawFormatStringToHandle(Game::kScreenWidth / 2 - width / 2, Game::kScreenHeight / 2 - 64 / 2,
			GetColor(255, 0, 0), m_fontHandle, "%d", m_countFrame / 60 + 1);
	}

	// �Q�[���I�[�o�[�̕\��
	if (m_player.GetHp() <= 0)
	{
		// 0~60�̊Ԃŕω�����m_gameoverFrameCount��
		// 0~255�̒l�ɕϊ�����K�v������

		// �������g�p���ĕϊ����s��
		// m_gameoverFrameCount��i�s�����ɕϊ�����
		float progressRate = static_cast<float>(m_gameoverFrameCount) / kGameoverFadeFrame;
		//	printfDx("%f %%\n", progressRate);

			// ���������ۂ̓����x�ɕϊ�����
		int alpha = static_cast<int>(255 * progressRate);

		// �����ȍ~�Ă΂��Draw�֐��̕`����@��ύX����
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		int width = GetDrawStringWidthToHandle("GAME OVER", strlen("GAME OVER"), m_fontHandle);
		DrawStringToHandle(Game::kScreenWidth / 2 - width / 2, Game::kScreenHeight / 2 - 64 / 2,
			"GAME OVER", GetColor(255, 0, 0), m_fontHandle);

		// �ȍ~�̕\�������������Ȃ�Ȃ��悤�Ɍ��̐ݒ�ɖ߂��Ă���
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// �t�F�[�h����
	int fadeAlpha = 0; // 0~255

	// m_fadeFrameCount =  0�̂Ƃ�fadeAlpha = 255 �^����
	// m_fadeFrameCount = 30�̂Ƃ�fadeAlpha = 0   ��ʂ��f��

	// �����𗘗p����m_fadeFrameCount��fadeAlpha�ɕϊ�����

	// 30�t���[�������Đ��l��0~255�ɕω���������
	float fadeRate = static_cast<float>(m_fadeFrameCount) / 30;
	fadeRate = 1.0f - fadeRate;
	fadeAlpha = 255 * fadeRate;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, fadeAlpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
