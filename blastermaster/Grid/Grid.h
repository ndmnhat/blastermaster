#pragma once
#include "..\Define\Define.h"
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include <math.h>
#include "..\Camera\Camera.h"
#include "..\Object\GameObject.h"

class CGrid
{
private:
	static CGrid* _instance;
	unordered_map<int,unordered_map<int, vector<LPGAMEOBJECT>>> Cell;
public:
	static CGrid* GetInstance() { if (_instance == NULL) _instance = new CGrid(); return _instance; }
	void addObject(LPGAMEOBJECT object);
	void removeObject(LPGAMEOBJECT object);
	void updateObjects(vector<LPGAMEOBJECT> objects);
	vector<LPGAMEOBJECT> ObjectsInCam(CCamera* cam);
};

