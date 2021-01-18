#include "BigJason.h"

void CBigJason::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + BIGJASON_BBOX_WIDTH;
	bottom = top - BIGJASON_BBOX_HEIGHT;
}

void CBigJason::UpdateStateTime()
{
	if (isUntouchable && (GetTickCount() - untouchableStart > BIGJASON_UNTOUCHABLE_TIME))
	{
		untouchableStart = 0;
		isUntouchable = false;
	}
}

CBigJason::CBigJason()
{
	this->type = TYPE_BIGJASON;
	state = BIGJASON_ANI_IDLE_RIGHT;
	currentBulletType = BulletType::JasonBullet;
	untouchableEffect = new CRenderEffect((*CRenderEffects::GetInstance()->Get(0)));
	Health = BIGJASON_MAX_HEALTH;
}

void CBigJason::Fire(float Direction)
{
	//No more bullet in clip
	if (ClipSize < 1)
		return;
	ClipSize--;

	LPBULLET bullet;
	switch (currentBulletType)
	{
	case BulletType::BigJasonBullet:
		bullet = new CBigJasonBullet();
		break;
	default:
		bullet = new CBigJasonBullet();
		break;
	}
	float bulletX = this->x, bulletY = this->y;
	//DebugOut(L"%f\n", bulletY);
	//bulletY -= 8;
	if (nx > 0)
	{
		bulletX = x + BIGJASON_BBOX_WIDTH;
		bulletY = y - 13;
	}
	else if (nx < 0)
	{
		bulletY = y - 13;
	}
	else if (ny > 0)
	{
		bulletX = x + 3;
	}
	else if (ny < 0)
	{
		bulletX = x + 3;
		bulletY = y - BIGJASON_BBOX_HEIGHT;
	}
	bullet->SetPosition(bulletX, bulletY);
	bullet->SetDirection(Direction);
	CGrid::GetInstance()->addObject(bullet);
}

void CBigJason::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
#pragma region Auto go X handle
	if (isAutoGoX == true)
	{
		float space;
		int direction;
		//if (CCamera::GetInstance()->isMovingToNewSection == false)
			//for (int i = 0; i < coObjects->size(); ++i)
			//	if (coObjects->at(i)->type == TYPE_WALLIMAGE)
			//	{
			//		//DebugOut(L"%f, %f\n", x + SOPHIA_BBOX_WIDTH, coObjects->at(i)->GetX());
			//		if (isCollidingWith(coObjects->at(i), space, direction) == true)
						CSectionManager::GetInstance()->ChangeSection(backupSectionID);
				//}
		if (round(y) < round(AutoY))
			y += BIGJASON_WALKING_SPEED * dt;
		if (round(y) > round(AutoY))
			y -= BIGJASON_WALKING_SPEED * dt;
		if (nx > 0)
		{
			state = BIGJASON_STATE_WALKING_RIGHT;
			if (x < AutoX)
			{
				vx = BIGJASON_WALKING_SPEED;
				vy = 0;
				x += vx * dt;
				return;
			}
			else
			{
				SetState(BIGJASON_STATE_IDLE_RIGHT);
				isAutoGoX = false;
			}
		}
		else if (nx < 0)
		{
			state = BIGJASON_STATE_WALKING_LEFT;
			if (x > AutoX)
			{
				vx = -BIGJASON_WALKING_SPEED;
				vy = 0;
				x += vx * dt;
				return;
			}
			else
			{
				isAutoGoX = false;
			}
		}
	}

#pragma endregion
#pragma region Auto go Y handle
	if (isAutoGoY == true)
	{
		float space;
		int direction;
		//if (CCamera::GetInstance()->isMovingToNewSection == false)
			//for (int i = 0; i < coObjects->size(); ++i)
			//	if (coObjects->at(i)->type == TYPE_WALLIMAGE)
			//	{
			//		//DebugOut(L"%f, %f\n", x + SOPHIA_BBOX_WIDTH, coObjects->at(i)->GetX());
			//		if (isCollidingWith(coObjects->at(i), space, direction) == true)
						CSectionManager::GetInstance()->ChangeSection(backupSectionID);
				//}
		if (ny > 0)
		{
			state = BIGJASON_STATE_WALKING_UP;
			if (y < AutoY)
			{
				vy = BIGJASON_WALKING_SPEED;
				vx = 0;
				y += vy * dt;
				return;
			}
			else
			{
				SetState(BIGJASON_STATE_IDLE_UP);
				isAutoGoY = false;
			}
		}
		if (ny < 0)
		{
			state = BIGJASON_STATE_WALKING_DOWN;
			if (y > AutoY)
			{
				vy = -BIGJASON_WALKING_SPEED;
				vx = 0;
				y += vy * dt;
				return;
			}
			else
			{
				isAutoGoY = false;
			}
		}
	}

