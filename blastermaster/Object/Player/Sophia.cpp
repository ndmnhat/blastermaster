#include "Sophia.h"

CSophia::CSophia()
{
	CSophia::SetState(SOPHIA_STATE_IDLE_RIGHT);
}

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
						{
							x += dx;
						}
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
	//Set falling flag
	if (round(vy * 10) / 10 < 0.0f)
		isFalling = true;
	else
		isFalling = false;
	//Gun up handle
	if (isPressingUp == true && isGunUp == false)
	{
		isLiftingGun = true;
	}

	if (isPressingUp == false && isGunUp == true)
	{
		isLiftingGun = false;
		isLoweringGun = true;
	}

	if (isLiftingGun)
	{
		if (currentAnimation == SOPHIA_ANI_LIFTING_RIGHT || currentAnimation == SOPHIA_ANI_LIFTING_LEFT)
		{
			int frame = animation_set->at(currentAnimation)->GetCurrentFrame();
			//DebugOut(L"%d\n", frame);
			if (frame == 3 || frame == 7 || frame == 11 || frame == 15)
			{
				isLiftingGun = false;
				isGunUp = true;
			}
		}
	}

	if (isLoweringGun)
	{
		if (currentAnimation == SOPHIA_ANI_LOWERING_RIGHT || currentAnimation == SOPHIA_ANI_LOWERING_LEFT)
		{
			int frame = animation_set->at(currentAnimation)->GetCurrentFrame();
			//DebugOut(L"%d\n", frame);
			if (frame == 2 || frame == 5 || frame == 8 || frame == 11)
			{
				isLoweringGun = false;
				isGunUp = false;
			}
		}
	}
	DebugOut(L"%d, %d, %d\n", isLiftingGun, isGunUp, isLoweringGun);
}

void CSophia::Render()
{
	int ani = -1;
	float xdraw, ydraw;
	xdraw = x; //Default x draw
	ydraw = y; //Default y draw

	if (roundf(vx * 100)/100==0.00f)
	{
		RenderIdle(ani);
	}
	else
	{
		if (nx > 0)
			RenderWalkingRight(ani);
		else
			RenderWalkingLeft(ani);
	}
	if (isJumping)
	{
		RenderJumping(ani);
	}
	if (isFalling)
	{
		RenderFalling(ani);
	}
	if (isRotating)
	{
		if (!isJumping) //Not jumping
			RenderRotating(ani);
		else
			RenderRotatingWhileJumping(ani);
	}
	if (isLiftingGun)
	{
		RenderLiftingGun(ani, xdraw, ydraw);
	}
	if (isGunUp&&!isLoweringGun) //Not lowering gun
	{
		RenderGunUp(ani, xdraw, ydraw);
	}
	if (isLoweringGun)
	{
		RenderLoweringGun(ani, xdraw, ydraw);
	}
	if (ani != -1)
		currentAnimation = ani;
	animation_set->at(currentAnimation)->Render(xdraw, ydraw);
	RenderBoundingBox();
	//DebugOut(L"%d\n",isLiftingGun);
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
		//if (!isJumping&&!isFalling)
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
	float left, right, top, bot;
	GetBoundingBox(left, right, top, bot);
	//DebugOut(L"left: %f, right: %f, top: %f, bot: %f\n", left, right, top, bot);
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
	//if (isLiftingGun && (GetTickCount() - gunUpStart > 150))
	//{
	//	gunUpStart = 0;
	//	isLiftingGun = false;
	//	isGunUp = true;
	//}
}

void CSophia::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = left + SOPHIA_BBOX_WIDTH;
	bottom = top - SOPHIA_BBOX_HEIGHT;
}

void CSophia::RenderWalkingLeft(int &ani)
{
	if (nx < 0)
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
	//else //Walking backward
	//{
	//	ani = SOPHIA_ANI_WALKING_RIGHT_BACKWARD;
	//}
}

