#pragma once
#include "Player.h"
#include "..\Bullet\JasonBullet.h"
#include "..\..\Animations\RenderEffect.h"
#include "..\..\Scene\CSceneManager.h"
#include "..\Portal.h"

#define JASON_WALKING_SPEED 0.05f
#define JASON_JUMP_SPEED_Y 0.175f
#define JASON_JUMPIN_SPEED_Y 0.1f
#define JASON_GRAVITY 0.0005f
#define JASON_FRICTION 0.01f
#define JASON_RELOAD_TIME 100
#define JASON_MAX_HEALTH 100
#define JASON_UNTOUCHABLE_TIME 1000
#define JASON_BBOX_HEIGHT	17
#define JASON_BBOX_WIDTH	10

#define JASON_STATE_WALKING_LEFT	0
#define JASON_STATE_WALKING_RIGHT	1
#define JASON_STATE_IDLE_LEFT	2
#define JASON_STATE_IDLE_RIGHT	3
#define JASON_STATE_JUMP	5
#define JASON_STATE_JUMPIN	7
#define JASON_STATE_ATTACKED 8
#define JASON_STATE_DIE 9
#define JASON_STATE_INSOPHIA 10

#define JASON_ANI_WALKING_LEFT	0
#define JASON_ANI_WALKING_RIGHT	1
#define JASON_ANI_IDLE_LEFT	2
#define JASON_ANI_IDLE_RIGHT	3

class CJason : public CPlayer
{
private:
	CRenderEffect* untouchableEffect;
public:
	CJason();
	float backUpY;
	bool isJumpingIn = false;
	bool isJumping = false;
	bool isFalling = false;
	bool isInSophia = true;
	void Fire(float Direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetState(int state);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void UpdateStateTime();
};

