#include "Power.h"

CPower::CPower()
{
	type = TYPE_ITEM;
	SetAnimation(CAnimations::GetInstance()->Get(POWER_ANIMATION_ID));
}

void CPower::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	//vy -= POWER_GRAVITY * dt;

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i) == NULL)
				continue;
		}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(listObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}

	else
	{
		float min_tx, min_ty, nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			switch (e->obj->type)
			{
			case TYPE_WALL:
			{
				x += min_tx * dx + e->nx * 0.1f;
				y += min_ty * dy + e->ny * 0.1f;

				if (e->nx != 0) vx = 0;
				if (e->ny != 0) vy = 0;
			}
			break;
			default: break;
			}
		}
	}
#pragma region Colliding with object handle

	for (UINT i = 0; i < listObject->size(); i++)
	{
		float space;
		int direction;
		if (isCollidingWith(listObject->at(i), space, direction))
		{
			switch (listObject->at(i)->type)
			{
			case TYPE_WALL:
			{
				if (direction == 0)
				{
					y -= space;
					vy = 0;
				}
				else
				{
					x -= space;
					vx = 0;
				}
			}
			break;
			default: break;
			}
		}
	}
}

void CPower::Render()
{
	animation->Render(x, y);
	RenderBoundingBox();
}

void CPower::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + POWER_BBOX_WIDTH;
	bottom = top - POWER_BBOX_HEIGHT;
}

void CPower::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case POWER_STATE_CONSUMED:
		isDestroyed = true;
		break;
	default: break;
	}
}
