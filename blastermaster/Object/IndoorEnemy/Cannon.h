#pragma once
#include "IndoorEnemy.h"
#include "..\Bullet\EyeballBullet.h"
#include "..\Bullet\BigJasonBullet.h"
#define CANNON_BULLET_CLIPSIZE		2
#define CANNON_BULLET_RELOADTIME	800

#define CANNON_HEALTH	100
#define CANNON_DAMAGE	100

#define CANNON_BBOX_HEIGHT	26	 
#define CANNON_BBOX_WIDTH	26 

class CCannon : public CIndoorEnemy
{
public:
	int ClipSize;
	bool isShootingVertically = false;
	DWORD reloadingTimeCount;

	CCannon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Fire(int Direction);
};

