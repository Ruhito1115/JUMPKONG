#pragma once
#include<memory>
#include "Rect.h"

class Player;
class Map
{
public:

	Map();
	 ~Map();


	void Init(Player* pPlayer);   // 初期化
	void End();    // 終了処理

	void Update();
	void Draw();

	//指定した矩形と当たっているか判定
	//参照を使用してぶつかったマップチップの矩形情報を取得する
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
