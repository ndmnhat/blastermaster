#pragma once
#include "..\GameObject.h"

enum OutdoorEnemyType {
	Crabullus,
	Dome,
	Floater,
	Insect,
	Jumper,
	Mine,
	Orb,
	Skull,
	Worm
};

class COutdoorEnemy : public CGameObject
{
public:
	OutdoorEnemyType enemyType;

	COutdoorEnemy();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render() = 0;
	virtual void SetState(int state);
};

