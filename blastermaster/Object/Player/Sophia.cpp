#include "Sophia.h"

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	// simple fall down
	if (isFalling == true) 
	{
		vy -= SOPHIA_GRAVITY * dt;
	}
	

	UpdateStateTime();

	vector<LPGAMEOBJECT> listObject;
	listObject.clear();
	for (UINT i = 0; i < coObjects->size(); i++)
	{
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(&listObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.1f; // nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->obj->type == ObjectType::ENEMY)
			{
				if (isUntouchable)
				{
					if (e->nx != 0)
						x += dx;
					if (e->ny != 0)
						y += dy;
				}
				else
					SetState(SOPHIA_STATE_ATTACKED);
			}
		}
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
		if (nx > 0)
			ani = SOPHIA_ANI_IDLE_RIGHT;
		else
			ani = SOPHIA_ANI_IDLE_LEFT;
	}
	else if (vx > 0)
		ani = SOPHIA_ANI_WALKING_RIGHT;
	else
		ani = SOPHIA_ANI_WALKING_LEFT;

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
		//if (y==100)
		vy = SOPHIA_JUMP_SPEED_Y;
		break;
	case SOPHIA_STATE_ATTACKED:
		vx = -0.1f * nx;
		StartUntouchable();
		break;
	case SOPHIA_STATE_IDLE:
		vx = 0;
		break;
	}
}

void CSophia::UpdateStateTime()
{
	if (isUntouchable && (GetTickCount() - untouchableStart > SOPHIA_UNTOUCHABLE_TIME))
	{
		untouchableStart = 0;
		isUntouchable = false;
	}
}

void CSophia::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + SOPHIA_BBOX_WIDTH;
	bottom = top + SOPHIA_BBOX_HEIGHT;
}
