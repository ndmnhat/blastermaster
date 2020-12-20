#pragma once
#include "GameObject.h"
class CGateway : public CGameObject
{
private:
	float DestinationX;
	float DestinationY;
public:
	CGateway();
	int newSectionID;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetDestination(float x, float y) { DestinationX = x; DestinationY = y; }
	void GetDestination(float& x, float& y) { x = DestinationX; y = DestinationY; }
	void SetSize(int width, int height);
	void Render();
};

