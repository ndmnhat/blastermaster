#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"

#define BOSS_BULLET_SPEED 0.03f
#define BOSS_BULLET_DAMAGE 10
#define BOSS_BULLET_RELOADTIME 1000
#define BOSS_BULLET_LIFETIME 500
#define BOSS_BULLET_CLIPSIZE 1
#define BOSS_BULLET_INCLIP_RELOADTIME 1000
#define BOSS_BULLET_BBOX_WIDTH 9
#define BOSS_BULLET_BBOX_HEIGHT 9
#define BOSS_BULLET_ANIMATION_SET_ID 45

class CBossBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CBossBullet();
};

