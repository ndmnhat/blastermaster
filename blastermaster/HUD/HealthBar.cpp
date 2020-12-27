#include "HealthBar.h"

CHealthBar::CHealthBar()
{
	Healthbar = CSprites::GetInstance()->Get(HEALTHBAR_SPRITE_ID);
	Health = CSprites::GetInstance()->Get(HEALTH_SPRITE_ID);
	POW = CSprites::GetInstance()->Get(POW_SPRITE_ID);
}

void CHealthBar::Update(LPGAMEOBJECT object)
{
	HealthCount = ceil((float)(object->GetHealth())/100*8);
}

void CHealthBar::Render()
{
	POW->Draw2(20, 185);
	Healthbar->Draw2(20, 152);
	for (int i = 0; i < HealthCount; ++i)
	{
		Health->Draw2(20, 180-4*i);
	}
}
