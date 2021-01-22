#include "Cannon.h"

CCannon::CCannon()
{
	enemyType = IndoorEnemyType::Cannon;
	width = CANNON_BBOX_WIDTH;
	height = CANNON_BBOX_HEIGHT;
	ClipSize = CANNON_BULLET_CLIPSIZE;
	reloadingTimeCount = GetTickCount();
	Health = CANNON_HEALTH;
	Damage = CANNON_DAMAGE;
	isShootingVertically = false;
}

void CCannon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (ClipSize > 0) {
		if (isShootingVertically == true) {
			Fire(90);
			Fire(270);
			isShootingVertically = false;
		}
		else {
			Fire(0);
			Fire(180);
			isShootingVertically = true;
		}
	}

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

	if (coEvents.size() != 0)
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
	if (ClipSize == 0)
	{
		if (GetTickCount() - reloadingTimeCount > CANNON_BULLET_RELOADTIME)
		{
			ClipSize = CANNON_BULLET_CLIPSIZE;
			reloadingTimeCount = GetTickCount();
		}
	}
}

void CCannon::SetState(int state)
{
	CGameObject::SetState(state);
}

void CCannon::Render()
{
	int ani;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CCannon::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	CIndoorEnemy::GetBoundingBox(left, top, right, bottom);
}

void CCannon::Fire(int Direction)
{
	//No more bullet in clip
	if (ClipSize == 0)
		return;
	ClipSize--;

	LPBULLET bullet = new CEyeballBullet();
	float bulletX, bulletY;

	if (Direction == 0 || Direction == 180) {
		bulletY = this->y - CANNON_BBOX_HEIGHT / 2 + 5;
		if (Direction == 0)		bulletX = this->x;
		if (Direction == 180)	bulletX = this->x + CANNON_BBOX_WIDTH;
	}
	if (Direction == 90 || Direction == 270) {
		bulletX = this->x + (CANNON_BBOX_WIDTH / 2 - 5);
		if (Direction == 90)	bulletY = this->y;
		if (Direction == 270)	bulletY = this->y - CANNON_BBOX_HEIGHT;
	}

	bullet->SetPosition(bulletX, bulletY);
	bullet->SetDirection(Direction);
	CGrid::GetInstance()->addObject(bullet);
}
