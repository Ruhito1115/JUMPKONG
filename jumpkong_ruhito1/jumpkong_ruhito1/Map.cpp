#include "Map.h"
#include "Player.h"
#include "game.h"
#include "Rect.h"
#include "DxLib.h"
#include <memory>
#include <cassert>

namespace
{
	// マップチップの1つのサイズ
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// マップに敷き詰めるチップの数
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth +1;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight +1;

	//チップの配置情報
	// -1: チップなし 7:床
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,-1,-1,-1,-1},
	};
}

Map::Map():
	m_handle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
}

Map::~Map()
{	
}

void Map::Init(Player* pPlayer)
{
	/*m_pPlayer = pPlayer;*/
		// グラフィックの読み込み
	m_handle = LoadGraph("data/image/map.png");
	assert(m_handle != -1); // 読み込み失敗チェック

	// 読み込んだグラフィックにチップが何個あるかを教えておく
	int graphWidth = 0;
	int graphHeight = 0;
	GetGraphSize(m_handle, &graphWidth, &graphHeight);

	m_graphChipNumX = graphWidth / kChipHeight;
	m_graphChipNumY = graphHeight / kChipHeight;
}

void Map::End()
{
	// グラフィックの解放
	DeleteGraph(m_handle);
}

void Map::Update()
{
}

void Map::Draw()
{

	for (int y = 0; y < kChipNumY; y++)
	{

		for (int x = 0; x < kChipNumX; x++)
		{

			int posX = kChipWidth * x;
			int posY = kChipHeight * y;

			//画面外を描画しない
			if (posX < 0 - kChipWidth) continue;
			if (posX > Game::kScreenWidth) continue;
			if (posY < 0 - kChipHeight) continue;
			if (posY > Game::kScreenHeight) continue;

			if (kChipData[y][x] == 7)//床ブロック
			{
				DrawRectGraph(posX, posY, kChipWidth*1,0, kChipWidth,kChipHeight, m_handle,true,false, false);
				DrawCircle(posX, posY, 4, 0xff0000, false);
			}
		}

	}
	
}

bool Map::IsCol(Rect rect, Rect& chipRect)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		//ここの処理を工夫してもっと処理を早く

		for (int y = 0; y < kChipNumY; y++)
		{
			//壁以外とは当たらない
			if (kChipData[y][x] == -1) continue;

			int chipLeft = kChipWidth * x;
			int chipRight = chipLeft + kChipWidth;
			int chipTop = kChipHeight * y;
			int chipBottom = chipTop + kChipHeight;

			//絶対に当たらないパターンをはじく
			if (chipLeft > rect.right) continue;
			if (chipTop > rect.bottom) continue;
			if (chipRight < rect.left) continue;
			if (chipBottom < rect.top) continue;

			//ぶつかったマップチップの矩形を設定する
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;
			//DrawBox(chipLeft, chipTop, chipRight, chipBottom, 0xff0000, false);

			//いずれかのチップと当たっていたら終了
			printfDx("%d\n", kChipData[y][x]);
			return true;

		}

	}
	//全てのチップをチェックして一つも当たっていなければ当たっていない
	return false;
}

