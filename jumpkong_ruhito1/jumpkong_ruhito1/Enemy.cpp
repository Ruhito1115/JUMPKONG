#include "Enemy.h"
#include "DxLib.h"
#include "game.h"
#include <cassert>

// �萔�̒�`
namespace
{
	// �L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 52;
	constexpr int kGraphHeight = 34;

	// �A�j���[�V�����̃R�}��
	constexpr int kRunAnimNum = 6;

	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 7;

	// �����ʒu
	constexpr int kDefaultLeft = 0.0f - kGraphWidth / 2;
	constexpr int kDefaultRight = Game::kScreenWidth + kGraphWidth / 2;

	// �n�ʂ̍���
	constexpr float kFieldHeight = 500.0f + 352.0f;

	// �X�s�[�h
	constexpr float kSpeed = 1.0f;

	// �҂�����
	constexpr int kWaitFrameMin = 30;    // �ŏ��҂��t���[����
	constexpr int kWaitFrameRandom = 60; // �҂��t���[�������_����
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
	// ��莞�ԑ҂�
	m_waitFrameCount--;
	if (m_waitFrameCount > 0)
	{
		// �֐��������ŏI��点��
		return;
	}

	// �A�j���[�V��������
	m_animFrameCount++;
	if (m_animFrameCount >= kRunAnimNum * kSingleAnimFrame)
	{
		m_animFrameCount = 0;
	}

	// �ړ�
	m_pos.x += m_speed;

	// ��ʊO�ɏo����ēo�ꂳ����
	if ((m_pos.x <= 0.0f - kGraphWidth / 2) &&
		(m_speed < 0.0f))
	{
		// �E�����Ɉړ��������ʁA�������ʊO�ɏo��
		Setting();
	}

	if ((m_pos.x >= Game::kScreenWidth + kGraphWidth / 2) &&
		(m_speed > 0.0f))
	{
		// �������Ɉړ��������ʁA�E�����ʊO�ɏo��
		Setting();
	}
}

void Enemy::Draw()
{
	int animNo = m_animFrameCount / kSingleAnimFrame;

	// �E�Ɉړ����Ă��邩�A���Ɉړ����Ă��邩���`�F�b�N����
	// ���E���]�̐ݒ���s��

	// ���E���]���邩���Ȃ���
	bool isFlip = false;
	if (m_speed > 0.0f)
	{
		// �E�����@���]����
		isFlip = true;
	}

	DrawRectGraph(m_pos.x - kGraphWidth / 2, m_pos.y - kGraphHeight,
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		m_handle, true, isFlip);

#ifdef _DEBUG
	// �����蔻��̃f�o�b�O�\��
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
	// �����ʒu�A�ړ������A�҂����Ԃ�ݒ肷��
	if (GetRand(1) == 1)
	{
		// �E����o�ꂷ��
		m_pos.x = kDefaultRight;
		m_speed = -kSpeed;
	}
	else
	{
		// ������o�ꂷ��
		m_pos.x = kDefaultLeft;
		m_speed = kSpeed;
	}
	m_pos.y = kFieldHeight;

	m_waitFrameCount = GetRand(kWaitFrameRandom) + kWaitFrameMin;
}
