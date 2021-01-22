#pragma once
#include "OutdoorEnemy.h"
#include "..\Effect\SmallBulletExplosion.h"
#include "..\..\Grid\Grid.h"
#include "..\Bullet\JasonBullet.h"
#define ORB_HEALTH				100
#define ORB_DAMAGE				100

#define ORB_MOVING_SPEED		0.05f

#define ORB_ANI_SPINNING		0

#define ORB_BBOX_HEIGHT	18
#define ORB_BBOX_WIDTH	18


class COrb2 : public COutdoorEnemy
{
public:
	int ny;
	COrb2();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

