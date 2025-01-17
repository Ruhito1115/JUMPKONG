#pragma once
#include<memory>
#include "Rect.h"

class Map;
class Player
{
public:
	Player(Map& map);
	~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	// �v���C���[�̏����擾����
	float GetLeft() const;
	float GetTop() const;
	float GetRight() const;
	float GetBottom() const;

	int GetHp() const { return m_hp; };

	// �v���C���[�ƓG���Ԃ�����
	void OnDamage();

	// �N���X�̊O����Ăяo���Ȃ������o�֐���private��
private:
	// ��ԕω�����Ƃ��̏���
	// ���S���o�̏�����
	void InitDead();

	// �e��Ԗ���Update����
	void UpdateNormal(); // �Q�[������Update
	void UpdateDead();   // ���S���Update

private:
	// �O���t�B�b�N�n���h��
	int m_handleIdle;
	int m_handleRun;

	// �A�j���[�V�����֘A
	int m_animFrame; // �t���[�����𐔂���
	// ���ݍĐ����̃A�j���[�V����
	// true:�����Ă��� false:�ҋ@
	bool m_isRun;

	// �v���C���[�̕\���ʒu
	Vec2 m_pos;

	// �v���C���[���������������Ă��邩
	// true:������ false:�E����
	bool m_isDirLeft;

	// �W�����v����
	bool m_isJump;
	float m_jumpSpeed;

	// �_��
	int m_blinkFrameCount;

	// �v���C���[��HP
	int m_hp;

	// ���S���o
	int m_deadFrameCount;
	// �㉺�ړ��̉��o��m_jumpSpeed���g���܂킷

// �W�����v�{�^���̃g���K�[����
// 1�O�̃t���[���ɃW�����v�{�^����������Ă������ǂ���
// ���o���Ă���
	bool m_isLastJumpButton;

	Map& m_map;
};
