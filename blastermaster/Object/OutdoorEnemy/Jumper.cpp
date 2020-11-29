#include "Jumper.h"

CJumper::CJumper() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Jumper;
	width = JUMPER_BBOX_WIDTH;
	height = JUMPER_BBOX_HEIGHT;
}

void CJumper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CJumper::Render()
{
}

void CJumper::SetState(int state)
{
	CGameObject::SetState(state);
}
