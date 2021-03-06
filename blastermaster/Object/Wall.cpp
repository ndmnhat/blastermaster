#include "Wall.h"

CWall::CWall()
{
	this->type = TYPE_WALL;
}

void CWall::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void CWall::Render()
{
	//RenderBoundingBox();
}

void CWall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}
