#include "Worm.h"

CWorm::CWorm() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Worm;
	nx = -1;
	width = WORM_BBOX_WIDTH;
	height = WORM_BBOX_HEIGHT;
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CWorm::SetState(int state)
{
	CGameObject::SetState(state);
}

void CWorm::Render()
{

}
