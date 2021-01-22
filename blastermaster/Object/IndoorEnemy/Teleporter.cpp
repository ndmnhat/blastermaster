#include "Teleporter.h"

CTeleporter::CTeleporter()
{
	enemyType = IndoorEnemyType::Teleporter;
	width = TELEPORTER_BBOX_WIDTH;
	height = TELEPORTER_BBOX_HEIGHT;
	Health = TELEPORTER_HEALTH;
	Damage = TELEPORTER_DAMAGE;
	this->x = x;
	this->y = y;
	SetState(TELEPORTER_STATE_IDLE);
	idleTimeCount = GetTickCount();
	srand(time(NULL));
}

void CTeleporter::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == TELEPORTER_STATE_TELEPORT && teleportCount != 0) {
		teleportCount--;
		teleportGapTimeCount = GetTickCount();
		dx = rand() % 10 - 5;
		dy = rand() % 10 - 5;
		x += dx;
		y += dy;
	}

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY)
				listObject->push_back(coObjects->at(i));
			if (coObjects->at(i)->type == TYPE_BIGJASON)
			{
				if (state == TELEPORTER_STATE_IDLE && GetTickCount() - idleTimeCount > TELEPORTER_IDLE_TIME) {
					SetState(TELEPORTER_STATE_TRANSFORM);
					transformTimeCount = GetTickCount();
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

				if (e->nx != 0) vx = 0;
				if (e->ny != 0) vy = 0;

				break;
			case TYPE_BULLET:
				e->obj->isDestroyed = true;
				if (state != TELEPORTER_STATE_IDLE) {
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

	if (state == TELEPORTER_STATE_TRANSFORM) {
		if (GetTickCount() - transformTimeCount > TELEPORTER_TRANSFORMING_TIME) {
			SetState(TELEPORTER_STATE_TELEPORT);
			teleportTimeCount = GetTickCount();
		}
		else
			Sound::GetInstance()->Play(eSound::soundTeleporterTransform);
	}

	if (state == TELEPORTER_STATE_TELEPORT) {
		if (GetTickCount() - teleportTimeCount > TELEPORTER_TELEPORTING_TIME) {
			SetState(TELEPORTER_STATE_IDLE);
			idleTimeCount = GetTickCount();
		}
	}

	if (teleportCount == 0) {
		if (GetTickCount() - teleportGapTimeCount > TELEPORTER_TELEPORTING_GAP_TIME) {
			teleportCount = 1;
		}
	}
}

void CTeleporter::Render()
{
	int ani;
	switch (state) {
	case TELEPORTER_STATE_IDLE:
		ani = TELEPORTER_ANI_IDLE;
		break;
	case TELEPORTER_STATE_TRANSFORM:
		ani = TELEPORTER_ANI_TRANSFORM;
		break;
	case TELEPORTER_STATE_TELEPORT:
		ani = TELEPORTER_ANI_TELEPORT;
		break;
	}
	animation_set->at(ani)->Render(x, y);
}

void CTeleporter::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == TELEPORTER_ANI_IDLE) {
		dx = 0;
		dy = 0;
	}
}

void CTeleporter::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	CIndoorEnemy::GetBoundingBox(left, top, right, bottom);
}
