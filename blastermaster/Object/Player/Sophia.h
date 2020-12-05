#pragma once
#include "..\GameObject.h"
#include "..\..\Utils\Utils.h"
#define SOPHIA_WALKING_SPEED 0.07f
#define SOPHIA_JUMP_SPEED_Y 0.25f
#define SOPHIA_GRAVITY 0.0005f
#define SOPHIA_FRICTION 0.01f

//STATE
#define SOPHIA_STATE_IDLE_LEFT 0
#define SOPHIA_STATE_IDLE_RIGHT 1
#define SOPHIA_STATE_WALKING_RIGHT 2
#define SOPHIA_STATE_WALKING_LEFT 3

#define SOPHIA_STATE_JUMP 4
#define SOPHIA_STATE_DIE 5
#define SOPHIA_STATE_ATTACKED 6

//ANIMATION
#define SOPHIA_ANI_IDLE_LEFT_1 0
#define SOPHIA_ANI_IDLE_LEFT_2 1
#define SOPHIA_ANI_IDLE_LEFT_3 2
#define SOPHIA_ANI_IDLE_LEFT_4 3

#define SOPHIA_ANI_IDLE_RIGHT_1 4
#define SOPHIA_ANI_IDLE_RIGHT_2 5
#define SOPHIA_ANI_IDLE_RIGHT_3 6
#define SOPHIA_ANI_IDLE_RIGHT_4 7

#define SOPHIA_ANI_WALKING_LEFT 8
#define SOPHIA_ANI_WALKING_RIGHT 9

#define SOPHIA_ANI_ROTATING_LEFT_1 10
#define SOPHIA_ANI_ROTATING_LEFT_2 11
#define SOPHIA_ANI_ROTATING_LEFT_3 12
#define SOPHIA_ANI_ROTATING_LEFT_4 13

#define SOPHIA_ANI_ROTATING_RIGHT_1 14
#define SOPHIA_ANI_ROTATING_RIGHT_2 15
#define SOPHIA_ANI_ROTATING_RIGHT_3 16
#define SOPHIA_ANI_ROTATING_RIGHT_4 17

#define SOPHIA_UNTOUCHABLE_TIME 1000

#define SOPHIA_BBOX_WIDTH 26
#define SOPHIA_BBOX_HEIGHT 18


class CSophia : public CGameObject
{
	static CSophia* __instance; // Singleton Patern
	DWORD untouchableStart;
	DWORD rotatingStart;
	int currentAnimation;
	void RenderWalkingLeft(int& ani);
	void RenderWalkingRight(int& ani);
	void RenderIdle(int& ani);
	void RenderRotating(int& ani);

public:
	bool isRotating;
	bool isUntouchable;
	bool isFalling;
	bool isJumping = false;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdateStateTime();
	void StartUntouchable() { isUntouchable = true; untouchableStart = GetTickCount(); }
};