#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"

#define CANNON_BULLET_SPEED 0.03f
#define CANNON_BULLET_DAMAGE 10
#define CANNON_BULLET_RELOADTIME 1000
#define CANNON_BULLET_LIFETIME 500
#define CANNON_BULLET_CLIPSIZE 1
#define CANNON_BULLET_INCLIP_RELOADTIME 1000
#define CANNON_BULLET_BBOX_WIDTH 8
#define CANNON_BULLET_BBOX_HEIGHT 8
#define CANNON_BULLET_ANIMATION_SET_ID 44

class CCannonBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CCannonBullet();
};
