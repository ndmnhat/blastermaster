#include "Teleporter.h"

CTeleporter::CTeleporter()
{
	enemyType = IndoorEnemyType::Teleporter;
	width = TELEPORTER_BBOX_WIDTH;
	height = TELEPORTER_BBOX_HEIGHT;
	this->x = x;
	this->y = y;
}

void CTeleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	//vy = -WORM_GRAVITY;
	//vx = WORM_WALKING_SPEED * nx;

	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == TYPE_SOPHIA)
			{
				if (this->x - coObjects->at(i)->x >= 30)
				{
					nx = -1;
				}
				else if (this->x - coObjects->at(i)->x < -30)
				{
					nx = 1;
				}
			}
		}

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_TELEPORTER)
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
				if (e->ny != 0) vy = 0;

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

void CTeleporter::Render()
{
	int ani;
	if (nx > 0) {
		ani = TELEPORTER_ANI_TRANSFORM;
	}
	animation_set->at(ani)->Render(x, y);
}

void CTeleporter::SetState(int state)
{
	CGameObject::SetState(state);
}

void CTeleporter::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	CIndoorEnemy::GetBoundingBox(left, top, right, bottom);
}
