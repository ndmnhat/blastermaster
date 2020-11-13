#include "OutdoorEnemy.h"

COutdoorEnemy::COutdoorEnemy()
{
	type = ObjectType::ENEMY;
}

void COutdoorEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void COutdoorEnemy::SetState(int state)
{
	CGameObject::SetState(state);
}
