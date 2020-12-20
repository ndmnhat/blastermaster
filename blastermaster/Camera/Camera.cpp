#include "Camera.h"

CCamera* CCamera::_instance = NULL;

D3DXVECTOR3 CCamera::Transform(D3DXVECTOR3 mapPosition)
{
	//return D3DXVECTOR3(mapPosition.x-xCam,mapPosition.y-yCam,0);
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._11 = 1;
	matrix._22 = -1;
	matrix._33 = 1;
	matrix._44 = 1;
	matrix._41 = -xCam;
	matrix._42 = yCam;

	D3DXVECTOR3 pos3(mapPosition.x, mapPosition.y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	D3DXVECTOR3 result = D3DXVECTOR3(MatrixResult.x, MatrixResult.y, 0);
	return result;
}

void CCamera::MoveToSection(float left, float top, float right, float bottom)
{
	isMovingToNewSection = true;
	backupLeftBoundary = LeftBoundary;
	LeftBoundary = left;
	TopBoundary = top;
	RightBoundary = right;
	BottomBoundary = bottom;
}

void CCamera::SetFollow(CGameObject* gameobject)
{
	this->objectToFollow = gameobject;
}

void CCamera::Update(DWORD dt)
{
	int screen_height = CGlobalVariable::GetInstance()->ScreenHeight;
	int screen_width = CGlobalVariable::GetInstance()->ScreenWidth;
	if (isMovingToNewSection)
	{
		if (backupLeftBoundary < LeftBoundary) // Move to left
		{
			if (this->xCam < LeftBoundary) //Still moving
			{
				this->xCam += CAMERA_MOVE_SECTION_SPEED * dt;
			}
			else //Moving done
			{
				this->isMovingToNewSection = false;
			}
		}
		else // Move to right
		{
			if (this->xCam > RightBoundary) //Still moving
			{
				this->xCam -= CAMERA_MOVE_SECTION_SPEED * dt;
			}
			else //Moving done
			{
				this->isMovingToNewSection = false;
			}
		}
		if (this->yCam>TopBoundary)
		{
			this->yCam -= CAMERA_MOVE_SECTION_SPEED * dt;
		}
		if (this->yCam < BottomBoundary)
		{
			this->yCam += CAMERA_MOVE_SECTION_SPEED * dt;
		}
		return;
	}
	//Follow object
	if (objectToFollow != NULL)
	{
		if (objectToFollow->GetX() < xCam + (screen_width - freeCamWidth) / 2)
			this->xCam = objectToFollow->GetX() - (screen_width - freeCamWidth) / 2;

		if (objectToFollow->GetX() > xCam + (screen_width + freeCamWidth) / 2 - 30)
			this->xCam = objectToFollow->GetX() - (screen_width + freeCamWidth) / 2 + 30;

		if (objectToFollow->GetY() > yCam - (screen_height - freeCamHeight) / 2)
			this->yCam = objectToFollow->GetY() + (screen_height - freeCamHeight) / 2;

		if (objectToFollow->GetY() < yCam - (screen_height + freeCamHeight) / 2)
			this->yCam = objectToFollow->GetY() + (screen_height + freeCamHeight) / 2;
	}

	//this->xCam = objectToFollow->GetX() - WINDOW_WIDTH/2;
	//this->yCam = objectToFollow->GetY() + WINDOW_HEIGHT/2;
	
	//Check boundary
	if (this->xCam < LeftBoundary)
		this->xCam = LeftBoundary;
	if (this->xCam > RightBoundary)
		this->xCam = RightBoundary;
	if (this->yCam > TopBoundary)
		this->yCam = TopBoundary;
	if (this->yCam < BottomBoundary)
		this->yCam = BottomBoundary;
	//DebugOut(L"%f, %f, %f\n",this->yCam, TopBoundary, BottomBoundary);
}

CCamera* CCamera::GetInstance()
{
	if (_instance == NULL)
		_instance = new CCamera();
	return _instance;
}
