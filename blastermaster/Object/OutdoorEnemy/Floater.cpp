#include "Floater.h"

CFloater::CFloater() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Floater;
	width = FLOATER_BBOX_WIDTH;
	height = FLOATER_BBOX_HEIGHT;
	ClipSize = FLOATER_BULLET_CLIPSIZE;
	reloadingTimeCount = GetTickCount();
	Health = FLOATER_HEALTH;
	Damage = FLOATER_DAMAGE;
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
			if (coObjects->at(i)->type != TYPE_ENEMY)
				listObject->push_back(coObjects->at(i));
			if (coObjects->at(i)->type == TYPE_SOPHIA)
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
			case TYPE_SOPHIA: case TYPE_JASON:
				x += dx;
				y += dy;
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
	if (ClipSize < 1)
	{
		if (GetTickCount() - reloadingTimeCount > FLOATER_BULLET_RELOADTIME)
		{
			ClipSize++;
			reloadingTimeCount = GetTickCount();
		}
	}
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

void CFloater::Fire(int Direction)
{
	//No more bullet in clip
	if (ClipSize < 1)
		return;
	ClipSize--;

	LPBULLET bullet = new CFloaterBullet();
	float bulletX = this->x + FLOATER_BBOX_WIDTH / 2, bulletY = this->y - FLOATER_BBOX_HEIGHT;

	bullet->SetPosition(bulletX, bulletY);
	bullet->SetDirection(Direction);
	CGrid::GetInstance()->addObject(bullet);
}

void CFloater::SetState(int state)
{
	CGameObject::SetState(state);
}
