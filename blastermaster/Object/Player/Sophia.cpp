#include "Sophia.h"

void CSophia::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	//Calculate dx, dy
	CGameObject::Update(dt);

	// simple fall down
	//if (isFalling == true) 
	//{
		vy -= SOPHIA_GRAVITY * dt;
	//}

	UpdateStateTime();

	vector<LPGAMEOBJECT>* listObject = new vector<LPGAMEOBJECT>();
	listObject->clear();
	if(coObjects != NULL)
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->type != TYPE_SOPHIA)
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
							x += dx;
						if (e->ny != 0)
							y += dy;
					}
					else
						SetState(SOPHIA_STATE_ATTACKED);
				}
				break;
				default: break;
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
#pragma endregion
	if (round(vy * 10) / 10 < 0.0f)
		isFalling = true;
	else
		isFalling = false;
	// simple screen edge collision!!!
	//if (vx > 0 && x > 290) x = 290;
	//if (vx < 0 && x < 0) x = 0;
}

void CSophia::Render()
{
	int ani = -1;

	if (roundf(vx * 100)/100==0.00f)
	{
		RenderIdle(ani);
	}
	else if (vx > 0)
	{
		RenderWalkingRight(ani);
	}
	else if (vx < 0)
	{
		RenderWalkingLeft(ani);
	}
	if (isRotating)
	{
		RenderRotating(ani);
	}
	if (ani != -1)
		currentAnimation = ani;
	animation_set->at(currentAnimation)->Render(x, y);
	//RenderBoundingBox();
	
}

void CSophia::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SOPHIA_STATE_WALKING_RIGHT:
		vx = SOPHIA_WALKING_SPEED;
		if (nx == -1) { isRotating = true; rotatingStart = GetTickCount(); }
		nx = 1;
		break;
	case SOPHIA_STATE_WALKING_LEFT:
		vx = -SOPHIA_WALKING_SPEED;
		if (nx == 1) { isRotating = true; rotatingStart = GetTickCount(); }
		nx = -1;
		break;
	case SOPHIA_STATE_JUMP:
		if (!isJumping&&!isFalling)
		{
			vy = SOPHIA_JUMP_SPEED_Y;
			isJumping = true;
		}
		break;
	case SOPHIA_STATE_ATTACKED:
		vx = -0.1f * nx;
		StartUntouchable();
		break;
	case SOPHIA_STATE_IDLE_LEFT: case SOPHIA_STATE_IDLE_RIGHT:
		if (vx != 0)
		{
				vx -= SOPHIA_FRICTION * vx * dt;
		}
		break;
	}
}

void CSophia::UpdateStateTime()
{
	if (isUntouchable && (GetTickCount() - untouchableStart > SOPHIA_UNTOUCHABLE_TIME))
	{
		untouchableStart = 0;
		isUntouchable = false;
	}
	if (isRotating && (GetTickCount() - rotatingStart > 200))
	{
		rotatingStart = 0;
		isRotating = false;
	}
}

