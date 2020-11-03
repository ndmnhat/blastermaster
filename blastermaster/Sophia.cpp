#include "Sophia.h"

void CSophia::Update(DWORD dt)
{
	CGameObject::Update(dt);

	// simple fall down
	vy += SOPHIA_GRAVITY;
	if (y > 1170) 
	{
		vy = 0; y = 1170.0f;
	}

	// simple screen edge collision!!!
	//if (vx > 0 && x > 290) x = 290;
	//if (vx < 0 && x < 0) x = 0;
}

void CSophia::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx>0) ani = SOPHIA_ANI_IDLE_RIGHT;
		else ani = SOPHIA_ANI_IDLE_LEFT;
	}
	else if (vx > 0) 
		ani = SOPHIA_ANI_WALKING_RIGHT;
	else ani = SOPHIA_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void CSophia::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOPHIA_STATE_WALKING_RIGHT:
		vx = SOPHIA_WALKING_SPEED;
		nx = 1;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		vx = -SOPHIA_WALKING_SPEED;
		nx = -1;
		break;
	case SOPHIA_STATE_JUMP:
		/*if (y==100)*/
			vy = -SOPHIA_JUMP_SPEED_Y;

	case SOPHIA_STATE_IDLE:
		vx = 0;
		break;
	}
}

