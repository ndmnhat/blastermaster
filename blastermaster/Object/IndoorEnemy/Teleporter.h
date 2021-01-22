#pragma once
#include "IndoorEnemy.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "..\Bullet\BigJasonBullet.h"
#define TELEPORTER_HEALTH	100
#define TELEPORTER_DAMAGE	100


#define TELEPORTER_BBOX_HEIGHT	32
#define TELEPORTER_BBOX_WIDTH	24

#define TELEPORTER_TRANSFORMING_TIME	500		//thoi gian trong trang thai bien hinh
#define TELEPORTER_TELEPORTING_TIME		2000	//thoi gian trong trang thai dich chuyen
#define TELEPORTER_TELEPORTING_GAP_TIME	500		//thoi gian giua moi lan dich chuyen
#define TELEPORTER_IDLE_TIME			3000	//thoi gian bat dong


#define TELEPORTER_STATE_IDLE		0	
#define TELEPORTER_STATE_TRANSFORM	1	//trang thai bien hinh
#define TELEPORTER_STATE_TELEPORT	2

#define TELEPORTER_ANI_IDLE			0
#define TELEPORTER_ANI_TRANSFORM	1
#define TELEPORTER_ANI_TELEPORT		2

class CTeleporter : public CIndoorEnemy
{
public:
	CTeleporter();
	DWORD transformTimeCount;
	DWORD teleportTimeCount;
	int teleportCount = 1;
	DWORD teleportGapTimeCount;
	DWORD idleTimeCount;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

