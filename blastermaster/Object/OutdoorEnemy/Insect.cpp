#include "Insect.h"

CInsect::CInsect() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Insect;
	width = INSECT_BBOX_WIDTH;
	height = INSECT_BBOX_HEIGHT;
	health = INSECT_HEALTH;
	damage = INSECT_DAMAGE;
	nx = -1;
	velVariation = INSECT_SPEED_VARIATION;
	
}

void CInsect::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = INSECT_FLYING_SPEED_X * nx;
	//vy = INSECT_FLYING_UP_SPEED;
	vy += velVariation;
	if (vy >= INSECT_FLYING_UP_SPEED || vy <= -INSECT_FLYING_DOWN_SPEED) {
		velVariation *= -1;
	}
	CGameObject::Update(dt);
	
	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_INSECT)
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

				if (e->nx != 0)
						this->nx *= -1;
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
	//DebugOut(L"Insect x: %f y: %f\n", this->x, this->y);
}

void CInsect::Render()
{
	int ani;
	if (nx > 0)
		ani = INSECT_ANI_FLYING_RIGHT;
	else 
		ani = INSECT_ANI_FLYING_LEFT;
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CInsect::SetState(int state)
{
	CGameObject::SetState(state);
}
