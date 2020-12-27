#pragma once
#include "OutdoorEnemy.h"
#include "..\..\Utils\Utils.h"
#include "..\..\Camera\Camera.h"
#define DOME_CHARGING_SPEED		0.15f
#define DOME_MOVING_SPEED		0.025f
#define DOME_GRAVITY			0.001f
#define DOME_ANI_CRAWLING_LEFT			0	//di qua trai tren tran
#define DOME_ANI_CRAWLING_RIGHT			1	//di qua phai tren tran
#define DOME_ANI_CRAWLING_DOWN_LEFT		2	//di xuong duoi ben trai tuong
#define DOME_ANI_CRAWLING_UP_LEFT		3	//di len tren ben trai tuong 
#define DOME_ANI_CRAWLING_UP_RIGHT		4	//di len tren ben phai tuong
#define DOME_ANI_CRAWLING_DOWN_RIGHT	5	//di xuong duoi ben phai tuong
#define DOME_ANI_WALKING_LEFT			6	//di qua trai duoi dat
#define DOME_ANI_WALKING_RIGHT			7	//di qua phai tren tran
#define DOME_ANI_CHARGING_LEFT			8	//tan cong ve phia bên trai
#define DOME_ANI_CHARGING_RIGHT			9	//tan cong ve phia bên phai
#define DOME_ANI_CHARGING_DOWN			10	//tan cong xuong duoi
#define DOME_ANI_CHARGING_UP			11	//tan cong len tren


#define DOME_STATE_ATTACK_Y			0	//t_thai tan cong theo phuong doc
#define DOME_STATE_ATTACK_X			1	//t_thai tan cong theo phuong ngang
#define DOME_STATE_ON_LEFT_WALL		2
#define DOME_STATE_ON_RIGHT_WALL	3
#define DOME_STATE_ON_THE_CEILING	4	
#define DOME_STATE_ON_THE_GROUND	5	

#define DOME_BBOX_HEIGHT	18	 
#define DOME_BBOX_WIDTH		18

struct Location {
	float left = -1;
	float top = 2147483647;
	float right = 2147483647;
	float bottom = -1;
};

class CDome : public COutdoorEnemy
{
	int ny;
	Location wallPosition; //nho thong so cua tuong da va cham
public:
	CDome();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void SetState(int state);
};

