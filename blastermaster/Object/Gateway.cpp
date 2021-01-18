#include "Gateway.h"

CGateway::CGateway()
{
	this->type = TYPE_GATEWAY;
}

void CGateway::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}

void CGateway::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

void CGateway::Render()
{
	RenderBoundingBox();
}
