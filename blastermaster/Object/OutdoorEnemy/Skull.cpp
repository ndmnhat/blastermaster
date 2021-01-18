#include "Skull.h"

CSkull::CSkull() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Skull;
	currentBulletType = BulletType::SkullBullet;
	width = SKULL_BBOX_WIDTH;
	height = SKULL_BBOX_HEIGHT;
	health = SKULL_HEALTH;
	damage = SKULL_DAMAGE;
	nx = -1;
	SetState(SKULL_STATE_MOVING);
}

void CSkull::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{	
	if (state == SKULL_STATE_MOVING) {
		int i = GetSophiaPosInCoobject(coObjects);
		if (i != -1)
		{
		if (nx < 0) {
			if (int(this->x) == int(coObjects->at(i)->x) + 18) {
				SetState(SKULL_STATE_ATTACKING);
			}
		}
		else if (int(this->x) == int(coObjects->at(i)->x)) {
				SetState(SKULL_STATE_ATTACKING);
		}
		}
	}
	
	if (state == SKULL_STATE_ATTACKING) {
		if ((GetTickCount() - startAttacking) > SKULL_ATTACKING_TIME) {
			startAttacking = 0;
			SetState(SKULL_STATE_MOVING);
		}
	}

	switch (state)
	{
	case SKULL_STATE_MOVING:
		vx = SKULL_MOVING_SPEED * nx;
		break;
	case SKULL_STATE_ATTACKING:
		vx = 0;
		break;
	default:
		break;
	}

	CGameObject::Update(dt);

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_SKULL)
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

void CSkull::Render()
{
	int ani;
	switch (state)
	{
	case SKULL_STATE_MOVING:
		if (nx < 0)
			ani = SKULL_ANI_MOVING_LEFT;
		else 
			ani = SKULL_ANI_MOVING_RIGHT;
		break;
	case SKULL_STATE_ATTACKING:
		if (nx < 0)
			ani = SKULL_ANI_ATTACKING_LEFT;
		else
			ani = SKULL_ANI_ATTACKING_RIGHT;
		break;
	default:
		break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CSkull::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state) {
	case SKULL_STATE_ATTACKING:
		startAttacking = GetTickCount();
		Fire(270, this->nx);
		break;
	default:
		break;
	}
}

void CSkull::Fire(float Direction, int nx)
{
	LPBULLET bullet;
	/*switch (currentBulletType)
	{
	case BulletType::SophiaBullet:
		bullet = new CSophiaBullet();
		break;
	case BulletType::SkullBullet:
		bullet = new CSkullBullet();
		break;
	default:
		bullet = new CSkullBullet();
		break;
	}*/
	bullet = new CSkullBullet(nx);
	float bulletX = this->x, bulletY = this->y;
	if (nx > 0)
	{
		bulletX = x + 18;
	}
	bullet->SetPosition(bulletX, bulletY);
	bullet->SetDirection(Direction);
	CGrid::GetInstance()->addObject(bullet);
}
