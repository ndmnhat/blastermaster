#pragma once
#include "GameObject.h"
class CFence : public CGameObject
{
protected:
	int width, height;
public:
	CFence();
	void SetSize(int width, int height);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};
