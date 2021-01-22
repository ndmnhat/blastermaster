#pragma once
#include "IndoorEnemy.h"
#include "..\Bullet\EyeballBullet.h"
#include "..\Player\BigJason.h"
#define PI						3.14159265f

#define EYEBALL_HEALTH			100
#define EYEBALL_DAMAGE			10

#define EYEBALL_MOVING_SPEED	0.05f

#define EYEBALL_BBOX_HEIGHT		16
#define EYEBALL_BBOX_WIDTH		16 

#define EYEBALL_ANI_MOVING 0

class CEyeball : public CIndoorEnemy
{
public:
	int ClipSize;
	DWORD reloadingTimeCount;
	CEyeball();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Fire(int Direction);
};

