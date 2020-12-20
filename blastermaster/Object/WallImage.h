#pragma once
#include "GameObject.h"
class CWallImage : public CGameObject
{
private:
	LPSPRITE image;
public:
	CWallImage();
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetSize(int width, int height);
	void SetImage(LPSPRITE sprite) { image = sprite; }
};