#pragma endregion

	CGameObject::Update(dt);
	UpdateStateTime();

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i) == NULL)
				continue;
			if (coObjects->at(i)->type != TYPE_BIGJASON)
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
				if (e->ny != 0) vy = 0;
			}
			break;
			case TYPE_ENEMY:
			{
				if (isUntouchable)
				{
					if (e->nx != 0)
					{
						x += dx;
					}
					if (e->ny != 0)
						y += dy;
				}
				else
					SetState(BIGJASON_STATE_ATTACKED);
			}
			break;
			case TYPE_GATEWAY:
				float left, top, right, bottom;
				CSectionManager::GetInstance()->Get(((CGateway*)(coEventsResult.at(i)->obj))->newSectionID)->GetSectionBoundary(left, top, right, bottom);
				if (y < bottom || y - BIGJASON_BBOX_HEIGHT > top)
				{
					if (isAutoGoY == false)
					{
						isAutoGoY = true;
						((CGateway*)(coEventsResult.at(i)->obj))->GetDestination(AutoX, AutoY);
						backupSectionID = ((CGateway*)(coEventsResult.at(i)->obj))->newSectionID;
					}

				}
				else
				{
						if (isAutoGoX == false)
						{
							isAutoGoX = true;
							((CGateway*)(coEventsResult.at(i)->obj))->GetDestination(AutoX, AutoY);
							backupSectionID = ((CGateway*)(coEventsResult.at(i)->obj))->newSectionID;
						}

				}
				break;
			default: break;
			}
		}
	}
	//DebugOut(L"%f\n", x+BIGJASON_BBOX_WIDTH);
#pragma region Colliding with object handle

	for (UINT i = 0; i < listObject->size(); i++)
	{
		float space;
		int direction;
		if (isCollidingWith(listObject->at(i), space, direction))
		{
			switch (listObject->at(i)->type)
			{
			case TYPE_WALL:
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
			break;
			//case TYPE_GATEWAY:
			//{
			//	if (direction == 0)
			//	{
			//		y += dy;
			//		if (isAutoGoY == false)
			//		{
			//		isAutoGoY = true;
			//		((CGateway*)(listObject->at(i)))->GetDestination(AutoX, AutoY);
			//		backupSectionID = ((CGateway*)(listObject->at(i)))->newSectionID;
			//		}
			//	}
			//	else
			//	{
			//		x += dx;
			//		if (isAutoGoX == false)
			//		{
			//			isAutoGoX = true;
			//			((CGateway*)(listObject->at(i)))->GetDestination(AutoX, AutoY);
			//			backupSectionID = ((CGateway*)(listObject->at(i)))->newSectionID;
			//		}
			//	}
			//}
			//break;
			default: break;
			}
		}
	}
#pragma endregion

	//Reload gun
	if (ClipSize < 3)
	{
		if (GetTickCount() - reloadingTimeCount > BIGJASON_RELOAD_TIME)
		{
			ClipSize++;
			reloadingTimeCount = GetTickCount();
		}
	}

	//Dead
	if(isDead && currentAnimation == BIGJASON_ANI_DIE)
		if (animation_set->at(currentAnimation)->GetCurrentFrame() == animation_set->at(currentAnimation)->GetFramesSize() - 1)
		{
			isDead = false;
			SetState(BIGJASON_STATE_IDLE_RIGHT);
			x = 110;
			y = 143;
			CSectionManager::GetInstance()->ChangeSection(1,true);
		}
}

void CBigJason::Render()
{
	int ani = currentAnimation;
	if ((roundf(vx * 100) / 100 == 0.00f) && (roundf(vy * 100) / 100 == 0.00f))
	{
		if (nx > 0)
			ani = BIGJASON_ANI_IDLE_RIGHT;
		else if (nx < 0)
			ani = BIGJASON_ANI_IDLE_LEFT;
		else if (ny > 0)
			ani = BIGJASON_ANI_IDLE_UP;
		else if (ny <0)
			ani = BIGJASON_ANI_IDLE_DOWN;
	}
	else
	{
			if (nx > 0)
				ani = BIGJASON_ANI_WALKING_RIGHT;
			else if (nx < 0)
				ani = BIGJASON_ANI_WALKING_LEFT;
			else if (ny > 0)
				ani = BIGJASON_ANI_WALKING_UP;
			else if (ny < 0)
				ani = BIGJASON_ANI_WALKING_DOWN;

	}
	if (isDead)
		ani = BIGJASON_ANI_DIE;
	currentAnimation = ani;
	if (isUntouchable)
	{
		CRenderEffectFrame* framecolor = untouchableEffect->GetColor();
		animation_set->at(currentAnimation)->Render(x, y, framecolor->A, framecolor->R, framecolor->G, framecolor->B);
	}
	else
		animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CBigJason::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BIGJASON_STATE_WALKING_RIGHT:
		vx = BIGJASON_WALKING_SPEED;
		nx = 1;
		ny = 0;
		break;
	case BIGJASON_STATE_WALKING_LEFT:
		vx = -BIGJASON_WALKING_SPEED;
		nx = -1;
		ny = 0;
		break;
	case BIGJASON_STATE_WALKING_DOWN:
		vy = -BIGJASON_WALKING_SPEED;
		ny = -1;
		nx = 0;
		break;
	case BIGJASON_STATE_WALKING_UP:
		vy = BIGJASON_WALKING_SPEED;
		ny = 1;
		nx = 0;
		break;
	case BIGJASON_STATE_ATTACKED:
		StartUntouchable();
		break;
	case BIGJASON_STATE_IDLE_LEFT: case BIGJASON_STATE_IDLE_RIGHT:
		vx = 0;
		break;
	case BIGJASON_STATE_IDLE_UP: case BIGJASON_STATE_IDLE_DOWN:
		vy = 0;
		break;
	case BIGJASON_STATE_DIE:
		isDead = true;
		break;
	}
}
