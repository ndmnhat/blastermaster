#pragma once
#include "Enemy.h"

#define ENEMY2_WALKING_SPEED		0.15f

#define ENEMY2_STATE_WALKING_RIGHT	100
#define ENEMY2_STATE_WALKING_LEFT	200

#define ENEMY2_ANI_WALKING_RIGHT	0
#define ENEMY2_ANI_WALKING_LEFT		1

class CEnemy2 : public CEnemy
{
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	CEnemy2() : CEnemy() { vx = ENEMY2_WALKING_SPEED; };
};

