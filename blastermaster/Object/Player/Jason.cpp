#include "Jason.h"

void CJason::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + JASON_BBOX_WIDTH;
	bottom = top - JASON_BBOX_HEIGHT;
}

void CJason::UpdateStateTime()
{
	if (isUntouchable && (GetTickCount() - untouchableStart > JASON_UNTOUCHABLE_TIME))
	{
		untouchableStart = 0;
		isUntouchable = false;
	}
}

CJason::CJason()
{
	this->type = TYPE_JASON;
	state = JASON_STATE_IDLE_RIGHT;
	currentBulletType = BulletType::JasonBullet;
	untouchableEffect = new CRenderEffect((*CRenderEffects::GetInstance()->Get(0)));
	Health = JASON_MAX_HEALTH;
}

void CJason::Fire(float Direction)
{
	//No more bullet in clip
	if (ClipSize < 1)
		return;
	ClipSize--;

	LPBULLET bullet;
	switch (currentBulletType)
	{
	case BulletType::JasonBullet:
		bullet = new CJasonBullet();
		break;
	default:
		bullet = new CJasonBullet();
		break;
	}
	float bulletX = this->x, bulletY = this->y;
	bulletY -= 8;
	if (nx > 0)
	{
		bulletX = x + 5;
	}
	bullet->SetPosition(bulletX, bulletY);
	bullet->SetDirection(Direction);
	CGrid::GetInstance()->addObject(bullet);
	Sound::GetInstance()->Play(eSound::soundSophiaShoot);
}

void CJason::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
#pragma region Auto go X handle
	if (isAutoGoX == true)
	{
		isJumping = false;
		float space;
		int direction;
		if (CCamera::GetInstance()->isMovingToNewSection == false)
			for (int i = 0; i < coObjects->size(); ++i)
				if (coObjects->at(i)->type == TYPE_WALLIMAGE)
				{
					//DebugOut(L"%f, %f\n", x + SOPHIA_BBOX_WIDTH, coObjects->at(i)->GetX());
					if (isCollidingWith(coObjects->at(i), space, direction) == true)
						CSectionManager::GetInstance()->ChangeSection(backupSectionID);
				}
		if (vx > 0)
		{
			state = JASON_STATE_WALKING_RIGHT;
			if (x < AutoX)
			{
				vx = JASON_WALKING_SPEED;
				vy = 0;
				x += vx * dt;
				return;
			}
			else
				isAutoGoX = false;
		}
		if (vx < 0)
		{
			state = JASON_STATE_WALKING_LEFT;
			if (x > AutoX)
			{
				vx = -JASON_WALKING_SPEED;
				vy = 0;
				x += vx * dt;
				return;
			}
			else
				isAutoGoX = false;
		}
	}

#pragma endregion
	CGameObject::Update(dt);
	vy -= JASON_GRAVITY * dt;
	UpdateStateTime();

	vector<LPGAMEOBJECT> *listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if (coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i) == NULL)
				continue;
			if (coObjects->at(i)->type != TYPE_JASON)
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

				if (e->nx != 0)
					vx = 0;
				if (e->ny != 0)
				{
					if (vy < 0)
						isJumping = false;
					vy = 0;
				}
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
				{
					SetState(JASON_STATE_ATTACKED);
					this->Health -= e->obj->Damage;
				}
			}
			break;
			case TYPE_LAVA:
			case TYPE_FENCE:
				x += dx;
				y += dy;
				break;
			case TYPE_BULLET:
				if (dynamic_cast<CFloaterBullet *>(e->obj) || dynamic_cast<CSkullBullet *>(e->obj) || dynamic_cast<CEyeballBullet *>(e->obj))
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
					{
						if (this->Health <= 0)
						{
							this->isDestroyed = true;
						}
						else
						{
							this->SetState(JASON_STATE_ATTACKED);
							this->Health -= e->obj->Damage;
						}
					}
				}
				break;
			case TYPE_PORTAL:
				x += dx;
				y += dy;
				CSceneManager::GetInstance()->SetScene(((CPortal *)(e->obj))->SceneID);
				break;
			case TYPE_ITEM:
				this->x += dx;
				this->y += dy;
				e->obj->isDestroyed = true;
				Sound::GetInstance()->Play(eSound::soundCollectItem);
				this->Health += 20;
				break;
			default:
				break;
			}
		}
	}
	DebugOut(L"%d\n", isPressingDown);
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
			case TYPE_GATEWAY:
			{
				if (isAutoGoX == false)
				{
					isAutoGoX = true;
					((CGateway *)(listObject->at(i)))->GetDestination(AutoX, AutoY);
					backupSectionID = ((CGateway *)(listObject->at(i)))->newSectionID;
				}
			}
			break;
			case TYPE_PORTAL:
			{
				if (isPressingDown)
				{
					isPressingDown = false;
					CSceneManager::GetInstance()->SetScene((((CPortal *)listObject->at(i)))->SceneID);
				}
			}
			break;
			case TYPE_LAVA:
			{
				vy += JASON_GRAVITY / 2;
				StartUntouchable();
			}
			break;
			case TYPE_FENCE:
			{
				StartUntouchable();
			}
			break;
			default:
				break;
			}
		}
	}
