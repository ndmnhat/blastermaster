#pragma once
#include "GameObject.h"
class CLava : public CGameObject
{
protected:
	int width, height;
public:
	CLava();
	void SetSize(int width, int height);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

