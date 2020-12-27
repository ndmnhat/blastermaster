#pragma once
#include "Player.h"
#include "..\..\Animations\RenderEffect.h"
#include "..\Bullet\BigJasonBullet.h"
#define BIGJASON_WALKING_SPEED 0.08f
#define BIGJASON_RELOAD_TIME 100
#define BIGJASON_UNTOUCHABLE_TIME 1000
#define BIGJASON_MAX_HEALTH 100
#define BIGJASON_BBOX_HEIGHT	32
#define BIGJASON_BBOX_WIDTH	24

#define BIGJASON_STATE_IDLE_DOWN	0
#define BIGJASON_STATE_IDLE_UP	1
#define BIGJASON_STATE_IDLE_LEFT	2
#define BIGJASON_STATE_IDLE_RIGHT	3
#define BIGJASON_STATE_WALKING_DOWN	4
#define BIGJASON_STATE_WALKING_UP	5
#define BIGJASON_STATE_WALKING_LEFT	6
#define BIGJASON_STATE_WALKING_RIGHT	7
#define BIGJASON_STATE_ATTACKED 8
#define BIGJASON_STATE_DIE 9

#define BIGJASON_ANI_IDLE_DOWN	0
#define BIGJASON_ANI_IDLE_UP	1
#define BIGJASON_ANI_IDLE_LEFT	2
#define BIGJASON_ANI_IDLE_RIGHT	3
#define BIGJASON_ANI_WALKING_DOWN	4
#define BIGJASON_ANI_WALKING_UP	5
#define BIGJASON_ANI_WALKING_LEFT	6
#define BIGJASON_ANI_WALKING_RIGHT	7
#define BIGJASON_ANI_DIE 8

class CBigJason : public CPlayer
{
private:
	CRenderEffect* untouchableEffect;
	int ny;
public:
	CBigJason();
	void Fire(float Direction);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void SetState(int state);
	int Getny() { return ny; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void UpdateStateTime();
};

