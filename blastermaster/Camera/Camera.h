#pragma once
#include "..\Define\Define.h"
#include <d3dx9.h>
#include "..\Object\GameObject.h"

#define CAMERA_MOVE_SECTION_SPEED 0.2f

class CCamera
{
private:
	static CCamera* _instance;
	float xCam;
	float yCam;
	
	float freeCamWidth = FREE_CAM_WIDTH;
	float freeCamHeight = FREE_CAM_HEIGHT;

	float LeftBoundary;
	float TopBoundary;
	float RightBoundary;
	float BottomBoundary;

	float backupLeftBoundary;

	CGameObject* objectToFollow = NULL;
public:
	bool isMovingToNewSection = false;
	void SetCamBoundary(float left, float top, float right, float bottom) { isMovingToNewSection = false;  LeftBoundary = left, TopBoundary = top; RightBoundary = right; BottomBoundary = bottom; };
	void SetPosition(float x, float y) { xCam = x; yCam = y; };
	D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(xCam, yCam, 0); };
	D3DXVECTOR3 Transform(D3DXVECTOR3 mapPosition);
	void MoveToSection(float left, float top, float right, float bottom);
	void SetFollow(CGameObject * gameobject);
	void Update(DWORD dt);
	static CCamera* GetInstance();
};

