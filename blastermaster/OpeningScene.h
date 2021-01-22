#pragma once
#include "Object/GameObject.h"
#include "IntroScene.h"

#define OPENING_CUT_SCENE_BBOX_WIDTH 256
#define OPENING_CUT_SCENE_BBOX_HEIGHT 224

#define OPENING_CUT_SCENE 0

class OpeningScene : public CGameObject
{
public:
	OpeningScene();

	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	~OpeningScene();
};

