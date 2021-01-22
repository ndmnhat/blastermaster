#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"
#include "..\..\Sound\Sound.h"

#define SKULL_BULLET_SPEED				0.05f
#define SKULL_BULLET_DAMAGE				10
#define SKULL_BULLET_LIFETIME			1000
#define SKULL_BULLET_BOUNCING_SPEED		0.05f
#define SKULL_BULLET_MOVING_SPEED		0.025f
#define SKULL_BULLET_GRAVITY			0.0005f


#define SKULL_BULLET_STATE_BOUNCING		0

#define SKULL_BULLET_BBOX_WIDTH		10
#define SKULL_BULLET_BBOX_HEIGHT	10

#define SKULL_BULLET_ANIMATION_SET_ID	43

class CSkullBullet: public CBullet
{
public:
	bool isBouncing = false;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CSkullBullet(int nx);
};

