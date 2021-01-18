#include "Jumper.h"

CJumper::CJumper() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Jumper;
	width = JUMPER_BBOX_WIDTH;
	height = JUMPER_BBOX_HEIGHT;
	health = JUMPER_HEALTH;
	damage = JUMPER_DAMAGE;
	nx = -1;
}

void CJumper::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy -= JUMPER_GRAVITY * dt;
	vx = JUMPER_WALKING_SPEED * nx;

	if (coObjects != NULL)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == TYPE_SOPHIA)
			{
				if (abs(this->x - coObjects->at(i)->x) <= 40)
				{
					if (isJumping == false)
					{
						vy = JUMPER_JUMPING_SPEED;
						isJumping = true;
					}
				}
				if (this->x - coObjects->at(i)->x > 70)
					nx = -1;
				if (this->x - coObjects->at(i)->x < -70)
					nx = 1;
			}
		}
	}
	CGameObject::Update(dt);
	

	
	
	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_JUMPER)
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
				x += min_tx * dx + e->nx * 0.1f;
				y += min_ty * dy + e->ny * 0.1f;

				if (e->nx != 0) vx = 0;
				if (e->ny != 0)
				{
						isJumping = false;
				}
				break;
			case TYPE_SOPHIA: case TYPE_ENEMY:
				x += dx;
				y += dy;
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

void CJumper::Render()
{
	int ani;
	if (isJumping == true) {
		if (nx > 0)
			ani = JUMPER_ANI_JUMPING_RIGHT;
		else if (nx < 0)
			ani = JUMPER_ANI_JUMPING_LEFT;
	}
	else {
		if (nx > 0)
			ani = JUMPER_ANI_WALKING_RIGHT;
		else if (nx < 0)
			ani = JUMPER_ANI_WALKING_LEFT;
	}

	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();

}

void CJumper::SetState(int state)
{
	CGameObject::SetState(state);
}
