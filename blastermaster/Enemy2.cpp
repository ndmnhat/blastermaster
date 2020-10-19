#include "Enemy2.h"

void CEnemy2::Update(DWORD dt)
{
	CGameObject::Update(dt);
	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}
}

void CEnemy2::Render()
{
	if (vx > 0)
		animations[ENEMY2_ANI_WALKING_RIGHT]->Render(x, y);
	else
		animations[ENEMY2_ANI_WALKING_LEFT]->Render(x, y);
}