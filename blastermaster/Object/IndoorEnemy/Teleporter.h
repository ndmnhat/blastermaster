#pragma once
#include "IndoorEnemy.h"

#define TELEPORTER_BBOX_HEIGHT	32 
#define TELEPORTER_BBOX_WIDTH	24

#define TELEPORTER_ANI_TRANSFORM 0

class CTeleporter : public CIndoorEnemy
{
public:
	CTeleporter();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

