#pragma once
#include "Enemy.h"

#define ENEMY1_WALKING_SPEED		0.1f

#define ENEMY1_STATE_WALKING_RIGHT	100
#define ENEMY1_STATE_WALKING_LEFT	200

#define ENEMY1_ANI_WALKING_RIGHT	0
#define ENEMY1_ANI_WALKING_LEFT		1

class CEnemy1 : public CEnemy
{
private:
	float nx = 0, ny = 0;
public:
	void Update(DWORD dt);
	void Render();
	void SetState(int state);
	CEnemy1() : CEnemy() { vx = ENEMY1_WALKING_SPEED; };
};

