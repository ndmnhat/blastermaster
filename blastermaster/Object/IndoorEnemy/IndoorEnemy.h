#pragma once
#include "..\GameObject.h"

enum IndoorEnemyType {
	Cannon,
	Eyeball,
	Teleporter
};


class CIndoorEnemy : public CGameObject
{
public:
	//CIndoorEnemy() : CGameObject() {};

	IndoorEnemyType enemyType;
	int health;
	int damage;

	CIndoorEnemy();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};


