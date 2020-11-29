#pragma once
#include "OutdoorEnemy.h"

#define FLOATER_BBOX_HEIGHT	16	 
#define FLOATER_BBOX_WIDTH	18 

class CFloater : public COutdoorEnemy
{
public:
	CFloater();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