void CSophia::RenderWalkingRight(int& ani)
{
	if (nx > 0)
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
	//else //Walking backward
	//{
	//	ani = SOPHIA_ANI_WALKING_LEFT_BACKWARD;
	//}
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
		default:
			ani = SOPHIA_ANI_IDLE_RIGHT_1;
			break;
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
		default:
			ani = SOPHIA_ANI_IDLE_LEFT_1;
			break;
		}
	}
}

void CSophia::RenderRotating(int& ani)
{
	switch (currentAnimation)
	{
	//RIGHT
	//IDLE
	case SOPHIA_ANI_ROTATING_RIGHT_1: case SOPHIA_ANI_IDLE_RIGHT_1: case SOPHIA_ANI_IDLE_RIGHT_FALL_1:
		ani = SOPHIA_ANI_ROTATING_RIGHT_1;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_2: case SOPHIA_ANI_IDLE_RIGHT_2: case SOPHIA_ANI_IDLE_RIGHT_FALL_2:
		ani = SOPHIA_ANI_ROTATING_RIGHT_2;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_3: case SOPHIA_ANI_IDLE_RIGHT_3: case SOPHIA_ANI_IDLE_RIGHT_FALL_3:
		ani = SOPHIA_ANI_ROTATING_RIGHT_3;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_4: case SOPHIA_ANI_IDLE_RIGHT_4: case SOPHIA_ANI_IDLE_RIGHT_FALL_4:
		ani = SOPHIA_ANI_ROTATING_RIGHT_4;
		break;
	//WALK
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
	//FALL
	case SOPHIA_ANI_WALKING_RIGHT_FALL:
	{
		switch (animation_set->at(SOPHIA_ANI_WALKING_RIGHT)->GetCurrentFrame())
		{
		case 0:
			ani = SOPHIA_ANI_ROTATING_RIGHT_1;
			break;
		case 1:
			ani = SOPHIA_ANI_ROTATING_RIGHT_2;
			break;
		case 2:
			ani = SOPHIA_ANI_ROTATING_RIGHT_3;
			break;
		case 3:
			ani = SOPHIA_ANI_ROTATING_RIGHT_4;
			break;
		default:break;
		}
	}
	break;
	//LEFT
	//IDLE
	case SOPHIA_ANI_ROTATING_LEFT_1: case SOPHIA_ANI_IDLE_LEFT_1:case SOPHIA_ANI_IDLE_LEFT_FALL_1:
		ani = SOPHIA_ANI_ROTATING_LEFT_1;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_2: case SOPHIA_ANI_IDLE_LEFT_2:case SOPHIA_ANI_IDLE_LEFT_FALL_2:
		ani = SOPHIA_ANI_ROTATING_LEFT_2;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_3: case SOPHIA_ANI_IDLE_LEFT_3:case SOPHIA_ANI_IDLE_LEFT_FALL_3:
		ani = SOPHIA_ANI_ROTATING_LEFT_3;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_4: case SOPHIA_ANI_IDLE_LEFT_4:case SOPHIA_ANI_IDLE_LEFT_FALL_4:
		ani = SOPHIA_ANI_ROTATING_LEFT_4;
		break;
	//WALK
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
	break;
	//FALL
	case SOPHIA_ANI_WALKING_LEFT_FALL:
	{
		switch (animation_set->at(SOPHIA_ANI_WALKING_LEFT)->GetCurrentFrame())
		{
		case 0:
			ani = SOPHIA_ANI_ROTATING_LEFT_1;
			break;
		case 1:
			ani = SOPHIA_ANI_ROTATING_LEFT_2;
			break;
		case 2:
			ani = SOPHIA_ANI_ROTATING_LEFT_3;
			break;
		case 3:
			ani = SOPHIA_ANI_ROTATING_LEFT_4;
			break;
		default:break;
		}
	}
	break;
	default:break;
	}
}

