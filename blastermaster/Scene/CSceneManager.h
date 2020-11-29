#pragma once
#include "..\Define\Define.h"
#include "Scene.h"
#include "SceneGame.h"
#include <unordered_map>

using namespace std;

class CSceneManager
{
	static CSceneManager* __instance;
	unordered_map<int, CScene*> scenes;
	int CurrentSceneID = -1;
public:
	CSceneManager();
	CScene* GetCurrentScene();
	void SetScene(int id);
	void AddScene(CScene * scene);
	void Update(DWORD dt);
	void Render();
	static CSceneManager* GetInstance();
};

