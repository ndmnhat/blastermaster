#include "Fence.h"

CFence::CFence()
{
	this->type = TYPE_FENCE;
}

void CFence::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void CFence::Render()
{
	//RenderBoundingBox();
}

void CFence::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}
