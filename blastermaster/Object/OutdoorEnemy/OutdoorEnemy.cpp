#include "OutdoorEnemy.h"

COutdoorEnemy::COutdoorEnemy()
{
	type = TYPE_ENEMY;
}

void COutdoorEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void COutdoorEnemy::SetState(int state)
{
	CGameObject::SetState(state);
}
