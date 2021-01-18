#include "WallImage.h"

CWallImage::CWallImage()
{
	this->type = TYPE_WALLIMAGE;
}

void CWallImage::Render()
{
	image->Draw(x, y, 255);
	//RenderBoundingBox();
}

void CWallImage::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top - height;
}

void CWallImage::SetSize(int width, int height)
{
	this->width = width;
	this->height = height;
}