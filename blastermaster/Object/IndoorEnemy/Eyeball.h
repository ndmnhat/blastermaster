#pragma once
#include "IndoorEnemy.h"

#define EYEBALL_MOVING_SPEED 0.05f

#define EYEBALL_BBOX_HEIGHT	16
#define EYEBALL_BBOX_WIDTH	16 

#define EYEBALL_ANI_MOVING 0
class CEyeball : public CIndoorEnemy
{
public:
	CEyeball();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

