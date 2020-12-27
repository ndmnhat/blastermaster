#pragma once
#include "OutdoorEnemy.h"

#define INSECT_BBOX_HEIGHT	18	 
#define INSECT_BBOX_WIDTH	18 

class CInsect : public COutdoorEnemy
{
public:
	CInsect();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

