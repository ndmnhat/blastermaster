#pragma once
#include "OutdoorEnemy.h"

#define INSECT_FLYING_SPEED_X		0.02f
#define INSECT_FLYING_DOWN_SPEED	0.04f
#define INSECT_FLYING_UP_SPEED		0.045f
#define INSECT_SPEED_VARIATION		0.001f


#define INSECT_ANI_FLYING_LEFT		0
#define INSECT_ANI_FLYING_RIGHT		1

#define INSECT_BBOX_HEIGHT	18	 
#define INSECT_BBOX_WIDTH	18 

class CInsect : public COutdoorEnemy
{
public:
	int ny;
	float velVariation;
	CInsect();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