void CSophia::RenderJumping(int& ani)
{
	if (roundf(vx * 100) / 100 == 0.00f)
	{
		if (nx > 0) //Idle right jump
		{
			switch (currentAnimation)
			{
			case SOPHIA_ANI_IDLE_RIGHT_1: case SOPHIA_ANI_IDLE_RIGHT_JUMP_1:
				ani = SOPHIA_ANI_IDLE_RIGHT_JUMP_1;
				break;
			case SOPHIA_ANI_IDLE_RIGHT_2: case SOPHIA_ANI_IDLE_RIGHT_JUMP_2:
				ani = SOPHIA_ANI_IDLE_RIGHT_JUMP_2;
				break;
			case SOPHIA_ANI_IDLE_RIGHT_3: case SOPHIA_ANI_IDLE_RIGHT_JUMP_3:
				ani = SOPHIA_ANI_IDLE_RIGHT_JUMP_3;
				break;
			case SOPHIA_ANI_IDLE_RIGHT_4: case SOPHIA_ANI_IDLE_RIGHT_JUMP_4:
				ani = SOPHIA_ANI_IDLE_RIGHT_JUMP_4;
				break;
			}
		}
		else //Idle left jump
		{
			switch (currentAnimation)
			{
			case SOPHIA_ANI_IDLE_LEFT_1: case SOPHIA_ANI_IDLE_LEFT_JUMP_1:
				ani = SOPHIA_ANI_IDLE_LEFT_JUMP_1;
				break;
			case SOPHIA_ANI_IDLE_LEFT_2: case SOPHIA_ANI_IDLE_LEFT_JUMP_2:
				ani = SOPHIA_ANI_IDLE_LEFT_JUMP_2;
				break;
			case SOPHIA_ANI_IDLE_LEFT_3: case SOPHIA_ANI_IDLE_LEFT_JUMP_3:
				ani = SOPHIA_ANI_IDLE_LEFT_JUMP_3;
				break;
			case SOPHIA_ANI_IDLE_LEFT_4: case SOPHIA_ANI_IDLE_LEFT_JUMP_4:
				ani = SOPHIA_ANI_IDLE_LEFT_JUMP_4;
				break;
			}
		}
	}
	else if (vx > 0)
	{
		if (nx > 0)
			ani = SOPHIA_ANI_WALKING_RIGHT_JUMP;
		else //Bouncing back
			ani = SOPHIA_ANI_WALKING_LEFT_JUMP;
	}
	else if (vx < 0)
	{
		if (nx < 0)
			ani = SOPHIA_ANI_WALKING_LEFT_JUMP;
		else //Bouncing back
			ani = SOPHIA_ANI_WALKING_RIGHT_JUMP;
	}
}

