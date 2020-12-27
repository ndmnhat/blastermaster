#pragma once
#include "OutdoorEnemy.h"

#define JUMPER_WALKING_SPEED	0.05f
#define JUMPER_JUMPING_SPEED	0.2f
#define JUMPER_GRAVITY			0.0005f

#define JUMPER_BBOX_HEIGHT	26	 
#define JUMPER_BBOX_WIDTH	17 

#define JUMPER_ANI_WALKING_LEFT		0
#define JUMPER_ANI_WALKING_RIGHT	1
#define JUMPER_ANI_JUMPING_LEFT		2
#define JUMPER_ANI_JUMPING_RIGHT	3

class CJumper : public COutdoorEnemy
{
public:
	bool isJumping = false;
	int jumpingHeight;
	CJumper();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

