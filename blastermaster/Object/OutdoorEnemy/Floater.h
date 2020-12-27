#pragma once
#include "OutdoorEnemy.h"
#include "..\Bullet\FloaterBullet.h"

#define FLOATER_FLYING_SPEED_X	0.05f
#define FLOATER_FLYING_SPEED_Y	0.04f

#define FLOATER_BBOX_HEIGHT	16
#define FLOATER_BBOX_WIDTH	18

#define FLOATER_ANI_FLYING_LEFT		0
#define FLOATER_ANI_FLYING_RIGHT	1
#define FLOATER_ANI_ATTACK_LEFT		2
#define FLOATER_ANI_ATTACK_RIGHT	3

class CFloater : public COutdoorEnemy
{
private:
	int ny;
	int ClipSize;
	DWORD reloadingTimeCount;
public:
	CFloater();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	void Fire(int Direction);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

