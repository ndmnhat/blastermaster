#include "Dome.h"

CDome::CDome() : COutdoorEnemy()
{
	enemyType = OutdoorEnemyType::Dome;
	width = DOME_BBOX_WIDTH;
	height = DOME_BBOX_HEIGHT;
	preNx = -1;
	state = DOME_STATE_ATTACK_Y;
	nx = 0;
	ny = 1;
}

void CDome::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	switch (state) {
	case DOME_STATE_ON_LEFT_WALL: case DOME_STATE_ON_RIGHT_WALL:
		if ((y <= wallPosition.bottom || y >= (wallPosition.top + height))) {
			if (state == DOME_STATE_ON_LEFT_WALL)
				nx = 1;
			else if (state == DOME_STATE_ON_RIGHT_WALL)
				nx = -1;

			if (ny < 0)
				SetState(DOME_STATE_ON_THE_CEILING);
			else if (ny > 0)
				SetState(DOME_STATE_ON_THE_GROUND);
			if (ny != 0) {
				preNy = ny;
				ny = 0;
			}
		}
		break;
	case DOME_STATE_ON_THE_GROUND: case DOME_STATE_ON_THE_CEILING:
		if ((x <= (wallPosition.left - width) || x >= wallPosition.right)) {
			if (state == DOME_STATE_ON_THE_CEILING)
				ny = 1;
			else if (state == DOME_STATE_ON_THE_GROUND)
				ny = -1;
			
			if (nx > 0)
				SetState(DOME_STATE_ON_RIGHT_WALL);
			else if (nx < 0)				
				SetState(DOME_STATE_ON_LEFT_WALL);
			if (nx != 0) {
				preNx = nx;
				nx = 0;
			}
		}
		break;
	}

	vy = DOME_MOVING_SPEED * ny;
	vx = DOME_MOVING_SPEED * nx;	

	CGameObject::Update(dt);

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_ENEMY_DOME)
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

				if (e->nx != 0)
				{
					e->obj->GetBoundingBox(wallPosition.left, wallPosition.top, wallPosition.right, wallPosition.bottom);
					
					if (nx != 0) {
						preNx = this->nx;
						this->nx = 0;
					}
					
					if (this->state == DOME_STATE_ON_THE_GROUND)
						this->ny = 1;
					else if (this->state == DOME_STATE_ON_THE_CEILING)
						this->ny = -1;
					else if (this->state == DOME_STATE_ATTACK_X)
						this->ny = preNy;

					if (e->nx < 0)
						this->SetState(DOME_STATE_ON_LEFT_WALL);
					else if (e->nx > 0)
						this->SetState(DOME_STATE_ON_RIGHT_WALL);
				}

				if (e->ny != 0)
				{
					e->obj->GetBoundingBox(wallPosition.left, wallPosition.top, wallPosition.right, wallPosition.bottom);
					
					if (ny != 0) {
						preNy = this->ny;
						this->ny = 0;
					}

					if (this->state == DOME_STATE_ON_RIGHT_WALL)
						this->nx = 1;
					else if (this->state == DOME_STATE_ON_LEFT_WALL)
						this->nx = -1;
					else if (this->state == DOME_STATE_ATTACK_Y)
						this->nx = preNx;
					
					if (e->ny < 0)
						this->SetState(DOME_STATE_ON_THE_CEILING);
					else if (e->ny > 0)
						this->SetState(DOME_STATE_ON_THE_GROUND);
				}
				break;
			case TYPE_SOPHIA:
				x += dx;
				y += dy;
				break;
			default:
				break;
			}
		}
	}
	float left, top, right, bottom;
	GetBoundingBox(left, top, right, bottom);
	//DebugOut(L"Wall: l: %f, t: %f, r: %f, b: %f\n", wallPosition.left, wallPosition.top, wallPosition.right, wallPosition.bottom);
	DebugOut(L"Dome: x: %f, y: %f\n", x, y);
	//DebugOut(L"%d\n", this->ny);
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



void CDome::Render()
{
	int ani=0;
	switch (state) {
	case DOME_STATE_ON_THE_GROUND:
		if (vx > 0)
			ani = DOME_ANI_WALKING_RIGHT;
		else
			ani = DOME_ANI_WALKING_LEFT;
		
		break;

	case DOME_STATE_ON_LEFT_WALL:
		if (vy > 0)
			ani = DOME_ANI_CRAWLING_UP_LEFT;
		else 
			ani = DOME_ANI_CRAWLING_DOWN_LEFT;
		break;

	case DOME_STATE_ON_RIGHT_WALL:
		if (vy > 0)
			ani = DOME_ANI_CRAWLING_UP_RIGHT;
		else
			ani = DOME_ANI_CRAWLING_DOWN_RIGHT;
		break;

	case DOME_STATE_ON_THE_CEILING:
		if (vx > 0)
			ani = DOME_ANI_CRAWLING_RIGHT;
		else
			ani = DOME_ANI_CRAWLING_LEFT;
		break;
	case DOME_STATE_ATTACK_X:
		if (vx > 0)
			ani = DOME_ANI_CHARGING_RIGHT;
		else 
			ani = DOME_ANI_CHARGING_LEFT;
	case DOME_STATE_ATTACK_Y:
		if (vy > 0)
			ani = DOME_ANI_CHARGING_UP;
		else
			ani = DOME_ANI_CHARGING_DOWN;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CDome::SetState(int state)
{
	CGameObject::SetState(state);

}

void CDome::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	right = left + this->width;
	top = this->y;
	bottom = top - this->height;
}

int CDome::GetSophiaPosInCoobject(std::vector<LPGAMEOBJECT>* coObjects)
{
	if (coObjects != NULL)
	{
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type == TYPE_SOPHIA)
			{
				return i;
			}
		}
	}
	else return -1;
}
