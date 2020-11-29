#pragma once
#include "OutdoorEnemy.h"


class CCrabullus : public COutdoorEnemy
{
public:
	CCrabullus();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