void CSophia::RenderFalling(int& ani)
{
	if (roundf(vx * 100) / 100 == 0.00f)
	{
		if (nx > 0) //Idle right fall
		{
			switch (currentAnimation)
			{
			case SOPHIA_ANI_IDLE_RIGHT_1: case SOPHIA_ANI_IDLE_RIGHT_JUMP_1: case SOPHIA_ANI_IDLE_RIGHT_FALL_1:
				ani = SOPHIA_ANI_IDLE_RIGHT_FALL_1;
				break;
			case SOPHIA_ANI_IDLE_RIGHT_2: case SOPHIA_ANI_IDLE_RIGHT_JUMP_2: case SOPHIA_ANI_IDLE_RIGHT_FALL_2:
				ani = SOPHIA_ANI_IDLE_RIGHT_FALL_2;
				break;
			case SOPHIA_ANI_IDLE_RIGHT_3: case SOPHIA_ANI_IDLE_RIGHT_JUMP_3: case SOPHIA_ANI_IDLE_RIGHT_FALL_3:
				ani = SOPHIA_ANI_IDLE_RIGHT_FALL_3;
				break;
			case SOPHIA_ANI_IDLE_RIGHT_4: case SOPHIA_ANI_IDLE_RIGHT_JUMP_4: case SOPHIA_ANI_IDLE_RIGHT_FALL_4:
				ani = SOPHIA_ANI_IDLE_RIGHT_FALL_4;
				break;
			}
		}
		else //Idle left fall
		{
			switch (currentAnimation)
			{
			case SOPHIA_ANI_IDLE_LEFT_1: case SOPHIA_ANI_IDLE_LEFT_JUMP_1: case SOPHIA_ANI_IDLE_LEFT_FALL_1:
				ani = SOPHIA_ANI_IDLE_LEFT_FALL_1;
				break;
			case SOPHIA_ANI_IDLE_LEFT_2: case SOPHIA_ANI_IDLE_LEFT_JUMP_2: case SOPHIA_ANI_IDLE_LEFT_FALL_2:
				ani = SOPHIA_ANI_IDLE_LEFT_FALL_2;
				break;
			case SOPHIA_ANI_IDLE_LEFT_3: case SOPHIA_ANI_IDLE_LEFT_JUMP_3: case SOPHIA_ANI_IDLE_LEFT_FALL_3:
				ani = SOPHIA_ANI_IDLE_LEFT_FALL_3;
				break;
			case SOPHIA_ANI_IDLE_LEFT_4: case SOPHIA_ANI_IDLE_LEFT_JUMP_4: case SOPHIA_ANI_IDLE_LEFT_FALL_4:
				ani = SOPHIA_ANI_IDLE_LEFT_FALL_4;
				break;
			}
		}
	}
	else if (vx > 0) //Walk right fall
	{
		if (nx > 0)
			ani = SOPHIA_ANI_WALKING_RIGHT_FALL;
		else //Bouncing back
			ani = SOPHIA_ANI_WALKING_LEFT_FALL;
	}
	else if (vx < 0) //Walk left fall
	{
		if (nx < 0)
			ani = SOPHIA_ANI_WALKING_LEFT_FALL;
		else //Bouncing back
			ani = SOPHIA_ANI_WALKING_RIGHT_FALL;
	}
}

void CSophia::RenderRotatingWhileJumping(int& ani)
{
	switch (currentAnimation)
	{
	//RIGHT
	//IDLE
	case SOPHIA_ANI_ROTATING_RIGHT_JUMP_1: case SOPHIA_ANI_IDLE_RIGHT_JUMP_1:
		ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_1;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_JUMP_2: case SOPHIA_ANI_IDLE_RIGHT_JUMP_2:
		ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_2;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_JUMP_3: case SOPHIA_ANI_IDLE_RIGHT_JUMP_3:
		ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_3;
		break;
	case SOPHIA_ANI_ROTATING_RIGHT_JUMP_4: case SOPHIA_ANI_IDLE_RIGHT_JUMP_4:
		ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_4;
		break;
		//WALK
	case SOPHIA_ANI_WALKING_RIGHT_JUMP:
	{
		switch (animation_set->at(SOPHIA_ANI_WALKING_RIGHT_JUMP)->GetCurrentFrame())
		{
		case 0:
			ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_1;
			break;
		case 1:
			ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_2;
			break;
		case 2:
			ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_3;
			break;
		case 3:
			ani = SOPHIA_ANI_ROTATING_RIGHT_JUMP_4;
			break;
		default:break;
		}
	}
	break;
	//LEFT
	//IDLE
	case SOPHIA_ANI_ROTATING_LEFT_JUMP_1: case SOPHIA_ANI_IDLE_LEFT_JUMP_1:
		ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_1;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_JUMP_2: case SOPHIA_ANI_IDLE_LEFT_JUMP_2:
		ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_2;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_JUMP_3: case SOPHIA_ANI_IDLE_LEFT_JUMP_3:
		ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_3;
		break;
	case SOPHIA_ANI_ROTATING_LEFT_JUMP_4: case SOPHIA_ANI_IDLE_LEFT_JUMP_4:
		ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_4;
		break;
		//WALK
	case SOPHIA_ANI_WALKING_LEFT_JUMP:
	{
		switch (animation_set->at(SOPHIA_ANI_WALKING_LEFT_JUMP)->GetCurrentFrame())
		{
		case 0:
			ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_1;
			break;
		case 1:
			ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_2;
			break;
		case 2:
			ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_3;
			break;
		case 3:
			ani = SOPHIA_ANI_ROTATING_LEFT_JUMP_4;
			break;
		default:break;
		}
	}
	break;
	default:break;
	}
}

