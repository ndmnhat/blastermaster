#include "OutdoorEnemy.h"

COutdoorEnemy::COutdoorEnemy()
{
	type = TYPE_ENEMY;
}

void COutdoorEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = left + width;
	top = y;
	bottom = top - height;
}

void COutdoorEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void COutdoorEnemy::Render()
{
}

void COutdoorEnemy::SetState(int state)
{
	CGameObject::SetState(state);
}
