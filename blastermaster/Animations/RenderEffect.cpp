#include "RenderEffect.h"

void CRenderEffect::Add(int a, int r, int g, int b, DWORD time)
{
	CRenderEffectFrame* frame = new CRenderEffectFrame(a, r, g, b, time);
	frames.push_back(frame);
}

CRenderEffectFrame* CRenderEffect::GetColor()
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}

	return frames[currentFrame]->GetFrame();
}

void CRenderEffects::Add(int id, CRenderEffect* effect)
{
	rendereffects[id] = effect;
}

CRenderEffect* CRenderEffects::Get(int id)
{
	return rendereffects[id];
}

void CRenderEffects::Clear()
{
}

CRenderEffects* CRenderEffects::_instance = NULL;

CRenderEffects* CRenderEffects::GetInstance()
{
	if (_instance == NULL)
	{
		_instance = new CRenderEffects();
		CRenderEffect* effect = new CRenderEffect();
		effect->Add(255, 255, 51, 0, 30);
		effect->Add(255, 102, 255, 153, 30);
		//effect->Add(255, 0, 0, 255, 15);
		_instance->Add(0, effect);
	}
	return _instance;
}
