#pragma once
#include "Bullet.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"

#define BIGJASON_BULLET_SPEED 0.12f
#define BIGJASON_BULLET_DAMAGE 10
#define BIGJASON_BULLET_RELOADTIME 1000
#define BIGJASON_BULLET_LIFETIME 500
#define BIGJASON_BULLET_CLIPSIZE 3
#define BIGJASON_BULLET_INCLIP_RELOADTIME 10

#define BIGJASON_BULLET_BBOX_WIDTH 8
#define BIGJASON_BULLET_BBOX_HEIGHT 8

#define BIGJASON_BULLET_ANIMATION_SET_ID 49
class CBigJasonBullet : public CBullet
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CBigJasonBullet();
};

