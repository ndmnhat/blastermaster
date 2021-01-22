#include "BossWall.h"

CBossWall::CBossWall()
{
	this->type = TYPE_BOSSWALL;
}

void CBossWall::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void CBossWall::Render()
{
	//RenderBoundingBox();
}

void CBossWall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}
