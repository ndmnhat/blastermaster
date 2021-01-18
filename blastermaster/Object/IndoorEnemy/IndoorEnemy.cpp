#include "IndoorEnemy.h"


CIndoorEnemy::CIndoorEnemy()
{
	type = TYPE_ENEMY;
}

void CIndoorEnemy::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	right = left + width;
	top = y;
	bottom = top - height;
}

void CIndoorEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
}

void CIndoorEnemy::Render()
{
}

void CIndoorEnemy::SetState(int state)
{
	CGameObject::SetState(state);
}