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

// �萔�̒�`
namespace
{
	// �L�����N�^�[�O���t�B�b�N�̕��ƍ���
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// �A�j���[�V�����̃R�}��
	constexpr int kIdleAnimNum = 6;
	constexpr int kRunAnimNum = 6;

	// �A�j���[�V����1�R�}�̃t���[����
	constexpr int kSingleAnimFrame = 5;

	// �L�����N�^�[�̈ړ����x
	constexpr float kSpeed = 2.0f;

	// �n�ʂ̍���
	constexpr float kFieldHeight = 300.0f + 352.0f;

	// �W�����v����
	constexpr float kJumpPower = -13.0f; // �W�����v�̉���
	constexpr float kGravity = 0.4f;    // �d��

	// �_���[�W�H�������̖��G����
	constexpr int kDamageBlinkFrame = 30;

	// �v���C���[�̏���HP
	constexpr int kMaxHp = 3;

	// ���S���o
	constexpr int kDeadStopFrame = 30;    // ���񂾏u�ԂɎ~�܂鎞��
	constexpr float kDeadJumpSpeed = -4.0f; // ���񂾂��Ɣ�яオ�鏉��
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
	// �O���t�B�b�N�̉��
	DeleteGraph(m_handleIdle);
	DeleteGraph(m_handleRun);
}

void Player::Update()
{
	// �����Ă���Ƃ��Ǝ���ł���Ƃ��ŏ�����؂蕪����
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
	// �_�ŏ���
	if ((m_blinkFrameCount / 2) % 2)
	{
		return;
	}

	int animNo = m_animFrame / kSingleAnimFrame;

	// �ړ����Ă���ꍇ��   m_isRun = true
	// �ړ����Ă��Ȃ��ꍇ�� m_isRun = false �ɂȂ��Ă���

	// m_pos�����������ɗ���悤�ɕ\������
	// ���ɔ��L�����A���1�L�������炷���Ƃő���������m_pos�ɂȂ�

	// �g�p����O���t�B�b�N�̃n���h������U�ʂ�int�^�ϐ��Ɋi�[����
	int useHandle = m_handleIdle;
	if (m_isRun)
	{
		useHandle = m_handleRun;
	}

	// ����ł�����㉺���]
	bool isDead = false;
	if (m_hp <= 0)
	{
		isDead = true;
	}

	DrawRectGraph(static_cast<int>(m_pos.x - kGraphWidth / 2), static_cast<int>(m_pos.y - kGraphHeight),
		animNo * kGraphWidth, 0, kGraphWidth, kGraphHeight,
		useHandle, true, m_isDirLeft, isDead);
	DrawCircle(m_pos.x, m_pos.y, 4, 0xff0000, false);

	//m_pos��player�̑������w���Ă��邽��player�̒������w��Vec2���쐬
	Vec2 centerPos = m_pos;
	centerPos.y += kGraphHeight / 2 * -1;
	//player��pos��Rect�ɕϊ�
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
	// ���Ƀ_���[�W���󂯂Ă���(���G���Ԃ�)
	// �ēx�_���[�W���󂯂邱�Ƃ͖���
	if (m_blinkFrameCount > 0) return;

	// ���G����(�_�ł��鎞��)��ݒ肷��
	m_blinkFrameCount = kDamageBlinkFrame;

	// �_���[�W���󂯂�
	m_hp--;
	// HP��0�ȉ��ɂȂ����玀�S���o���J�n����
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
	// ���G���Ԃ̍X�V
	m_blinkFrameCount--;
	if (m_blinkFrameCount < 0)
	{
		m_blinkFrameCount = 0;
	}

	// �A�j���[�V�����̍X�V
	m_animFrame++;

	// �ҋ@����0~65 �ړ�����0~71
	// m_animFrame >= 66�̎��Ɉړ��A�j������ҋ@�A�j���ɐ؂�ւ���
	// 

	int totalFrame = kIdleAnimNum * kSingleAnimFrame;
	if (m_isRun)
	{
		totalFrame = kRunAnimNum * kSingleAnimFrame;
	}

	// �A�j���[�V�����̍��v�t���[�����𒴂�����ŏ��ɖ߂�
	if (m_animFrame >= totalFrame)
	{
		m_animFrame = 0;
	}

	bool isLastRun = m_isRun;

	// ���E�ɃL�����N�^�[�𓮂���
	m_isRun = false;
	if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		// ���L�[�������Ă���Ƃ��̏���
		m_pos.x -= kSpeed;  // �������Ɉʒu��ύX
		m_isDirLeft = true; // �L�����N�^�[�����������Ă���
		m_isRun = true;
	}

	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		// �E�L�[�������Ă���Ƃ��̏���
		m_pos.x += kSpeed;   // �E�����Ɉʒu��ύX
		m_isDirLeft = false; // �L�����N�^�[���E�������Ă���
		m_isRun = true;
	}

	// 1�{�^�����������Ƃ��ɃW�����v����
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
	// ��������f�o�b�O�@�\ L�{�^��(5)�Ɋ��蓖�Ă�
//	if (pad & PAD_INPUT_5)
	if (Pad::IsTrigger(PAD_INPUT_5))
	{
		m_hp = 0;
	}
#endif

	if (m_isJump)
	{
		// �W�����v���͏�������ԑ���
		// ���̌㕑�t���[��������ւ̈ړ��ʂ����������炵�Ă���(�d�͂̍Č�)
		// �㏸���~�܂����獡�x�͉������ւ̈ړ��ʂ����������₵�Ă���(�d�͂̍Č�)
		// �������Ɉړ��������ʁA�n�ʂɂ�����W�����v�I��
		m_pos.y += m_jumpSpeed;
		m_jumpSpeed += kGravity; // ���t���[���������ɉ�������

		if (m_jumpSpeed > 0.0f)
		{
			if (m_pos.y >= kFieldHeight)
			{
				// �W�����v���I������
				m_isJump = false;
				m_jumpSpeed = 0.0f;

				// �n�ʂɂ̂߂肱�ނ��Ƃ�����̂Œn�ʂ̍����Ɉʒu��␳����
				m_pos.y = kFieldHeight;
			}
		}
	}
	//m_pos��player�̑������w���Ă��邽��player�̒������w��Vec2���쐬
	Vec2 centerPos = m_pos;
	centerPos.y += kGraphHeight / 2 * -1;
	//player��pos��Rect�ɕϊ�
	Rect playerRect;
	playerRect.SetRect(centerPos, kGraphWidth, kGraphHeight);
	//���������ꍇ��chip��Rect
	Rect colChipRect;
	//����������true
	bool isCol;
	//player��map�̓����蔻����s��
	isCol = m_map.IsCol(playerRect, colChipRect);
	//����������
	if (isCol)
	{
		//��������chip�̓����蔻��̕\��
		DrawBox(colChipRect.left - 2, colChipRect.top - 2, colChipRect.right + 2, colChipRect.bottom + 2, 0xffffff, false);
		//������
		//chip�ɓ��������ꍇ
		//player�̈ʒu��chip�ɓ�����Ȃ��Ȃ�܂Ŗ߂�����
		
	}

	// �������s�������ʁA�A�j���[�V�������ς���Ă����ꍇ�̏���
	if (m_isRun != isLastRun)
	{
		m_animFrame = 0;
	}

	// ��A�̏������s�������
	// ���̃t���[���ŕK�v�ȏ��������o�ϐ��ɕۑ����Ă���
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
	// ���S���u�~�܂�
	m_deadFrameCount++;
	if (m_deadFrameCount < kDeadStopFrame)
	{
		return;
	}

	// ��ʊO�ɗ����Ă������o
	m_pos.y += m_jumpSpeed;
	m_jumpSpeed += kGravity;
}
