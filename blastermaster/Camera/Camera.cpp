#include "Camera.h"

CCamera* CCamera::_instance = NULL;

D3DXVECTOR3 CCamera::Transform(D3DXVECTOR3 mapPosition)
{
	//return D3DXVECTOR3(mapPosition.x-xCam,mapPosition.y-yCam,0);
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = xCam;
	matrix._42 = yCam;

	D3DXVECTOR3 pos3(xCam, yCam, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR3 result = D3DXVECTOR3(MatrixResult.x, MatrixResult.y, 0);
	return result;
}

void CCamera::SetFollow(CGameObject* gameobject)
{
	this->objectToFollow = gameobject;
}

void CCamera::Update(DWORD dt)
{
	//Follow object
	if (objectToFollow != NULL)
	{
		if (objectToFollow->GetX() < xCam + (SCREEN_WIDTH - freeCamWidth) / 2)
			this->xCam = objectToFollow->GetX() - (SCREEN_WIDTH - freeCamWidth) / 2;

		if (objectToFollow->GetX() > xCam + (SCREEN_WIDTH + freeCamWidth) / 2 - 30)
			this->xCam = objectToFollow->GetX() - (SCREEN_WIDTH + freeCamWidth) / 2 + 30;

		if (objectToFollow->GetY() < yCam + (SCREEN_HEIGHT - freeCamHeight) / 2)
			this->yCam = objectToFollow->GetY() - (SCREEN_HEIGHT - freeCamHeight) / 2;

		if (objectToFollow->GetY() > yCam + (SCREEN_HEIGHT + freeCamHeight) / 2)
			this->yCam = objectToFollow->GetY() - (SCREEN_HEIGHT + freeCamHeight) / 2;
	}

	//this->xCam = objectToFollow->GetX() - SCREEN_WIDTH/2;
	//this->yCam = objectToFollow->GetY() - SCREEN_HEIGHT/2;
	
	//Check boundary
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
