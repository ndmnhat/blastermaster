#pragma once
#include "Define.h"
#include <d3dx9.h>
#include "GameObject.h"
class CCamera
{
private:
	static CCamera* _instance;
	float xCam;
	float yCam;
	
	float freeCamWidth = FREE_CAM_WIDTH;
	float freeCamHeight = FREE_CAM_HEIGHT;

	float RightBoundary;
	float BottomBoundary;

	CGameObject* objectToFollow = NULL;
public:
	void SetCamBoundary(float left, float bottom) { RightBoundary = left, BottomBoundary = bottom; };
	void SetPosition(float x, float y) { xCam = x; yCam = y; };
	D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(xCam, yCam, 0); };
	D3DXVECTOR3 Transform(D3DXVECTOR3 mapPosition);
	void SetFollow(CGameObject * gameobject);
	void Update(DWORD dt);
	static CCamera* GetInstance();
};
