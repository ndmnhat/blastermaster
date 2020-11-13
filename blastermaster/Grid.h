#pragma once
#include "Define.h"
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <math.h>
#include "GameObject.h"
#include "Camera.h"
class CGrid
{
private:
	vector<vector<vector<LPGAMEOBJECT>>> Cell;
public:
	void initGrid(vector<LPGAMEOBJECT> objects);
	void addObject(LPGAMEOBJECT object);
	void removeObject(LPGAMEOBJECT object);
	void updateObjects(vector<LPGAMEOBJECT> objects);
	vector<LPGAMEOBJECT> ObjectsInCam(CCamera* cam);
};

