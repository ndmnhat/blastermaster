#include "Bullet.h"

CBullet::CBullet()
{
	type = TYPE_BULLET;
}

void CBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}