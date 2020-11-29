#include "Orb.h"

COrb::COrb() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Orb;
	width = ORB_BBOX_WIDTH;
	height = ORB_BBOX_HEIGHT;
}

void COrb::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void COrb::Render()
{
}

void COrb::SetState(int state)
{
	CGameObject::SetState(state);
}
