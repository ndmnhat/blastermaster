#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"
#define SOPHIA_BULLET_SPEED 0.12f
#define SOPHIA_BULLET_DAMAGE 10
#define SOPHIA_BULLET_RELOADTIME 1000
#define SOPHIA_BULLET_LIFETIME 500
#define SOPHIA_BULLET_CLIPSIZE 3
#define SOPHIA_BULLET_INCLIP_RELOADTIME 10

#define SOPHIA_BULLET_BBOX_WIDTH 10
#define SOPHIA_BULLET_BBOX_HEIGHT 10

#define SOPHIA_BULLET_ANIMATION_SET_ID 41

class CSophiaBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CSophiaBullet();
};

