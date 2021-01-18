#pragma once
#include "..\GameObject.h"

class CItem : public CGameObject
{
public:
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) = 0;
	virtual void Render() = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
};

