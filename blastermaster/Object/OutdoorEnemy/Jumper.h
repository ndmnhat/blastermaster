#pragma once
#include "OutdoorEnemy.h"

#define JUMPER_BBOX_HEIGHT	26	 
#define JUMPER_BBOX_WIDTH	17 

class CJumper : public COutdoorEnemy
{
public:
	CJumper();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

