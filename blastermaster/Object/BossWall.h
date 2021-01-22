#pragma once
#include "GameObject.h"
class CBossWall : public CGameObject
{
protected:
	int width, height;
public:
	CBossWall();
	void SetSize(int width, int height);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

