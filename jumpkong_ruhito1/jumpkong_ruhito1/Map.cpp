#include "Map.h"
#include "Player.h"
#include "game.h"
#include "Rect.h"
#include "DxLib.h"
#include <memory>
#include <cassert>

namespace
{
	// �}�b�v�`�b�v��1�̃T�C�Y
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	// �}�b�v�ɕ~���l�߂�`�b�v�̐�
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth +1;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight +1;

	//�`�b�v�̔z�u���
	// -1: �`�b�v�Ȃ� 7:��
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
		// �O���t�B�b�N�̓ǂݍ���
	m_handle = LoadGraph("data/image/map.png");
	assert(m_handle != -1); // �ǂݍ��ݎ��s�`�F�b�N

	// �ǂݍ��񂾃O���t�B�b�N�Ƀ`�b�v�������邩�������Ă���
	int graphWidth = 0;
	int graphHeight = 0;
	GetGraphSize(m_handle, &graphWidth, &graphHeight);

	m_graphChipNumX = graphWidth / kChipHeight;
	m_graphChipNumY = graphHeight / kChipHeight;
}

void Map::End()
{
	// �O���t�B�b�N�̉��
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

			//��ʊO��`�悵�Ȃ�
			if (posX < 0 - kChipWidth) continue;
			if (posX > Game::kScreenWidth) continue;
			if (posY < 0 - kChipHeight) continue;
			if (posY > Game::kScreenHeight) continue;

			if (kChipData[y][x] == 7)//���u���b�N
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
		//�����̏������H�v���Ă����Ə����𑁂�

		for (int y = 0; y < kChipNumY; y++)
		{
			//�ǈȊO�Ƃ͓�����Ȃ�
			if (kChipData[y][x] == -1) continue;

			int chipLeft = kChipWidth * x;
			int chipRight = chipLeft + kChipWidth;
			int chipTop = kChipHeight * y;
			int chipBottom = chipTop + kChipHeight;

			//��΂ɓ�����Ȃ��p�^�[�����͂���
			if (chipLeft > rect.right) continue;
			if (chipTop > rect.bottom) continue;
			if (chipRight < rect.left) continue;
			if (chipBottom < rect.top) continue;

			//�Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;
			//DrawBox(chipLeft, chipTop, chipRight, chipBottom, 0xff0000, false);

			//�����ꂩ�̃`�b�v�Ɠ������Ă�����I��
			printfDx("%d\n", kChipData[y][x]);
			return true;

		}

	}
	//�S�Ẵ`�b�v���`�F�b�N���Ĉ���������Ă��Ȃ���Γ������Ă��Ȃ�
	return false;
}

