#pragma once
#include "OutdoorEnemy.h"

#define SKULL_BBOX_HEIGHT	21
#define SKULL_BBOX_WIDTH	18


class CSkull : public COutdoorEnemy
{
public:
	CSkull();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

