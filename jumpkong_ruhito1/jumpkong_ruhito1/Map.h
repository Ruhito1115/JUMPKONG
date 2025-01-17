#pragma once
#include<memory>
#include "Rect.h"

class Player;
class Map
{
public:

	Map();
	 ~Map();


	void Init(Player* pPlayer);   // ������
	void End();    // �I������

	void Update();
	void Draw();

	//�w�肵����`�Ɠ������Ă��邩����
	//�Q�Ƃ��g�p���ĂԂ������}�b�v�`�b�v�̋�`�����擾����
	bool IsCol(Rect rect, Rect& chipRect);
	
private:
	

	int m_handle;
	int m_graphChipNumX;
	int m_graphChipNumY;

	int m_bgHandle;
	int m_moveHandle;
	int m_dashHandle;
	int m_jumpHandle;
	int m_getHandle;

};