void CSophia::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	bottom = y;
	right = left + SOPHIA_BBOX_WIDTH;
	top = bottom + SOPHIA_BBOX_HEIGHT;
}
void CSophia::RenderWalkingLeft(int &ani)
{
	switch (currentAnimation)
	{
	case SOPHIA_ANI_WALKING_LEFT:
		ani = SOPHIA_ANI_WALKING_LEFT;
		break;
	case SOPHIA_ANI_IDLE_LEFT_1:
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->SetCurrentFrame(9);
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_LEFT;
		break;
	case SOPHIA_ANI_IDLE_LEFT_2:
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->SetCurrentFrame(10);
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_LEFT;
		break;
	case SOPHIA_ANI_IDLE_LEFT_3:
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->SetCurrentFrame(3);
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_LEFT;
		break;
	case SOPHIA_ANI_IDLE_LEFT_4:
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->SetCurrentFrame(5);
		animation_set->at(SOPHIA_ANI_WALKING_LEFT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_LEFT;
		break;
	default:
		ani = SOPHIA_ANI_WALKING_LEFT;
		break;
	}
}
void CSophia::RenderWalkingRight(int& ani)
{
	switch (currentAnimation)
	{
	case SOPHIA_ANI_WALKING_RIGHT:
		ani = SOPHIA_ANI_WALKING_RIGHT;
		break;
	case SOPHIA_ANI_IDLE_RIGHT_1:
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->SetCurrentFrame(9);
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_RIGHT;
		break;
	case SOPHIA_ANI_IDLE_RIGHT_2:
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->SetCurrentFrame(10);
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_RIGHT;
		break;
	case SOPHIA_ANI_IDLE_RIGHT_3:
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->SetCurrentFrame(3);
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_RIGHT;
		break;
	case SOPHIA_ANI_IDLE_RIGHT_4:
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->SetCurrentFrame(5);
		animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->ResetFrameTime();
		ani = SOPHIA_ANI_WALKING_RIGHT;
		break;
	default:
		ani = SOPHIA_ANI_WALKING_RIGHT;
		break;
	}
}
void CSophia::RenderIdle(int &ani)
{
	if (nx > 0)
	{
		int frame = animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->GetCurrentFrame();
		//DebugOut(L"%d\n", frame);
		switch (frame)
		{
		case 0: case 4: case 8:
			ani = SOPHIA_ANI_IDLE_RIGHT_1;
			break;
		case 1: case 5: case 9:
			ani = SOPHIA_ANI_IDLE_RIGHT_2;
			break;
		case 2: case 6: case 10:
			ani = SOPHIA_ANI_IDLE_RIGHT_3;
			break;
		case 3: case 7: case 11:
			ani = SOPHIA_ANI_IDLE_RIGHT_4;
			break;
		default:break;
		}
	}
	else
	{
		int frame = animation_set->at(SOPHIA_ANI_WALKING_LEFT)->GetCurrentFrame();
		//DebugOut(L"%d\n", frame);
		switch (frame)
		{
		case 0: case 4: case 8:
			ani = SOPHIA_ANI_IDLE_LEFT_1;
			break;
		case 1: case 5: case 9:
			ani = SOPHIA_ANI_IDLE_LEFT_2;
			break;
		case 2: case 6: case 10:
			ani = SOPHIA_ANI_IDLE_LEFT_3;
			break;
		case 3: case 7: case 11:
			ani = SOPHIA_ANI_IDLE_LEFT_4;
			break;
		default:break;
		}
	}
}
void CSophia::RenderRotating(int& ani)
{
	switch (currentAnimation)
	{
	case SOPHIA_ANI_ROTATING_RIGHT_1: case SOPHIA_ANI_IDLE_RIGHT_1:
		ani = SOPHIA_ANI_ROTATING_RIGHT_1;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_2: case SOPHIA_ANI_IDLE_RIGHT_2:
		ani = SOPHIA_ANI_ROTATING_RIGHT_2;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_3: case SOPHIA_ANI_IDLE_RIGHT_3:
		ani = SOPHIA_ANI_ROTATING_RIGHT_3;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_4: case SOPHIA_ANI_IDLE_RIGHT_4:
		ani = SOPHIA_ANI_ROTATING_RIGHT_4;
		break;
	case SOPHIA_ANI_WALKING_RIGHT:
	{
		switch (animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->GetCurrentFrame())
		{
		case 0: case 4: case 8:
			ani = SOPHIA_ANI_ROTATING_RIGHT_1;
			break;
		case 1: case 5: case 9:
			ani = SOPHIA_ANI_ROTATING_RIGHT_2;
			break;
		case 2: case 6: case 10:
			ani = SOPHIA_ANI_ROTATING_RIGHT_3;
			break;
		case 3: case 7: case 11:
			ani = SOPHIA_ANI_ROTATING_RIGHT_4;
			break;
		default:break;
		}
	}
	break;
	case SOPHIA_ANI_ROTATING_LEFT_1: case SOPHIA_ANI_IDLE_LEFT_1:
		ani = SOPHIA_ANI_ROTATING_LEFT_1;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_2: case SOPHIA_ANI_IDLE_LEFT_2:
		ani = SOPHIA_ANI_ROTATING_LEFT_2;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_3: case SOPHIA_ANI_IDLE_LEFT_3:
		ani = SOPHIA_ANI_ROTATING_LEFT_3;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_4: case SOPHIA_ANI_IDLE_LEFT_4:
		ani = SOPHIA_ANI_ROTATING_LEFT_4;
		break;
	case SOPHIA_ANI_WALKING_LEFT:
	{
		switch (animation_set->at(SOPHIA_ANI_WALKING_LEFT)->GetCurrentFrame())
		{
		case 0: case 4: case 8:
			ani = SOPHIA_ANI_ROTATING_LEFT_1;
			break;
		case 1: case 5: case 9:
			ani = SOPHIA_ANI_ROTATING_LEFT_2;
			break;
		case 2: case 6: case 10:
			ani = SOPHIA_ANI_ROTATING_LEFT_3;
			break;
		case 3: case 7: case 11:
			ani = SOPHIA_ANI_ROTATING_LEFT_4;
			break;
		default:break;
		}
	}
	default:break;
	}
}