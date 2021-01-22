#pragma once
#include "Item.h"
//#include "..\..\Sound\Sound.h"
#define POWER_GRAVITY 0.0005f
#define POWER_BBOX_HEIGHT 16
#define POWER_BBOX_WIDTH 16
#define POWER_ANIMATION_ID 2201
#define POWER_STATE_CONSUMED 1

class CPower : public CItem
{
public:
	CPower();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state);
};

