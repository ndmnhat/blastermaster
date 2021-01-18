#include "Orb1.h"

COrb1::COrb1() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Orb1;
	width = ORB_BBOX_WIDTH;
	height = ORB_BBOX_HEIGHT;
	health = ORB_HEALTH;
	damage = ORB_DAMAGE;
	nx = -1;
	SetState(ORB_STATE_MOVING);
	startWaiting = GetTickCount();
}

void COrb1::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ORB_STATE_TURNING && GetTickCount() - startTurning > ORB_TURNING_TIME) {
		startTurning = 0;
		SetState(ORB_STATE_MOVING);
	}

	if (state == ORB_STATE_SPINNING && GetTickCount() - startSpinning > ORB_SPINNING_TIME) {
		startSpinning = 0;
		SetState(ORB_STATE_MOVING);
		startWaiting = GetTickCount();
	}

	if (state == ORB_STATE_MOVING && GetTickCount() - startWaiting > ORB_WAITING_TIME) {
		SetState(ORB_STATE_SPINNING);
	}


	switch (state) {
	case ORB_STATE_MOVING: case ORB_STATE_TURNING:
		vx = ORB_MOVING_SPEED * nx;
		vy = 0;
		break;
	case ORB_STATE_SPINNING:
		vx = 0;
		vy = -ORB_MOVING_SPEED;
		break;
	}
	CGameObject::Update(dt);

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_ORB_1)
				listObject->push_back(coObjects->at(i));
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

				if (e->nx != 0) {
					this->SetState(ORB_STATE_TURNING);
					if (e->nx > 0)
						this->nx = 1;
					if (e->nx < 0)
						this->nx = -1;
				}

				if (e->ny != 0) vy = 0;
			}
			break;
			case TYPE_SOPHIA: case TYPE_ENEMY:
				x += dx;
				y += dy;
				break;
			default:
				break;
			}
		}
	}

#pragma region Colliding with wall handle

	for (UINT i = 0; i < listObject->size(); i++)
	{
		if (listObject->at(i)->type == TYPE_WALL)
		{
			float space;
			int direction;
			if (isCollidingWith(listObject->at(i), space, direction))
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
		}
	}
}

void COrb1::Render()
{
	int ani;
	switch (state)
	{
	case ORB_STATE_MOVING:
		if (nx < 0)
			ani = ORB_ANI_MOVING_LEFT;
		else
			ani = ORB_ANI_MOVING_RIGHT;
		break;
	case ORB_STATE_TURNING:
		if (nx < 0) 
			ani = ORB_ANI_TURNING_LEFT;
		else 
			ani = ORB_ANI_TURNING_RIGHT;
		break;
	case ORB_STATE_SPINNING:
		ani = ORB_ANI_SPINNING;
		break;
	default:
		break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void COrb1::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case ORB_STATE_TURNING:
		startTurning = GetTickCount();
		break;	
	case ORB_STATE_SPINNING:
		startSpinning = GetTickCount();
		break;
	default:
		break;
	}
}
