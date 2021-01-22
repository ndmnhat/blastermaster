#pragma once
#include "OutdoorEnemy.h"
#include "..\..\Grid\Grid.h"
#include "..\Bullet\BossBullet.h"

#define CRABULLUS_MOVING_SPEED_X 0.05f
#define CRABULLUS_MOVING_SPEED_Y 0.01f
#define CRABULLUS_BBOX_WIDTH 60
#define CRABULLUS_BBOX_HEIGHT 65
#define CRABULLUS_RELOAD_TIME 3000
#define CRABULLUS_INCLIP_RELOAD_TIME 250


class CCrabullus : public COutdoorEnemy
{
private:
	DWORD ReloadTimeCount;
	DWORD InclipReloadTimeCount;
	void StartReload();
	int ClipSize;
	bool isReloading = false;
public:
	CCrabullus();
	int ny;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Fire(int Direction);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

