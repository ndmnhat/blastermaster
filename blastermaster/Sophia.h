#pragma once
#include "GameObject.h"

#define SOPHIA_WALKING_SPEED	0.1f
#define SOPHIA_JUMP_SPEED_Y		0.5f
#define SOPHIA_GRAVITY			0.1f
		
#define SOPHIA_STATE_IDLE			0
#define SOPHIA_STATE_WALKING_RIGHT	100
#define SOPHIA_STATE_WALKING_LEFT	200
#define SOPHIA_STATE_JUMP			300

#define SOPHIA_ANI_IDLE_LEFT		0
#define SOPHIA_ANI_IDLE_RIGHT		1
#define SOPHIA_ANI_WALKING_LEFT		2
#define SOPHIA_ANI_WALKING_RIGHT	3


class CSophia : public CGameObject
{
public: 

	void Update(DWORD dt);
	void Render();
	void SetState(int state);
};