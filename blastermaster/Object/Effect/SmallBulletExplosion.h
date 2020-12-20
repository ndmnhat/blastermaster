#pragma once
#include "Effect.h"

#define SMALL_BULLET_EXLOSION_ANI_ID 2005
#define SMALL_BULLET_EXLOSION_BBOX_HEIGHT 10;
#define SMALL_BULLET_EXLOSION_BBOX_WIDTH 10;
class CSmallBulletExplosion : public CEffect
{
public:
	CSmallBulletExplosion();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
};

