#pragma once

#include "..\GameObject.h"
#include <math.h>

#define PI 3.14159265f

class CGameObject;


class CBullet : public CGameObject
{
protected:
	float Direction;
	float Speed;
	DWORD LifeTime;
	float DirectioninRad;
	DWORD lifeTimeStart;
public:
	virtual void SetDirection(float direction) { this->Direction = direction; DirectioninRad = Direction * PI / 180; }
	virtual float GetDirection() { return Direction; }
	virtual int GetDamage() { return this->Damage; }
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CBullet();
};

