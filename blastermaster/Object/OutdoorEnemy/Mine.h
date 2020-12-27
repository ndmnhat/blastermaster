#pragma once
#include "OutdoorEnemy.h"


class CMine : public COutdoorEnemy
{
public:
	CMine();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

