#pragma once
#include "..\Define\Define.h"
#include "GameObject.h"

class CWall : public CGameObject
{
protected:
	int width, height;
public:
	CWall();
	void SetSize(int width, int height);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

