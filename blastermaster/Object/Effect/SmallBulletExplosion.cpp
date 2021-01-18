#include "SmallBulletExplosion.h"

CSmallBulletExplosion::CSmallBulletExplosion()
{
	LPANIMATION ani = new CAnimation();
	*ani = *(CAnimations::GetInstance()->Get(SMALL_BULLET_EXLOSION_ANI_ID));
	this->animation = ani;
	animation->SetCurrentFrame(0);
	animation->ResetFrameTime();
}

void CSmallBulletExplosion::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = left + SMALL_BULLET_EXLOSION_BBOX_WIDTH;
	bottom = top - SMALL_BULLET_EXLOSION_BBOX_HEIGHT;
}

void CSmallBulletExplosion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (animation->GetCurrentFrame() == animation->GetFramesSize() - 1)
	{
		this->isDestroyed = true;
	}
}

void CSmallBulletExplosion::Render()
{
	int width = SMALL_BULLET_EXLOSION_BBOX_WIDTH;
	int height = SMALL_BULLET_EXLOSION_BBOX_HEIGHT
	float centerx = (float)width / 2;
	float centery = (float)height / 2;
	if(!isDestroyed)
		this->animation->Render(x, y,255,255,255,255,&D3DXVECTOR3(centerx,centery,0.0f));
}
