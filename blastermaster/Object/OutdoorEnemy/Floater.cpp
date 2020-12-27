#include "Floater.h"

CFloater::CFloater() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Floater;
	width = FLOATER_BBOX_WIDTH;
	height = FLOATER_BBOX_HEIGHT;
	health = FLOATER_HEALTH;
	damage = FLOATER_DAMAGE;
	nx = 1;
	ny = 1;
}

void CFloater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = FLOATER_FLYING_SPEED_Y * ny;
	vx = FLOATER_FLYING_SPEED_X * nx;


	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_FLOATER)
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
							if (e->nx < 0)
								this->nx = -1;
							else
								this->nx = 1;
						}
						if (e->ny != 0)
							if (e->ny < 0)
								this->ny = -1;
							else
								this->ny = 1;
					}
					break;
				case TYPE_SOPHIA:
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
					//velVariation *= -1;
				}
				else
				{
					x -= space;
					vx = 0;
					//nx *= -1;
				}

			}
		}
	}

	//#pragma endregion
	//
		/* simple screen edge collision!!!
		if (vx > 0 && x > 290) x = 290;
		if (vx < 0 && x < 0) x = 0;*/
		//DebugOut(L"Pos: %.2f ,%.2f\n", x, y);
}

void CFloater::Render()
{
	int ani;
	if (nx > 0)
		ani = FLOATER_ANI_FLYING_RIGHT;
	else
		ani = FLOATER_ANI_FLYING_LEFT;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CFloater::SetState(int state)
{
	CGameObject::SetState(state);
}
