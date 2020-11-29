#pragma once
#include "..\..\GameObject.h"

enum IndoorEnemyType {
	Cannon,
	Eyeball,
	Teleporter
};


class CIndoorEnemy : public CGameObject
{
public:
	CIndoorEnemy() : CGameObject() {};
};


