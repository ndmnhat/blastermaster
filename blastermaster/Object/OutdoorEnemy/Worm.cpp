#include "Worm.h"

CWorm::CWorm() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Worm;
	width = WORM_BBOX_WIDTH;
	height = WORM_BBOX_HEIGHT;
	this->x = x;
	this->y = y;
	health = WORM_HEALTH;
	damage = WORM_DAMAGE;
}

void CWorm::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	vy = -WORM_GRAVITY;
	vx = WORM_WALKING_SPEED * nx;

	int i = GetSophiaPosInCoobject(coObjects);
	if (i != -1)
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
				x += min_tx * dx + e->nx * 0.1f;
				y += min_ty * dy + e->ny * 0.1f;

				if (e->nx != 0) vx = 0;
				if (e->ny != 0) vy = 0;

				break;
			case TYPE_SOPHIA: case TYPE_ENEMY:
				x += dx;
				y += dy;
			case TYPE_BULLET:
				if (dynamic_cast<CJasonBullet*>(e->obj))
				{
					this->isDestroyed = true;
					if (rand() % 3 == 1)
					{
					CPower* power = new CPower();
					power->SetPosition(x, y);
					CGrid::GetInstance()->addObject(power);
					}
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
	{
		ani = WORM_ANI_WALKING_LEFT;
	}
	else if (vx > 0) 
	{
		ani = WORM_ANI_WALKING_RIGHT;
	}
	else if(vx == 0)
	{
		if (nx > 0)
			ani = WORM_ANI_FALLING_LEFT;
		else
			ani = WORM_ANI_FALLING_RIGHT;
	}
		 
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}