#pragma once
#include "..\GameObject.h"
#include "..\..\Utils\Utils.h"
#include "..\Bullet\Bullet.h"
#include "..\Gateway.h"
#include "..\..\Grid\Grid.h"
#include "..\..\Map\Section.h"
class CPlayer : public CGameObject
{
protected:
	DWORD untouchableStart;
	DWORD rotatingStart;
	DWORD reloadingTimeCount;
	BulletType currentBulletType;
	int currentAnimation;
	int ClipSize;
	float AutoX;
	float AutoY;
	int backupSectionID;
	bool isUntouchable = false;
	void StartUntouchable() { this->isUntouchable = true; untouchableStart = GetTickCount(); }
public:
	bool isDead = false;
	bool isAutoGoX = false;
	bool isAutoGoY = false;
	virtual void Render() = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) = 0;
	virtual void SetState(int state) = 0;
	virtual void Fire(float Direction) = 0;
};

