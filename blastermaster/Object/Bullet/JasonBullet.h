#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"

#define JASON_BULLET_SPEED 0.08f
#define JASON_BULLET_DAMAGE 10
#define JASON_BULLET_RELOADTIME 1000
#define JASON_BULLET_LIFETIME 500
#define JASON_BULLET_CLIPSIZE 3
#define JASON_BULLET_INCLIP_RELOADTIME 10

#define JASON_BULLET_BBOX_WIDTH 4
#define JASON_BULLET_BBOX_HEIGHT 4

#define JASON_BULLET_ANIMATION_SET_ID 42

class CJasonBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CJasonBullet();
};

