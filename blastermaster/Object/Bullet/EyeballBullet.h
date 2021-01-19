#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"

#define EYEBALL_BULLET_SPEED		0.05f
#define EYEBALL_BULLET_DAMAGE		10
#define EYEBALL_BULLET_RELOADTIME	2000
#define EYEBALL_BULLET_LIFETIME		1500
#define EYEBALL_BULLET_CLIPSIZE		1

#define EYEBALL_BULLET_INCLIP_RELOADTIME	1000
#define EYEBALL_BULLET_BBOX_WIDTH			4
#define EYEBALL_BULLET_BBOX_HEIGHT			4

#define EYEBALL_BULLET_ANIMATION_SET_ID		140

class CEyeballBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CEyeballBullet();
};

