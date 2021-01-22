#include "Eyeball.h"

CEyeball::CEyeball()
{
	enemyType = IndoorEnemyType::Eyeball;
	width = EYEBALL_BBOX_WIDTH;
	height = EYEBALL_BBOX_HEIGHT;
	Health = EYEBALL_HEALTH;
	Damage = EYEBALL_DAMAGE;
	ClipSize = EYEBALL_BULLET_CLIPSIZE;
	reloadingTimeCount = GetTickCount();
	this->x = x;
	this->y = y;
	nx = -1;
}

void CEyeball::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

	vx = EYEBALL_MOVING_SPEED * nx;
	//vx = sqrt((EYEBALL_MOVING_SPEED*nx)*(EYEBALL_MOVING_SPEED*nx) + EYEBALL_MOVING_SPEED * EYEBALL_MOVING_SPEED);

	/*if (coObjects != NULL)
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
		}*/

	CGameObject::Update(dt);

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY)
				listObject->push_back(coObjects->at(i));
			if (coObjects->at(i)->type == TYPE_BIGJASON)
			{
				if (coObjects->at(i)->y < this->y)
				{
					float coX = coObjects->at(i)->x - this->x;
					float coY = coObjects->at(i)->y - this->y;
					float angle = acos((-coX) / sqrt(coX * coX + coY * coY));
					//DebugOut(L"%f\n", (angle * 180 / PI) - (angle * 180 / PI) * 2);
					Fire((angle * 180 / PI) - (angle * 180 / PI) * 2);
				}
			}

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

				if (e->nx != 0)
					this->nx *= -1;
				if (e->ny != 0)
					vy = 0;

				break;
			case TYPE_BIGJASON:
				x += dx;
				y += dy;
				break;
			case TYPE_BULLET:
				e->obj->isDestroyed = true;
				if (dynamic_cast<CBigJasonBullet*>(e->obj))
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
					else 
						this->Health -= (e->obj->Damage);
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
	if (ClipSize < 1)
	{
		if (GetTickCount() - reloadingTimeCount > EYEBALL_BULLET_RELOADTIME)
		{
			ClipSize++;
			reloadingTimeCount = GetTickCount();
		}
	}
	//DebugOut(L"EYEBALL VX: %f\n", this->vx);
}

void CEyeball::Render()
{
	int ani;
	ani = EYEBALL_ANI_MOVING;
	animation_set->at(ani)->Render(x, y);
}
void CEyeball::SetState(int state)
{
	CGameObject::SetState(state);
}
void CEyeball::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	CIndoorEnemy::GetBoundingBox(left, top, right, bottom);
}

void CEyeball::Fire(int Direction)
{
	//No more bullet in clip
	if (ClipSize < 1)
		return;
	ClipSize--;

	LPBULLET bullet = new CEyeballBullet();
	float bulletX = this->x + EYEBALL_BBOX_WIDTH / 2, bulletY = this->y - EYEBALL_BBOX_HEIGHT;

	bullet->SetPosition(bulletX, bulletY);
	bullet->SetDirection(Direction);
	CGrid::GetInstance()->addObject(bullet);
}
