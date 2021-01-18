#pragma once
#include "..\Animations\Animations.h"
#include "..\Object\GameObject.h"
#define HEALTHBAR_SPRITE_ID 100000
#define HEALTH_SPRITE_ID 100001
#define POW_SPRITE_ID 100002

class CHealthBar
{
public:
	CHealthBar();
	CSprite* POW;
	CSprite* Healthbar;
	CSprite* Health;
	int HealthCount;
	void Update(LPGAMEOBJECT object);
	void Render();
};