#pragma endregion
	if (isJumpingIn)
	{
		if (isFalling)
		{
			isJumpingIn = false;
			state = JASON_STATE_INSOPHIA;
			this->isEnabled = false;
		}
	}
	//Set falling flag
	if (round(vy * 10) / 10 < 0.0f)
		isFalling = true;
	else
	{
		isFalling = false;
		Sound::GetInstance()->Play(eSound::soundSophiaGroundTouch);
	}

	//Reload gun
	if (ClipSize < 3)
	{
		if (GetTickCount() - reloadingTimeCount > JASON_RELOAD_TIME)
		{
			ClipSize++;
			reloadingTimeCount = GetTickCount();
		}
	}
}

void CJason::Render()
{
	int ani = currentAnimation;
	if (roundf(vx * 100) / 100 == 0.00f)
	{
		if (nx > 0)
			ani = JASON_ANI_IDLE_RIGHT;
		else
			ani = JASON_ANI_IDLE_LEFT;
	}
	else
	{
		if (nx > 0)
			ani = JASON_ANI_WALKING_RIGHT;
		else
			ani = JASON_ANI_WALKING_LEFT;
	}
	if (isJumping)
	{
		if (nx > 0)
			ani = JASON_ANI_IDLE_RIGHT;
		else
			ani = JASON_ANI_IDLE_LEFT;
	}
	currentAnimation = ani;
	if (isUntouchable)
	{
		CRenderEffectFrame *framecolor = untouchableEffect->GetColor();
		animation_set->at(currentAnimation)->Render(x, y, framecolor->A, framecolor->R, framecolor->G, framecolor->B);
	}
	else
		animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CJason::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JASON_STATE_WALKING_RIGHT:
		vx = JASON_WALKING_SPEED;
		nx = 1;
		break;
	case JASON_STATE_WALKING_LEFT:
		vx = -JASON_WALKING_SPEED;
		nx = -1;
		break;
	case JASON_STATE_JUMP:
		if (!isJumping && !isFalling)
		{
			vy = JASON_JUMP_SPEED_Y;
			isJumping = true;
			Sound::GetInstance()->Play(eSound::soundSophiaLongJump);
		}
		break;
	case JASON_STATE_ATTACKED:
		vx = -0.1f * nx;
		StartUntouchable();
		break;
	case JASON_STATE_JUMPIN:
		if (!isJumping && !isFalling && !isJumpingIn)
		{
			vy = JASON_JUMPIN_SPEED_Y;
			isJumpingIn = true;
			Sound::GetInstance()->Play(eSound::soundSophiaLongJump);
		}
	case JASON_STATE_IDLE_LEFT:
	case JASON_STATE_IDLE_RIGHT:
		if (vx != 0)
		{
			vx -= JASON_FRICTION * vx * dt;
			//vx = 0;
		}
		break;
	}
}
