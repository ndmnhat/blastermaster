#pragma once
#include "GameObject.h"
#define PORTAL_BBOX_HEIGHT	16
#define PORTAL_BBOX_WIDTH	16
class CPortal : public CGameObject
{
public:
	CPortal();
	int SceneID;
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

