#include "Floater.h"

CFloater::CFloater() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Floater;
	width = FLOATER_BBOX_WIDTH;
	height = FLOATER_BBOX_HEIGHT;
}

void CFloater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CFloater::Render()
{
}

void CFloater::SetState(int state)
{
	CGameObject::SetState(state);
}
