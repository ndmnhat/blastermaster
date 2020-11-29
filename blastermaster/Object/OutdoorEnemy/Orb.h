#pragma once
#include "OutdoorEnemy.h"

#define ORB_BBOX_HEIGHT	18	 
#define ORB_BBOX_WIDTH	18 


class COrb : public COutdoorEnemy
{
public:
	COrb();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

