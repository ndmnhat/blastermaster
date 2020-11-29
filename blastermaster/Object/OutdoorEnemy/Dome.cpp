#include "Dome.h"

CDome::CDome() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Dome;
	width = DOME_BBOX_WIDTH;
	height = DOME_BBOX_HEIGHT;
}

void CDome::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CDome::Render()
{
}

void CDome::SetState(int state)
{
	CGameObject::SetState(state);
}
