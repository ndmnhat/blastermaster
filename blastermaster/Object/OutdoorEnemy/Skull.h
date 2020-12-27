#pragma once
#include "OutdoorEnemy.h"
#include "..\Bullet\Bullet.h"
#include "..\Bullet\SophiaBullet.h"
#include "..\Bullet\SkullBullet.h"

#define SKULL_HEALTH				100
#define SKULL_DAMAGE				100

#define SKULL_MOVING_SPEED			0.08f
#define SKULL_ATTACKING_TIME		1000
#define SKULL_STATE_MOVING			0
#define SKULL_STATE_ATTACKING		1

#define SKULL_ANI_MOVING_LEFT		0
#define SKULL_ANI_MOVING_RIGHT		1
#define SKULL_ANI_ATTACKING_LEFT	2
#define SKULL_ANI_ATTACKING_RIGHT	3
#define SKULL_ANI_BULLETS_LEFT		4
#define SKULL_ANI_BULLETS_RIGHT		5

#define SKULL_BBOX_HEIGHT	21
#define SKULL_BBOX_WIDTH	18


class CSkull : public COutdoorEnemy
{
public:
	DWORD startAttacking = 0;
	BulletType currentBulletType;
	CSkull();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void Fire(float Direction, int nx);
};

