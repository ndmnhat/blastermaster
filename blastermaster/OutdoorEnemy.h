#pragma once
#include "GameObject.h"

enum OutdoorEnemyType {
	Crabullus,
	Dome,
	Floater,
	Insect,
	Jumper,
	Mine,
	Orb,
	Ship,
	Skull,
	Worm
};

class COutdoorEnemy : public CGameObject
{
public:
	COutdoorEnemy();


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() = 0;
	virtual void SetState(int state);
};

