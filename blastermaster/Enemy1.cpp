#include "Enemy1.h"

void CEnemy1::Update(DWORD dt)
{
	CGameObject::Update(dt);
	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}
}

void CEnemy1::Render()
{
	if(vx>0)
		animations[ENEMY1_ANI_WALKING_RIGHT]->Render(x,y);
	else
		animations[ENEMY1_ANI_WALKING_LEFT]->Render(x, y);
}