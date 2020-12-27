#include "Insect.h"

CInsect::CInsect() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Insect;
	width = INSECT_BBOX_WIDTH;
	height = INSECT_BBOX_HEIGHT;
}

void CInsect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CInsect::Render()
{
}

void CInsect::SetState(int state)
{
	CGameObject::SetState(state);
}