void CSophia::RenderLiftingGun(int& ani, float &xdraw, float &ydraw)
{
	int currentFrameIndex = animation_set->at(currentAnimation)->GetCurrentFrame();
	if (currentAnimation != SOPHIA_ANI_LIFTING_LEFT && currentAnimation != SOPHIA_ANI_LIFTING_RIGHT) //Not lift yet
	{
		if (nx > 0)	//Right
		{
			ani = SOPHIA_ANI_LIFTING_RIGHT;
		}
		else //Left
		{
			ani = SOPHIA_ANI_LIFTING_LEFT;
		}

		//Set frame
		if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_1 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 0 || currentFrameIndex == 4 || currentFrameIndex == 8) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 0||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 0 || currentFrameIndex == 4 || currentFrameIndex == 8) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 0)
		{
			animation_set->at(ani)->SetCurrentFrame(0);
			animation_set->at(ani)->ResetFrameTime();
		}
		else if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_2 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 1 || currentFrameIndex == 5 || currentFrameIndex == 9) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 1||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 1 || currentFrameIndex == 5 || currentFrameIndex == 9) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 1)
		{
			animation_set->at(ani)->SetCurrentFrame(4);
			animation_set->at(ani)->ResetFrameTime();
		}
		else if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_3 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 2 || currentFrameIndex == 6 || currentFrameIndex == 10) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 2||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 2 || currentFrameIndex == 6 || currentFrameIndex == 10) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 2)
		{
			animation_set->at(ani)->SetCurrentFrame(8);
			animation_set->at(ani)->ResetFrameTime();
		}
		else if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_4 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 3 || currentFrameIndex == 7 || currentFrameIndex == 11) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 3 ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 3 || currentFrameIndex == 7 || currentFrameIndex == 11) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 3)
		{
			animation_set->at(ani)->SetCurrentFrame(12);
			animation_set->at(ani)->ResetFrameTime();
		}
		//Change y draw
		ydraw += 8;
		return;
	}
	else //Lifting
	{	
		if (animation_set->at(currentAnimation)->GetPassedFrameTime() < animation_set->at(currentAnimation)->GetFrameAt(currentFrameIndex)->GetTime())
		{
			ani = currentAnimation;
			//Change ydraw
			switch (currentFrameIndex)
			{
			case 0: case 4: case 8: case 12:
				ydraw += 8;
				break;
			case 1: case 5: case 9: case 13:
				ydraw += 10;
				break;
			case 2: case 6: case 10: case 14:
				ydraw += 12;
				break;
			case 3: case 7: case 11: case 15:
				ydraw += 16;
				break;
			}
			return;
		}
		else
		{
			int newFrameIndex = currentFrameIndex + 1;
			if (nx > 0)
			{
				ani = SOPHIA_ANI_LIFTING_RIGHT;
				if (currentAnimation == SOPHIA_ANI_LIFTING_LEFT) //Rotating
				{
					animation_set->at(ani)->SetCurrentFrame(newFrameIndex);
					animation_set->at(ani)->ResetFrameTime();
				}
			}
			else
			{
				ani = SOPHIA_ANI_LIFTING_LEFT;
				if (currentAnimation == SOPHIA_ANI_LIFTING_RIGHT) //Rotating
				{
					animation_set->at(ani)->SetCurrentFrame(newFrameIndex);
					animation_set->at(ani)->ResetFrameTime();
				}
			}
			if (roundf(vx * 100) / 100 == 0.00f)
			{
				newFrameIndex = (currentFrameIndex - 3 + 16) % 16;
				animation_set->at(ani)->SetCurrentFrame(newFrameIndex);
				animation_set->at(ani)->ResetFrameTime();
			}
			//Change ydraw
			switch (newFrameIndex)
			{
			case 0: case 4: case 8: case 12:
				ydraw += 8;
				break;
			case 1: case 5: case 9: case 13:
				ydraw += 10;
				break;
			case 2: case 6: case 10: case 14:
				ydraw += 12;
				break;
			case 3: case 7: case 11: case 15:
				ydraw += 16;
				break;
			}
			return;
		}
	}
}

