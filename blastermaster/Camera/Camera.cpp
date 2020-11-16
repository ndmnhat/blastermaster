#include "Camera.h"

CCamera* CCamera::_instance = NULL;

D3DXVECTOR3 CCamera::Transform(D3DXVECTOR3 mapPosition)
{
	return D3DXVECTOR3(mapPosition.x-xCam,mapPosition.y-yCam,0);
}

void CCamera::SetFollow(CGameObject* gameobject)
{
	this->objectToFollow = gameobject;
}

void CCamera::Update(DWORD dt)
{
	if (objectToFollow->GetX() < xCam + (SCREEN_WIDTH - freeCamWidth)/2)
		this->xCam = objectToFollow->GetX() - (SCREEN_WIDTH - freeCamWidth) / 2;

	if (objectToFollow->GetX() > xCam + (SCREEN_WIDTH  + freeCamWidth) / 2 - 30)
		this->xCam = objectToFollow->GetX() - (SCREEN_WIDTH + freeCamWidth) / 2 + 30;
	
	if (objectToFollow->GetY() < yCam + (SCREEN_HEIGHT - freeCamHeight) / 2)
		this->yCam = objectToFollow->GetY() - (SCREEN_HEIGHT - freeCamHeight) / 2;

	if (objectToFollow->GetY() > yCam + (SCREEN_HEIGHT + freeCamHeight) / 2)
		this->yCam = objectToFollow->GetY() - (SCREEN_HEIGHT + freeCamHeight) / 2;

	//this->xCam = objectToFollow->GetX() - SCREEN_WIDTH/2;
	//this->yCam = objectToFollow->GetY() - SCREEN_HEIGHT/2;

	if (this->xCam < 0)
		this->xCam = 0;
	if (this->xCam > this->RightBoundary)
		this->xCam = this->RightBoundary;
	if (this->yCam < 0)
		this->yCam = 0;
	if (this->yCam > this->BottomBoundary)
		this->yCam = this->BottomBoundary;
}

CCamera* CCamera::GetInstance()
{
	if (_instance == NULL)
		_instance = new CCamera();
	return _instance;
}
