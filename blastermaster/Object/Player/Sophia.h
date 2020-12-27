#pragma once
#include "Player.h"
#include "..\Bullet\SophiaBullet.h"
#include "..\..\Animations\RenderEffect.h"

#define SOPHIA_WALKING_SPEED 0.07f
#define SOPHIA_JUMP_SPEED_Y 0.25f
#define SOPHIA_GRAVITY 0.0005f
#define SOPHIA_FRICTION 0.01f
#define SOPHIA_RELOAD_TIME 100
#define SOPHIA_MAX_HEALTH 100
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

#define SOPHIA_ANI_WALKING_LEFT_GUNUP 32
#define SOPHIA_ANI_WALKING_RIGHT_GUNUP 33

#define SOPHIA_ANI_ROTATING_LEFT_1 34
#define SOPHIA_ANI_ROTATING_LEFT_2 35
#define SOPHIA_ANI_ROTATING_LEFT_3 36
#define SOPHIA_ANI_ROTATING_LEFT_4 37

#define SOPHIA_ANI_ROTATING_RIGHT_1 38
#define SOPHIA_ANI_ROTATING_RIGHT_2 39
#define SOPHIA_ANI_ROTATING_RIGHT_3 40
#define SOPHIA_ANI_ROTATING_RIGHT_4 41

#define SOPHIA_ANI_ROTATING_LEFT_JUMP_1 42
#define SOPHIA_ANI_ROTATING_LEFT_JUMP_2 43
#define SOPHIA_ANI_ROTATING_LEFT_JUMP_3 44
#define SOPHIA_ANI_ROTATING_LEFT_JUMP_4 45

#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_1 46
#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_2 47
#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_3 48
#define SOPHIA_ANI_ROTATING_RIGHT_JUMP_4 49

#define SOPHIA_ANI_LIFTING_RIGHT 50
#define SOPHIA_ANI_LIFTING_LEFT 51

#define SOPHIA_ANI_LOWERING_RIGHT 52
#define SOPHIA_ANI_LOWERING_LEFT 53

#define SOPHIA_ANI_OPENING_RIGHT 54
#define SOPHIA_ANI_OPENING_LEFT 55

#define SOPHIA_UNTOUCHABLE_TIME 1000
#define SOPHIA_ROTATING_TIME 200
#define SOPHIA_OPENING_TIME 250

#define SOPHIA_BBOX_WIDTH 26
#define SOPHIA_BBOX_HEIGHT 18


class CSophia : public CPlayer
{
private:
	DWORD openingStart;
	CRenderEffect* untouchableEffect;
	void RenderWalkingLeft(int& ani);
	void RenderWalkingRight(int& ani);
	void RenderIdle(int& ani);
	void RenderRotating(int& ani);
	void RenderJumping(int& ani);
	void RenderFalling(int& ani);
	void RenderOpening(int& ani, float &ydraw);
	void RenderRotatingWhileJumping(int& ani);
	void RenderLiftingGun(int& ani, float& xdraw, float& ydraw);
	void RenderLoweringGun(int& ani, float& xdraw, float& ydraw);
	void RenderGunUp(int& ani, float& xdraw, float& ydraw);
public:
	void StartOpening() { isOpening = true; openingStart = GetTickCount(); }
	bool isHavingJason = true;
	bool isOpening = false;
	bool isRotating = false;
	bool isFalling = false;
	bool isGunUp = false;
	bool isLiftingGun = false;
	bool isLoweringGun = false;
	bool isPressingUp = false;
	bool isJumping = false;
	void Fire(float Direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void UpdateStateTime();
	CSophia();
};