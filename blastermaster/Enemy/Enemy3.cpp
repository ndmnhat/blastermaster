#include "Enemy3.h"

void CEnemy3::Update(DWORD dt)
{
	CGameObject::Update(dt);
	if (vx > 0 && x > 290) {
		x = 290; vx = -vx;
	}
	if (vx < 0 && x < 0) {
		x = 0; vx = -vx;
	}
}

void CEnemy3::Render()
{
	if (vx > 0)
		animations[ENEMY3_ANI_WALKING_RIGHT]->Render(x, y);
	else
		animations[ENEMY3_ANI_WALKING_LEFT]->Render(x, y);
}