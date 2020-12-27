#pragma once
#include "..\GameObject.h"
#include "..\Item\Power.h"

enum OutdoorEnemyType {
	Crabullus,
	Dome,
	Floater,
	Insect,
	Jumper,
	Mine,
	Orb1,
	Orb2,
	Skull,
	Worm
};

class COutdoorEnemy : public CGameObject
{
public:
	OutdoorEnemyType enemyType;
	int health;
	int damage;

	COutdoorEnemy();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual int GetSophiaPosInCoobject(std::vector<LPGAMEOBJECT>* coObjects);
};

