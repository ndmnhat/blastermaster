#pragma once
#include "OutdoorEnemy.h"

#define WORM_WALKING_SPEED 0.1f

#define WORM_STATE_WALKING_LEFT 100
#define WORM_STATE_WALKING_LEFT 200

#define WORM_BBOX_WIDTH		18
#define WORM_BBOX_HEIGHT	10

class CWorm : public COutdoorEnemy
{
public:
	CWorm();
};

