#include "Lava.h"

CLava::CLava()
{
	this->type = TYPE_LAVA;
}

void CLava::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void CLava::Render()
{
	//RenderBoundingBox();
}

void CLava::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}
