#include "FloaterBullet.h"
#include "..\Player\Sophia.h"
#include "..\Player\Jason.h"
void CFloaterBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vx = -cos(DirectioninRad) * Speed;
	vy = sin(DirectioninRad) * Speed;
	CGameObject::Update(dt);
	x += dx;
	y += dy;

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == TYPE_BULLET)
				continue;
			if (coObjects->at(i) == NULL)
				continue;
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
				if (e->ny != 0)
				{
					vy = 0;
				}
			}
			break;
			case TYPE_JASON:
			{
				this->isDestroyed = true;
				((CJason*)(e->obj))->SetState(JASON_STATE_ATTACKED);
				e->obj->Health -= this->Damage;
			}
			break;
			case TYPE_SOPHIA:
			{
				this->isDestroyed = true;
				((CSophia*)(e->obj))->SetState(SOPHIA_STATE_ATTACKED);
				e->obj->Health -= this->Damage;
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
				this->isDestroyed = true;
				CSmallBulletExplosion* explosion = new CSmallBulletExplosion();
				explosion->SetPosition(x, y);
				CGrid::GetInstance()->addObject(explosion);
			}
		}
	}
	if (LifeTime < GetTickCount() - lifeTimeStart)
		this->isDestroyed = true;
}

void CFloaterBullet::Render()
{
	animation_set->at(0)->Render(x, y);
}

void CFloaterBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + FLOATER_BULLET_BBOX_WIDTH;
	bottom = top - FLOATER_BULLET_BBOX_HEIGHT;
}

CFloaterBullet::CFloaterBullet()
{
	this->Speed =    FLOATER_BULLET_SPEED;
	this->Damage =   FLOATER_BULLET_DAMAGE;
	this->LifeTime = FLOATER_BULLET_LIFETIME;
	LPANIMATION_SET ani_set = CAnimationSets::GetInstance()->Get(FLOATER_BULLET_ANIMATION_SET_ID);
	this->SetAnimationSet(ani_set);
	this->lifeTimeStart = GetTickCount();
}
