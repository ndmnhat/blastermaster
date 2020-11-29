#include "Skull.h"

CSkull::CSkull() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Skull;
	width = SKULL_BBOX_WIDTH;
	height = SKULL_BBOX_HEIGHT;
}

void CSkull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CSkull::Render()
{
}

void CSkull::SetState(int state)
{
	CGameObject::SetState(state);
}
