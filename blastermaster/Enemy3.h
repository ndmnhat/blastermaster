#pragma once
#include "Enemy.h"

#define ENEMY3_WALKING_SPEED		0.2f
			 
#define ENEMY3_STATE_WALKING_RIGHT	100
#define ENEMY3_STATE_WALKING_LEFT	200
			 
#define ENEMY3_ANI_WALKING_RIGHT	0
#define ENEMY3_ANI_WALKING_LEFT		1

class CEnemy3 : public CEnemy
{
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	CEnemy3() : CEnemy() { vx = ENEMY3_WALKING_SPEED; };
};

