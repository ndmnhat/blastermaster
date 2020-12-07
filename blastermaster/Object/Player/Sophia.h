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

#define SOPHIA_ANI_IDLE_LEFT_JUMP_1 8
#define SOPHIA_ANI_IDLE_LEFT_JUMP_2 9
#define SOPHIA_ANI_IDLE_LEFT_JUMP_3 10
#define SOPHIA_ANI_IDLE_LEFT_JUMP_4 11

#define SOPHIA_ANI_IDLE_RIGHT_JUMP_1 12
#define SOPHIA_ANI_IDLE_RIGHT_JUMP_2 13
#define SOPHIA_ANI_IDLE_RIGHT_JUMP_3 14
#define SOPHIA_ANI_IDLE_RIGHT_JUMP_4 15

#define SOPHIA_ANI_IDLE_LEFT_FALL_1 16
#define SOPHIA_ANI_IDLE_LEFT_FALL_2 17
#define SOPHIA_ANI_IDLE_LEFT_FALL_3 18
#define SOPHIA_ANI_IDLE_LEFT_FALL_4 19

#define SOPHIA_ANI_IDLE_RIGHT_FALL_1 20
#define SOPHIA_ANI_IDLE_RIGHT_FALL_2 21
#define SOPHIA_ANI_IDLE_RIGHT_FALL_3 22
#define SOPHIA_ANI_IDLE_RIGHT_FALL_4 23

#define SOPHIA_ANI_WALKING_LEFT 24
#define SOPHIA_ANI_WALKING_LEFT_BACKWARD 25
#define SOPHIA_ANI_WALKING_RIGHT 26
#define SOPHIA_ANI_WALKING_RIGHT_BACKWARD 27

#define SOPHIA_ANI_WALKING_LEFT_JUMP 28
#define SOPHIA_ANI_WALKING_RIGHT_JUMP 29

#define SOPHIA_ANI_WALKING_LEFT_FALL 30
#define SOPHIA_ANI_WALKING_RIGHT_FALL 31

#define SOPHIA_ANI_ROTATING_LEFT_1 32
#define SOPHIA_ANI_ROTATING_LEFT_2 33
#define SOPHIA_ANI_ROTATING_LEFT_3 34
#define SOPHIA_ANI_ROTATING_LEFT_4 35

#define SOPHIA_ANI_ROTATING_RIGHT_1 36
#define SOPHIA_ANI_ROTATING_RIGHT_2 37
#define SOPHIA_ANI_ROTATING_RIGHT_3 38
#define SOPHIA_ANI_ROTATING_RIGHT_4 39

#define SOPHIA_ANI_ROTATING_LEFT_JUMP_1 40
#define SOPHIA_ANI_ROTATING_LEFT_JUMP_2 41
#define SOPHIA_ANI_ROTATING_LEFT_JUMP_3 42
#define SOPHIA_ANI_ROTATING_LEFT_JUMP_4 43

#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_1 44
#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_2 45
#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_3 46
#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_4 47

#define SOPHIA_UNTOUCHABLE_TIME 1000

#define SOPHIA_BBOX_WIDTH 26
#define SOPHIA_BBOX_HEIGHT 18


class CSophia : public CGameObject
{
	static CSophia* __instance; // Singleton Patern
	DWORD untouchableStart;
	DWORD rotatingStart;
	DWORD gunUpStart;
	int currentAnimation;
	void RenderWalkingLeft(int& ani);
	void RenderWalkingRight(int& ani);
	void RenderIdle(int& ani);
	void RenderRotating(int& ani);
	void RenderJumping(int& ani);
	void RenderFalling(int& ani);
	void RenderRotatingWhileJumping(int& ani);
public:
	bool isRotating;
	bool isUntouchable;
	bool isFalling;
	bool isGunUp = false;
	bool isLiftingGun = false;
	bool isPressingUp = false;
	bool isJumping = false;
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdateStateTime();
	void StartUntouchable() { isUntouchable = true; untouchableStart = GetTickCount(); }
};