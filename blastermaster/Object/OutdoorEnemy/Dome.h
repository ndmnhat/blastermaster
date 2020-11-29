#pragma once
#include "OutdoorEnemy.h"

#define DOME_BBOX_HEIGHT	18	 
#define DOME_BBOX_WIDTH		18 

class CDome : public COutdoorEnemy
{
public:
	CDome();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

