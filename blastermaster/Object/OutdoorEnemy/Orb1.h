#pragma once
#include "OutdoorEnemy.h"

#define ORB_HEALTH				100
#define ORB_DAMAGE				100

#define ORB_MOVING_SPEED		0.1f
#define ORB_TURNING_TIME		150
#define ORB_SPINNING_TIME		200
#define ORB_WAITING_TIME		10000


#define ORB_STATE_MOVING			0
#define ORB_STATE_TURNING			1
#define ORB_STATE_SPINNING			2

#define ORB_ANI_MOVING_LEFT		0
#define ORB_ANI_MOVING_RIGHT	1
#define ORB_ANI_TURNING_LEFT	2
#define ORB_ANI_TURNING_RIGHT	3
#define ORB_ANI_SPINNING		4

#define ORB_BBOX_HEIGHT	18	 
#define ORB_BBOX_WIDTH	18 


class COrb1 : public COutdoorEnemy
{
public:
	DWORD startTurning = 0;
	DWORD startWaiting = 0;
	DWORD startSpinning = 0;

	float speed;
	COrb1();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

