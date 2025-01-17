#pragma once
#include "Vec2.h"

class Enemy
{
public:
	Enemy();
	~Enemy();

	void Init();
	void End();
	void Update();
	void Draw();

	// �G�L�����N�^�[�̏����擾����
	float GetLeft();
	float GetTop();
	float GetRight();
	float GetBottom();

	// �G�L�����N�^�[�̏����ݒ�
	void Setting();

private:
	// �O���t�B�b�N�̃n���h��
	int m_handle;

	// �A�j���[�V�����֘A
	int m_animFrameCount;

	// �ړ����
	Vec2 m_pos;

	// �ړ�����
	// ���Ɉړ����Ă���Ƃ���0��菬����
	// �E�Ɉړ����Ă���Ƃ���0���傫��
	float m_speed;

	// �ҋ@�t���[��
	int m_waitFrameCount;

};