void CSophia::RenderLoweringGun(int& ani, float& xdraw, float& ydraw)
{
	int currentFrame = animation_set->at(currentAnimation)->GetCurrentFrame();
	int newFrame = 0;
	if (currentAnimation != SOPHIA_ANI_LOWERING_LEFT && currentAnimation != SOPHIA_ANI_LOWERING_RIGHT)
	{
		if (nx < 0)
			ani = SOPHIA_ANI_LOWERING_LEFT;
		else
			ani = SOPHIA_ANI_LOWERING_RIGHT;
		if (currentAnimation == SOPHIA_ANI_WALKING_LEFT_GUNUP || currentAnimation == SOPHIA_ANI_WALKING_RIGHT_GUNUP)
		{
			switch (currentFrame)
			{
			case 0:
				newFrame = 0;
				break;
			case 1:
				newFrame = 3;
				break;
			case 2:
				newFrame = 6;
				break;
			case 3:
				newFrame = 9;
				break;
			default:
				break;
			}
		}
		animation_set->at(ani)->SetCurrentFrame(newFrame);
		animation_set->at(ani)->ResetFrameTime();
		ydraw += 12;
		return;
	}
	else if (currentAnimation == SOPHIA_ANI_LOWERING_LEFT || currentAnimation == SOPHIA_ANI_LOWERING_RIGHT)
	{
		if (animation_set->at(currentAnimation)->GetPassedFrameTime() < animation_set->at(currentAnimation)->GetFrameAt(currentFrame)->GetTime())
		{
			ani = currentAnimation;
			//Change ydraw
			switch (currentFrame)
			{
			case 0: case 3: case 6: case 9:
				ydraw += 12;
				break;
			case 1: case 4: case 7: case 10:
				ydraw += 10;
				break;
			case 2: case 5: case 8: case 11:
				ydraw += 8;
				break;
			}
			return;
		}
		else
		{
			newFrame = currentFrame + 1;
			if (nx > 0)
			{
				ani = SOPHIA_ANI_LOWERING_RIGHT;
				if (currentAnimation == SOPHIA_ANI_LOWERING_LEFT) //Rotating
				{
					animation_set->at(ani)->SetCurrentFrame(newFrame);
					animation_set->at(ani)->ResetFrameTime();
				}
			}
			else
			{
				ani = SOPHIA_ANI_LOWERING_LEFT;
				if (currentAnimation == SOPHIA_ANI_LOWERING_RIGHT) //Rotating
				{
					animation_set->at(ani)->SetCurrentFrame(newFrame);
					animation_set->at(ani)->ResetFrameTime();
				}
			}
			if (roundf(vx * 100) / 100 == 0.00f)
			{
				newFrame = (currentFrame - 2 + 12) % 12;
				animation_set->at(ani)->SetCurrentFrame(newFrame);
				animation_set->at(ani)->ResetFrameTime();
			}
			//Change ydraw
			switch (newFrame)
			{
			case 0: case 3: case 6: case 9:
				ydraw += 12;
				break;
			case 1: case 4: case 7: case 10:
				ydraw += 10;
				break;
			case 2: case 5: case 8: case 11:
				ydraw += 8;
				break;
			}
			return;
		}
	}

}

