#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

class CRenderEffectFrame {
public:
	int A;
	int R;
	int G;
	int B;
	DWORD time;
	CRenderEffectFrame(int a, int r, int g, int b, int time) { this->A = a; this->R = r; this->G = g; this->B = b; this->time = time; }
	DWORD GetTime() { return time; }
	CRenderEffectFrame* GetFrame() { return this; }
};
class CRenderEffect
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	std::vector<CRenderEffectFrame*> frames;
public:
	CRenderEffect(int defaultTime = 15) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; }
	void Add(int a, int r, int g, int b, DWORD time = 0);
	int GetCurrentFrame() { return currentFrame; }
	int GetFramesSize() { return frames.size(); }
	void SetCurrentFrame(int frame) { currentFrame = frame; }
	DWORD GetPassedFrameTime() { return (GetTickCount() - lastFrameTime); }
	CRenderEffectFrame* GetColor();
};
class CRenderEffects
{
	static CRenderEffects* _instance;
	std::unordered_map<int, CRenderEffect*> rendereffects;
public:
	void Add(int id, CRenderEffect* effect);
	CRenderEffect* Get(int id);
	void CRenderEffects::Clear();

	static CRenderEffects* GetInstance();
};
