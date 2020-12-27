#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"

#define FLOATER_BULLET_SPEED 0.1f
#define FLOATER_BULLET_DAMAGE 10
#define FLOATER_BULLET_RELOADTIME 1000
#define FLOATER_BULLET_LIFETIME 500
#define FLOATER_BULLET_CLIPSIZE 1

#define FLOATER_BULLET_INCLIP_RELOADTIME 1000
#define FLOATER_BULLET_BBOX_WIDTH 4
#define FLOATER_BULLET_BBOX_HEIGHT 4

#define FLOATER_BULLET_ANIMATION_SET_ID 42

class CFloaterBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CFloaterBullet();
};