void CSophia::RenderGunUp(int& ani, float& xdraw, float& ydraw)
{
	int currentFrameIndex = animation_set->at(currentAnimation)->GetCurrentFrame();
	if (currentAnimation != SOPHIA_ANI_WALKING_LEFT_GUNUP && currentAnimation != SOPHIA_ANI_WALKING_RIGHT_GUNUP)
	{
		if (nx > 0)
			ani = SOPHIA_ANI_WALKING_RIGHT_GUNUP;
		else
			ani = SOPHIA_ANI_WALKING_LEFT_GUNUP;

		if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_1 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_1 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 0 || currentFrameIndex == 4 || currentFrameIndex == 8) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 0 ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 0 || currentFrameIndex == 4 || currentFrameIndex == 8) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 0||
			currentAnimation == SOPHIA_ANI_LIFTING_RIGHT && currentFrameIndex == 7 ||
			currentAnimation == SOPHIA_ANI_LIFTING_LEFT && currentFrameIndex == 7)
		{
			animation_set->at(ani)->SetCurrentFrame(0);
			animation_set->at(ani)->ResetFrameTime();\
		}
		else if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_2 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_2 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 1 || currentFrameIndex == 5 || currentFrameIndex == 9) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 1 ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 1 || currentFrameIndex == 5 || currentFrameIndex == 9) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 1||
			currentAnimation == SOPHIA_ANI_LIFTING_RIGHT && currentFrameIndex == 11 ||
			currentAnimation == SOPHIA_ANI_LIFTING_LEFT && currentFrameIndex == 11)
		{
			animation_set->at(ani)->SetCurrentFrame(1);
			animation_set->at(ani)->ResetFrameTime();\
		}
		else if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_3 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_3 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 2 || currentFrameIndex == 6 || currentFrameIndex == 10) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 2 ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 2 || currentFrameIndex == 6 || currentFrameIndex == 10) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 2||
			currentAnimation == SOPHIA_ANI_LIFTING_RIGHT && currentFrameIndex == 15 ||
			currentAnimation == SOPHIA_ANI_LIFTING_LEFT && currentFrameIndex == 15)
		{
			animation_set->at(ani)->SetCurrentFrame(2);
			animation_set->at(ani)->ResetFrameTime();
		}
		else if (currentAnimation == SOPHIA_ANI_IDLE_RIGHT_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_FALL_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_RIGHT_JUMP_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_FALL_4 ||
			currentAnimation == SOPHIA_ANI_IDLE_LEFT_JUMP_4 ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT && (currentFrameIndex == 3 || currentFrameIndex == 7 || currentFrameIndex == 11) ||
			currentAnimation == SOPHIA_ANI_WALKING_RIGHT_JUMP && currentFrameIndex == 3 ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT && (currentFrameIndex == 3 || currentFrameIndex == 7 || currentFrameIndex == 11) ||
			currentAnimation == SOPHIA_ANI_WALKING_LEFT_JUMP && currentFrameIndex == 3||
			currentAnimation == SOPHIA_ANI_LIFTING_RIGHT && currentFrameIndex == 3 ||
			currentAnimation == SOPHIA_ANI_LIFTING_LEFT && currentFrameIndex == 3)
		{
			animation_set->at(ani)->SetCurrentFrame(3);
			animation_set->at(ani)->ResetFrameTime();
		}
	}
	else
	{
		if (roundf(vx * 100) / 100 == 0.00f)
		{
			if (nx > 0)
				ani = SOPHIA_ANI_WALKING_RIGHT_GUNUP;
			else
				ani = SOPHIA_ANI_WALKING_LEFT_GUNUP;
			animation_set->at(ani)->SetCurrentFrame(currentFrameIndex);
			animation_set->at(ani)->ResetFrameTime();
		}
		else if (vx > 0)
		{
			ani = SOPHIA_ANI_WALKING_RIGHT_GUNUP;
		}
		else if (vx < 0)
		{
			ani = SOPHIA_ANI_WALKING_LEFT_GUNUP;
		}
	}
	//Change ydraw
	ydraw += 16;
}
