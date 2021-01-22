#include "BossCrabullus.h"

CCrabullus::CCrabullus()
{
	this->type = TYPE_ENEMY_CRABULLUS;
	ny = 1;
	nx = 1;
	ReloadTimeCount = GetTickCount();
	InclipReloadTimeCount = GetTickCount();
	ClipSize = 4;
}

void CCrabullus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + CRABULLUS_BBOX_WIDTH;
	bottom = top - CRABULLUS_BBOX_HEIGHT;
}

void CCrabullus::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy = CRABULLUS_MOVING_SPEED_Y * ny;
	vx = CRABULLUS_MOVING_SPEED_X * nx;

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
			{
				x += min_tx * dx + e->nx * 0.1f;
				y += min_ty * dy + e->ny * 0.1f;

				if (e->nx != 0)
				{
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
			case TYPE_BIGJASON:
			case TYPE_GATEWAY:
			case TYPE_WALLIMAGE:
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
//Reload gun
	if (ClipSize <= 0)
	{
		if(!isReloading)
			StartReload();
		else
		{
			if (GetTickCount() - ReloadTimeCount >= CRABULLUS_RELOAD_TIME)
				ClipSize = 4;
		}
	}
}

void CCrabullus::Fire(int Direction)
{
	if (ClipSize < 1)
		return;
	if (InclipReloadTimeCount - GetTickCount() < CRABULLUS_INCLIP_RELOAD_TIME)
	{
		return;
	}
	else
	{
		InclipReloadTimeCount = GetTickCount();
		ClipSize--;
		LPBULLET bullet = new CBossBullet();
		float bulletX = this->x + CRABULLUS_BBOX_WIDTH / 2, bulletY = this->y - CRABULLUS_BBOX_HEIGHT;

		bullet->SetPosition(bulletX, bulletY);
		bullet->SetDirection(Direction);
		CGrid::GetInstance()->addObject(bullet);
	}
	
}

void CCrabullus::Render()
{
	animation_set->at(0)->Render(x,y);
}

void CCrabullus::StartReload()
{
	ReloadTimeCount = GetTickCount();
	isReloading = true;
}

void CCrabullus::SetState(int state)
{
}
