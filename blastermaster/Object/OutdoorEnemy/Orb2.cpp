#include "Orb2.h"

COrb2::COrb2()
{
	enemyType = OutdoorEnemyType::Orb2;
	width = ORB_BBOX_WIDTH;
	height = ORB_BBOX_HEIGHT;
	Health = ORB_HEALTH;
	Damage = ORB_DAMAGE;
	nx = 1;
	ny = 1;
}

void COrb2::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	int i = GetSophiaPosInCoobject(coObjects);
	if (i != -1)
	{
		if (abs(this->x - coObjects->at(i)->x) <= 30 && abs(this->y - coObjects->at(i)->y) <= 30) {
			if (this->x < coObjects->at(i)->x)
				nx = 1;
			else if (this->x > coObjects->at(i)->x)
				nx = -1;

			if (this->y < coObjects->at(i)->y)
				ny = 1;
			else if (this->y > coObjects->at(i)->y)
				ny = -1;
		}
	}


	vy = ORB_MOVING_SPEED * ny;
	vx = ORB_MOVING_SPEED * nx;

	CGameObject::Update(dt);

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY)
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
			case TYPE_ENEMY:
				x += dx;
				y += dy;
				break;
			case TYPE_SOPHIA:
			{
				this->isDestroyed = true;
				CSmallBulletExplosion* explosion = new CSmallBulletExplosion();
				explosion->SetPosition(x, y);
				CGrid::GetInstance()->addObject(explosion);
			}

			break;
			case TYPE_BULLET:
				e->obj->isDestroyed = true;
				if (dynamic_cast<CJasonBullet*>(e->obj) || dynamic_cast<CSophiaBullet*>(e->obj))
				{
					if (this->Health <= 0) {
						this->isDestroyed = true;
						Sound::GetInstance()->Play(eSound::soundEnemyDestroyed);
						if (rand() % 3 == 1)
						{
							CPower* power = new CPower();
							power->SetPosition(x, y);
							CGrid::GetInstance()->addObject(power);
						}
					}
					else this->Health -= (e->obj->Damage);
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
}

void COrb2::Render()
{
	int ani;
	if (vx != 0 || vy != 0)
		ani = ORB_ANI_SPINNING;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void COrb2::SetState(int state)
{
}
