#include "Worm.h"

CWorm::CWorm() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Worm;
	this->x = x;
	this->y = y;
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

//	simple fall down
//	if (isFalling == true) 
//	{
	vy -= WORM_GRAVITY * dt;
//	}
//
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == TYPE_SOPHIA)
			{
				if (coObjects->at(i)->x < this->x) 
				{
					this->vx = -WORM_WALKING_SPEED;
				}
				else
				{
					this->vx = WORM_WALKING_SPEED;
				}
			}
		}

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_WORM)
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

					if (e->nx != 0) vx = 0;
					if (e->ny != 0) vy = 0;
				}
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

//#pragma endregion
//
	/* simple screen edge collision!!!
	if (vx > 0 && x > 290) x = 290;
	if (vx < 0 && x < 0) x = 0;*/
	//DebugOut(L"Pos: %.2f ,%.2f\n", x, y);
}

void CWorm::SetState(int state)
{
	CGameObject::SetState(state);
}

void CWorm::Render()
{
	int ani;
	//if (isFalling)
	if (vx < 0)
		ani = WORM_ANI_WALKING_LEFT;
	else
		ani = WORM_ANI_WALKING_RIGHT;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

 void CWorm::GetBoundingBox(float& left, float& top, float& right, float& bottom)
 {
	 left = x;
	 top = y;
	 right = x + WORM_BBOX_WIDTH;
	 bottom = y - WORM_BBOX_HEIGHT;
	 //DebugOut(L"%f\n", bottom);
 }