#include "Portal.h"

CPortal::CPortal()
{
	type = TYPE_PORTAL;
}

void CPortal::Render()
{
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + PORTAL_BBOX_WIDTH;
	bottom = top - PORTAL_BBOX_HEIGHT;
}
