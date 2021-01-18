#pragma once
#include "IndoorEnemy.h"

#define CANNON_ANI_LEFT		0
#define CANNON_ANI_RIGHT	1

#define CANNON_BBOX_HEIGHT	26	 
#define CANNON_BBOX_WIDTH	26 

class CCannon : public CIndoorEnemy
{
	int ny;
public:
	CCannon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

