#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"


using namespace std;

class CGameObject
{
protected:

	float x; 
	float y;

	float vx;
	float vy;

	int nx;	 

	int state;									

	vector<LPANIMATION> animations;

public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	
	void SetState(int state) { this->state = state; }
	int GetState() { return this->state; }


	void AddAnimation(int aniId);

	CGameObject();

	virtual void Update(DWORD dt);
	virtual void Render();
	~CGameObject();
};

typedef CGameObject* LPGAMEOBJECT;