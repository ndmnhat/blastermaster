#pragma once
#include "OutdoorEnemy.h"
#include "..\Player\Sophia.h"
#include "..\..\Scene\SceneGame.h"
#include "..\Bullet\JasonBullet.h"
#include "..\..\Game\Game.h"

#define WORM_WALKING_SPEED	0.025f
#define WORM_GRAVITY		0.15f

#define WORM_STATE_WALKING_LEFT		100
#define WORM_STATE_WALKING_RIGHT	200

#define WORM_ANI_FALLING_LEFT	0
#define WORM_ANI_FALLING_RIGHT	1	
#define WORM_ANI_WALKING_LEFT	2
#define WORM_ANI_WALKING_RIGHT	3

#define WORM_BBOX_WIDTH		18
#define WORM_BBOX_HEIGHT	10

class CWorm : public COutdoorEnemy
{
public:
	bool isFalling = false;

	CWorm();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

