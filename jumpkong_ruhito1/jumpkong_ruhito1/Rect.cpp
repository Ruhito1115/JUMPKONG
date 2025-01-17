#include "Rect.h"

Vec2 Rect::getCenter()
{
	return Vec2((left + right) / 2, (top + bottom) / 2);
}


bool Rect::isCol(const Rect& rect)
{
	if (top > rect.bottom)	return false;
	if (bottom < rect.top)	return false;
	if (left > rect.right)	return false;
	if (right < rect.left)	return false;

	return true;
}

void Rect::set_TL_Size(Vec2 posTL, Vec2 size)
{
	top = posTL.y;
	bottom = posTL.y + size.y;
	left = posTL.x;
	right = posTL.x + size.x;
}

void Rect::SetRect(Vec2 pos, float width, float height)
{
	bottom = pos.y + height / 2; //‰º
	top = pos.y - height / 2; //ã
	left = pos.x - width / 2; //¶
	right = pos.x + width / 2; //‰E
}
