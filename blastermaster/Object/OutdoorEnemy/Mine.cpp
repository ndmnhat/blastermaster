#include "Mine.h"

CMine::CMine()
{
	enemyType = OutdoorEnemyType::Mine;
}

void CMine::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CMine::Render()
{
}

void CMine::SetState(int state)
{
	CGameObject::SetState(state);
}
