#include "OpeningScene.h"



OpeningScene::OpeningScene()
{
	type = TYPE_INTRO_OPENING;
}

void OpeningScene::Update(DWORD dt)
{
	CGameObject::Update(dt);
}

void OpeningScene::Render()
{
	int ani;
	ani = OPENING_CUT_SCENE;
	animation_set->at(ani)->Render(x, y);
}

void OpeningScene::SetState(int state)
{
}

void OpeningScene::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	right = x + OPENING_CUT_SCENE_BBOX_WIDTH;
	top = y;
	bottom = y + OPENING_CUT_SCENE_BBOX_HEIGHT;
}


OpeningScene::~OpeningScene()
{
}
